#include "GL/glew.h"
#include "GL/glu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_opengl.h"

#include "gfx/Renderer.h"
#include "gfx/Camera.h"
#include "Color.h"
#include "GameObject.h"
#include "gfx/Sprite.h"
#include "util/Logger.h"
#include "Point.h"
#include "HitPoint.h"
#include "Entity.h"
#include "math/Math.h"
#include "util/FileReader.h"
#include "Frame.h"
#include "gfx/ResourceManager.h"
#include "gfx/lighting/LightManager.h"

#include "gfx/Shader.h"

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer()
{
    screenWidth_ = kRendererWidth;
    screenHeight_ = kRendererHeight;
    window_ = nullptr;
    renderer_ = nullptr;
    camera_ = nullptr;

    resourceManager_ = nullptr;
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
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        Logger::write(Logger::ss << "SDL could not initialize. SDL Error: " << SDL_GetError());
        return false;
    }

    // Setup screen size
    SDL_DisplayMode current;
    int display = 0;
    if(SDL_GetCurrentDisplayMode(display, &current)) {
        Logger::write(Logger::ss << "SDL could not get display mode. SDL Error: " << SDL_GetError());
    }
    else {
        screenWidth_ = current.w;
        screenHeight_ = current.h;
    }
    Logger::write(Logger::ss << "Setting window size: " << screenWidth_ << " x " << screenHeight_);

    // Set OpenGL Version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Initialize for core context, getting rid of old OpenGL functionality
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); // No idea what this does
    /* 3.2 and higher won't work because code currently doesn't use VAOs */

    // MSAA - Multisample Anti-Aliasing - Do before creating window
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    glEnable(GL_MULTISAMPLE);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    int imgFlags = IMG_INIT_PNG;

    // Initialize SDLImage
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        Logger::write(Logger::ss << "ERROR: SDLImage could not initialize! SDLImage Error: " <<  IMG_GetError());
        return false;
    }

    // Initialize SDLTtf
    if(TTF_Init() == -1) {
        Logger::write(Logger::ss << "ERROR: TTF_Init: " << TTF_GetError());
        return false;
    }

    // Setup renderer
    unsigned int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
    if(kFullscreen) flags |= SDL_WINDOW_FULLSCREEN;
    else flags |= SDL_WINDOW_BORDERLESS;
    window_ = SDL_CreateWindow(kWindowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        screenWidth_, screenHeight_, flags);
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

    // Initialize shaders
    shader_ = new Shader("shader/v1.vs", "shader/f1.fs");
    if(!shader_->init()) {
        Logger::write(Logger::ss << "ERROR: Could not initialize shader");
        return false;
    }
    //textureShader_ = new Shader("shader/v2.vs", "shader/f2.fs");
    //textureShader_ = new Shader("shader/v2.vs", "shader/lighting.fs");
    textureShader_ = new Shader("shader/lighting.vs", "shader/lighting.fs");
    if(!textureShader_->init()) {
        Logger::write(Logger::ss << "ERROR: Could not initialize shader");
        return false;
    }

    lightManager_ = new LightManager();
    if(!lightManager_->init()) {
        Logger::write(Logger::ss << "ERROR: Could not initialize LightManager");
        return false;
    }

    glEnable(GL_DEPTH_TEST);


    //int w;
    //int h;
    //SDL_GetWindowMinimumSize(window_, &w, &h);
    //Logger::write(Logger::ss << "Minimum: (" << w << " x " << h << ")");
    //SDL_GetWindowMaximumSize(window_, &w, &h);
    //Logger::write(Logger::ss << "Maximum: (" << w << " x " << h << ")");


    // Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);
    //glFrontFace(GL_CW);
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    camera_ = new Camera(kRendererWidth, kRendererHeight);
    resourceManager_ = new ResourceManager();

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::renderTexture(SDL_Texture * texture, SDL_Rect * offset, SDL_Rect * clip)
{
    // TODO(2013-09-09/JM): Add render offset checks
    Point point = Point(offset->x, offset->y);
    point = Math::convertToIsometric(point);

    //SDL_Rect rect = { (int)offset->x - (int)camera_->xPosition(), (int)offset->y - (int)camera_->yPosition(), (int)offset->w, (int)offset->h };
    //SDL_Rect rect = { (int)point.x() - (int)camera_->xPosition(), (int)point.y() - (int)camera_->yPosition(), (int)offset->w, (int)offset->h };
    SDL_Rect rect = { (int)point.x(), (int)point.y(), (int)offset->w, (int)offset->h };

    int returnCode = SDL_RenderCopy(renderer_, texture, clip, &rect);

    if(returnCode != 0) {
        Logger::write(Logger::ss << "Render Error: " << SDL_GetError());
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::renderTextureFrame(SDL_Texture * texture, Frame * frame, SDL_Rect * offset, SDL_Rect * clip)
{
    if(frame == nullptr) {
        renderTexture(texture, offset, clip);
    }
    else {
        //Logger::write(Logger::ss << frame->toString());
        SDL_Rect * newOffset = new SDL_Rect;
        newOffset->x = offset->x + frame->x();
        newOffset->y = offset->y + frame->y();
        newOffset->w = offset->w;
        newOffset->h = offset->h;

        renderTexture(texture, newOffset, clip);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::renderTextureRotate(SDL_Texture * texture, SDL_Rect * offset, SDL_Rect * clip, double angle)
{
    // TODO(2013-09-09/JM): Add render offset checks

    //SDL_Rect rect = { (int)offset->x - (int)camera_->xPosition(), (int)offset->y - (int)camera_->yPosition(), (int)offset->w, (int)offset->h };
    SDL_Rect rect = { (int)offset->x, (int)offset->y, (int)offset->w, (int)offset->h };

    int returnCode = SDL_RenderCopyEx(renderer_, texture, nullptr, &rect, -angle, nullptr, SDL_FLIP_NONE);

    if(returnCode != 0) {
        Logger::write(Logger::ss << "Render Error: " << SDL_GetError());
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::applySurface(SDL_Surface * source, SDL_Surface * destination, SDL_Rect * offset, SDL_Rect * clip)
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
    // Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::clear(Color clearColor)
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

}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::render()
{
    //if(debug_) debugFrame_->render();
    //SDL_RenderPresent(renderer_);
    SDL_GL_SwapWindow(window_);
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::cleanUp()
{
    // TODO(2013-08-23/JM): Move this elsewhere, cleanup function for whole game

    //NOTE/TODO: Uncomment this when SDLTtf is installed
    //TTF_Quit();
    
    // Destroy window
    SDL_DestroyWindow(window_);

    SDL_Quit();
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Renderer::loadImage(std::string filename)
{
    SDL_Surface* loadedImage    = nullptr;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage == nullptr) {
        Logger::write(Logger::ss << "IMG_Load Error: " << IMG_GetError());
    }
    else {
        Uint32 colorkey = SDL_MapRGB(loadedImage->format, 0xFF, 0, 0xFF);
        SDL_SetColorKey(loadedImage, SDL_TRUE, colorkey);
    }

    return loadedImage;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Surface * Renderer::loadImageAlpha(std::string filename)
{
    SDL_Surface* loadedImage = nullptr;

    loadedImage = IMG_Load(filename.c_str());
    if(loadedImage == nullptr) {
        Logger::write(Logger::ss << "IMG_Load Error: " << IMG_GetError());
    }
    return loadedImage;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
SDL_Texture * Renderer::loadTexture(std::string filename)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, loadImage(filename));

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
SDL_Texture * Renderer::loadTextureAlpha(std::string filename)
{
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer_, loadImageAlpha(filename));

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
void Renderer::drawLifeBar(Entity * entity, Frame * frame)
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

    int widthPerPoint = 4;

    int totalHp = entity->hp()->total();
    int currentHp = entity->hp()->current();

    int width = totalHp * widthPerPoint;
    int height = 5;
    int x = entity->xPosition() + frame->x()- (totalHp * widthPerPoint / 2);
    int y = entity->yPosition() + frame->y() - (entity->height() / 2) - height;
    //x = x - camera_->xPosition();
    //y = y - camera_->yPosition();

    Point point = Point(x,y);
    point = Math::convertToIsometric(point);
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
        currentHp * widthPerPoint,
        height
    };

    SDL_Rect negativeRect = {
        x + (currentHp * widthPerPoint),
        y,
        (totalHp - currentHp) * widthPerPoint,
        height
    };
    // TODO(2014-08-21/JM): Red is showing when entity is at full life. Add isFullLife() and isZeroLife() to lifepoint
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

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
void Renderer::warpMouse(const Vector2i position)
{
    SDL_WarpMouseInWindow(window_, position.x(), position.y());
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
void Renderer::showCursor(bool show)
{
    int toggle;
    if(show) toggle = 1;
    else toggle = 0;
    
    SDL_ShowCursor(toggle);
}

bool Renderer::windowFocused()
{
    unsigned int flags = SDL_GetWindowFlags(window_);
    bool ret = false;
    if(flags & SDL_WINDOW_INPUT_FOCUS) {
        ret = true;
    }
    return ret;
}



void Renderer::drawRectangle(SDL_Rect rect, Color color)
{
    SDL_SetRenderDrawColor(renderer_, color.red(), color.green(), color.blue(), 255);
    SDL_RenderDrawRect(renderer_, &rect );
}

void Renderer::drawLine(Point start, Point end, Color color)
{
    SDL_SetRenderDrawColor(renderer_, color.red(), color.green(), color.blue(), 255);
    SDL_RenderDrawLine(renderer_, start.x(), start.y(), end.x(), end.y());
}




