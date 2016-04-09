#include "GL/glew.h"
#include "GL/glu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_opengl.h"

#include "gfx/renderer.h"
#include "gfx/camera.h"
#include "color.h"
#include "game_object.h"
#include "gfx/sprite.h"
#include "util/logger.h"
#include "point.h"
#include "hit_point.h"
#include "entity.h"
#include "util/math/math.h"
#include "util/file_reader.h"
#include "frame.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer()
{
    window_ = nullptr;
    renderer_ = nullptr;
    camera_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
bool Renderer::init()
{
    // Initialize SDL
    // TODO(2013-08-23/JM): Move this elsewhere, init function for whole game
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        Logger::write(Logger::ss << "SDL could not initialize. SDL Error: " << SDL_GetError());
        return false;
    }

    // Initialize for core context, getting rid of old OpenGL functionality
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // No idea what this does

    // Set OpenGL Version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    int img_flags = IMG_INIT_PNG;

    // Initialize SDL_image
    if(!(IMG_Init(img_flags) & img_flags)) {
        Logger::write(Logger::ss << "ERROR: SDL_image could not initialize! SDL_image Error: " <<  IMG_GetError());
        return false;
    }

    // Initialize SDL_ttf
    if(TTF_Init() == -1) {
        Logger::write(Logger::ss << "ERROR: TTF_Init: " << TTF_GetError());
        return false;
    }

    // Setup renderer
    window_ = SDL_CreateWindow(kWindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        kRendererWidth, kRendererHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(window_ == nullptr) {
        Logger::write(Logger::ss << "ERROR: Could not create window! SDL Error: " << SDL_GetError());
        return false;
    }

    // Renderer for 2D opengl, leaving uncommented to prevent crashing but remove eventually
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if(renderer_ == nullptr) {
        Logger::write(Logger::ss << "ERROR: Could not create renderer! SDL Error: " << SDL_GetError());
        return false;
    }
    
    // Create context
    context_ = SDL_GL_CreateContext(window_);
    if(context_ == nullptr) {
        Logger::write(Logger::ss << "ERROR: Could not create OpenGL context! SDL Error: " << SDL_GetError());
        return false;
    }

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if(glewError != GLEW_OK) {
        Logger::write(Logger::ss << "ERROR: Could not initialize GLEW! GLEW Error: " << glewGetErrorString(glewError));
        return false;
    }

    // Enable VSync
    if(SDL_GL_SetSwapInterval(1) < 0) {
        Logger::write(Logger::ss << "ERROR: Could not set VSync! SDL Error: " << SDL_GetError());
        return false;
    }

    // Initialize OpenGL
    if(!initShader()) {
        Logger::write(Logger::ss << "ERROR: Could not initialize OpenGL!");
        return false;
    }

    //int w;
    //int h;
    //SDL_GetWindowMinimumSize(window_, &w, &h);
    //Logger::write(Logger::ss << "Minimum: (" << w << " x " << h << ")");
    //SDL_GetWindowMaximumSize(window_, &w, &h);
    //Logger::write(Logger::ss << "Maximum: (" << w << " x " << h << ")");

    return true;
}

bool Renderer::initShader()
{
    // Generate program
    programID_ = glCreateProgram();

    // Create vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Get vertex shader source
    //const GLchar * vertexShaderSource[] = FileReader::read_file("shader/v1.vs");
    std::string vertexShaderStr = FileReader::read_file("shader/v1.vs");
    const GLchar * vertexShaderSource = vertexShaderStr.c_str();
    
    //{
    //    "#version 130\nin vec2 LVertexPos2D; void main() { gl_Position = vec4(LVertexPos2D.x, LVertexPos2D.y, 0, 1); }" 
    //};

    // Set vertex source
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

    // Compile vertex source
    glCompileShader(vertexShader);

    // Check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);

    if(vShaderCompiled != GL_TRUE) {
        Logger::write(Logger::ss << "ERROR: Could not compile vertex shader: " << vertexShader);
        printShaderLog(vertexShader);
        return false;
    }

    // Attach vertex shader to program
    glAttachShader(programID_, vertexShader);

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Get fragment source
    std::string fragmentShaderStr = FileReader::read_file("shader/f1.fs");
    const GLchar * fragmentShaderSource = fragmentShaderStr.c_str();

    //{
    //    "#version 130\nout vec4 LFragment; void main() { LFragment = vec4(1.0, 1.0, 1.0, 1.0); }"
    //};

    // Set fragment source
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    // Compile fragment source
    glCompileShader(fragmentShader);

    // Check fragment shader for errors
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);

    if(fShaderCompiled != GL_TRUE) {
        Logger::write(Logger::ss << "ERROR: Could not compile fragment shader: " << fragmentShader);
        printShaderLog(fragmentShader);
        return false;
    }

    // Attach fragment shader to program
    glAttachShader(programID_, fragmentShader);

    // Link program
    glLinkProgram(programID_);

    // Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programID_, GL_LINK_STATUS, &programSuccess);

    if(programSuccess != GL_TRUE) {
        Logger::write(Logger::ss << "ERROR: Could not link program: " << programID_);
        printProgramLog(programID_); 
        return false;
    }

    return true;

}

void Renderer::printProgramLog(GLuint program)
{
    // Make sure name is program
    if(glIsProgram(program)) {
        
        // Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        // Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // Allocate string
        char * infoLog = new char[maxLength];

        // Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);

        if(infoLogLength > 0) {
            // Print log
            printf("%s\n", infoLog);
        }
        
        // Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a program\n", program);
    }
}

void Renderer::printShaderLog(GLuint shader)
{
    // Make sure name is shader
    if(glIsShader(shader)) {
        
        // Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        // Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // Allocate string
        char * infoLog = new char[maxLength];

        // Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

        if(infoLogLength > 0) {
            // Print log
            printf("%s\n", infoLog);
        }
        
        // Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a shader\n", shader);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::render_texture(SDL_Texture * texture, SDL_Rect * offset, SDL_Rect * clip)
{
    // TODO(2013-09-09/JM): Add render offset checks
    Point point = Point(offset->x, offset->y);
    point = Math::convert_to_isometric(point);

    //SDL_Rect rect = { (int)offset->x - (int)camera_->x_position(), (int)offset->y - (int)camera_->y_position(), (int)offset->w, (int)offset->h };
    SDL_Rect rect = { (int)point.x() - (int)camera_->x_position(), (int)point.y() - (int)camera_->y_position(), (int)offset->w, (int)offset->h };

    int return_code = SDL_RenderCopy(renderer_, texture, clip, &rect);

    if(return_code != 0) {
        Logger::write(Logger::ss << "Render Error: " << SDL_GetError());
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::render_texture_frame(SDL_Texture * texture, Frame * frame, SDL_Rect * offset, SDL_Rect * clip)
{
    if(frame == nullptr) {
        render_texture(texture, offset, clip);
    }
    else {
        //Logger::write(Logger::ss << frame->to_string());
        SDL_Rect * new_offset = new SDL_Rect;
        new_offset->x = offset->x + frame->x();
        new_offset->y = offset->y + frame->y();
        new_offset->w = offset->w;
        new_offset->h = offset->h;

        render_texture(texture, new_offset, clip);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::render_texture_rotate(SDL_Texture * texture, SDL_Rect * offset, SDL_Rect * clip, double angle)
{
    // TODO(2013-09-09/JM): Add render offset checks

    SDL_Rect rect = { (int)offset->x - (int)camera_->x_position(), (int)offset->y - (int)camera_->y_position(), (int)offset->w, (int)offset->h };

    int return_code = SDL_RenderCopyEx(renderer_, texture, nullptr, &rect, -angle, nullptr, SDL_FLIP_NONE);

    if(return_code != 0) {
        Logger::write(Logger::ss << "Render Error: " << SDL_GetError());
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::apply_surface(SDL_Surface * source, SDL_Surface * destination, SDL_Rect * offset, SDL_Rect * clip)
{
    SDL_BlitSurface(source, clip, destination, offset );
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::clear()
{
    SDL_SetRenderDrawColor(renderer_, kDefaultClearColor.red(), kDefaultClearColor.green(), kDefaultClearColor.blue(), 255);
    SDL_RenderClear(renderer_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::clear(Color clear_color)
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::update()
{
    //if(debug_) debug_frame_->render();
    //SDL_RenderPresent(renderer_);
    SDL_GL_SwapWindow(window_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::clean_up()
{
    // TODO(2013-08-23/JM): Move this elsewhere, cleanup function for whole game

    //NOTE/TODO: Uncomment this when SDL_ttf is installed
    //TTF_Quit();
    
    // Deallocate program
    glDeleteProgram(programID_);

    // Destroy window
    SDL_DestroyWindow(window_);

    SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Renderer::load_image(std::string filename)
{
    SDL_Surface* loaded_image    = nullptr;

    loaded_image = IMG_Load(filename.c_str());

    if(loaded_image == nullptr) {
        Logger::write(Logger::ss << "IMG_Load Error: " << IMG_GetError());
    }
    else {
        Uint32 colorkey = SDL_MapRGB(loaded_image->format, 0xFF, 0, 0xFF);
        SDL_SetColorKey(loaded_image, SDL_TRUE, colorkey);
    }

    return loaded_image;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Renderer::load_image_alpha(std::string filename)
{
    SDL_Surface* loaded_image = nullptr;

    loaded_image = IMG_Load(filename.c_str());
    if(loaded_image == nullptr) {
        Logger::write(Logger::ss << "IMG_Load Error: " << IMG_GetError());
    }
    return loaded_image;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Texture * Renderer::load_texture(std::string filename)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, load_image(filename));

    if(texture == nullptr) {
        Logger::write(Logger::ss << "Error creating texture: " << SDL_GetError());
    }

     return texture;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Texture * Renderer::load_texture_alpha(std::string filename)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, load_image_alpha(filename));

    if(texture == nullptr) {
        Logger::write(Logger::ss << "Error creating texture: " << SDL_GetError());
    }

     return texture;
}
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::init_object(GameObject * object)
{
    object->sprite()->set_texture(load_texture_alpha(object->sprite()->art_asset()));
    object->sprite()->set_renderer(this);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::draw_life_bar(Entity * entity, Frame * frame)
{
    int kBorderRed   = 0x00;
    int kBorderGreen = 0x00;
    int kBorderBlue  = 0x00;
    int kBorderAlpha = 0xFF;

    int kPositiveRed   = 0x00;
    int kPositiveGreen = 0xFF;
    int kPositiveBlue  = 0x00;
    int kPositiveAlpha = 0xFF;

    int kNegativeRed   = 0xFF;
    int kNegativeGreen = 0x00;
    int kNegativeBlue  = 0x00;
    int kNegativeAlpha = 0xFF;

    int width_per_point = 4;

    int total_hp = entity->hp()->total();
    int current_hp = entity->hp()->current();

    int width = total_hp * width_per_point;
    int height = 5;
    int x = entity->x_position() + frame->x()- (total_hp * width_per_point / 2);
    int y = entity->y_position() + frame->y() - (entity->height() / 2) - height;
    x = x - camera_->x_position();
    y = y - camera_->y_position();

    Point point = Point(x,y);
    point = Math::convert_to_isometric(point);
    x = point.x();
    y = point.y();

    SDL_Rect borderRect = {
        x - 1,
        y - 1,
        width + 2,
        height + 2
    };

    SDL_Rect positiveRect = {
        x,
        y,
        current_hp * width_per_point,
        height
    };

    SDL_Rect negativeRect = {
        x + (current_hp * width_per_point),
        y,
        (total_hp - current_hp) * width_per_point,
        height
    };
    // TODO(2014-08-21/JM): Red is showing when entity is at full life. Add is_full_life() and is_zero_life() to lifepoint
    // and use those tests to determine if you should draw the part of the life bar that isn't needed
    // Border
    SDL_SetRenderDrawColor(renderer_, kBorderRed, kBorderGreen, kBorderBlue, kBorderAlpha);
    SDL_RenderDrawRect(renderer_, &borderRect );

    // Negative
    SDL_SetRenderDrawColor(renderer_, kNegativeRed, kNegativeGreen, kNegativeBlue, kNegativeAlpha);
    SDL_RenderFillRect(renderer_, &negativeRect );

    // Positive
    SDL_SetRenderDrawColor(renderer_, kPositiveRed, kPositiveGreen, kPositiveBlue, kPositiveAlpha);
    SDL_RenderFillRect(renderer_, &positiveRect );
}


void Renderer::draw_rectangle(SDL_Rect rect, Color color)
{
    SDL_SetRenderDrawColor(renderer_, color.red(), color.green(), color.blue(), 255);
    SDL_RenderDrawRect(renderer_, &rect );
}

void Renderer::draw_line(Point start, Point end, Color color)
{
    SDL_SetRenderDrawColor(renderer_, color.red(), color.green(), color.blue(), 255);
    SDL_RenderDrawLine(renderer_, start.x(), start.y(), end.x(), end.y());
}


