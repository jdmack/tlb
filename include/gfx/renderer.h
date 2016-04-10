#ifndef TLB_GFX_RENDERER_H_
#define TLB_GFX_RENDERER_H_

#include "GL/glew.h"
#include "GL/glu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "constants.h"
#include "color.h"
#include "point.h"

class GameObject;
class Entity;
class DebugFrame;
class Camera;
class Frame;

/* Renderer Attributes */
//const int kRendererWidth        = 800;
//const int kRendererHeight       = 600;

const Color kDefaultClearColor = kColorWhite;
//const Color kDefaultClearColor = kColorBlack;

const bool kDebugFrame = false;

class Renderer
{
    private:
        SDL_Window * window_;
        SDL_Renderer * renderer_;
        SDL_GLContext context_;
        Camera * camera_;

        GLuint programID_;

    public:
        Renderer();

        // accessors
        SDL_Window * window() const { return window_; }
        SDL_Renderer * renderer() const { return renderer_; }
        SDL_GLContext context() const { return context_;}
        Camera * camera() const { return camera_; }
        GLuint programID() { return programID_; }

        // mutators
        void set_camera(Camera * camera) { camera_ = camera; }

        bool init();
        void update();
        void clear();
        void clear(Color color);
        void clean_up();
        void init_object(GameObject * object);

        void render_texture(SDL_Texture * source, SDL_Rect * offset, SDL_Rect * clip = nullptr);
        void render_texture_frame(SDL_Texture * source, Frame * frame, SDL_Rect * offset, SDL_Rect * clip = nullptr);
        void render_texture_rotate(SDL_Texture * source, SDL_Rect * offset, SDL_Rect * clip , double angle);
        void apply_surface(SDL_Surface * source, SDL_Surface * destination, SDL_Rect * offset, SDL_Rect * clip = nullptr);

        void draw_rectangle(SDL_Rect rect, Color color);
        void draw_line(Point start, Point end, Color color);


        SDL_Surface * load_image(std::string);
        SDL_Surface * load_image_alpha(std::string);
        SDL_Texture * load_texture(std::string);
        SDL_Texture * load_texture_alpha(std::string);

        void draw_life_bar(Entity * entity, Frame * frame = nullptr);

        bool initShader();
        void printProgramLog(GLuint program);
        void printShaderLog(GLuint program);

};

#endif