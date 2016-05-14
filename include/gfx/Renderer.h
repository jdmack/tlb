#ifndef TLB_GFX_RENDERER_H_
#define TLB_GFX_RENDERER_H_

#include "GL/glew.h"
#include "GL/glu.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "Constants.h"
#include "Color.h"
#include "Point.h"
#include "math/Vector2i.h"

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
const bool kFullscreen = false;

class Renderer
{
    private:
        int screenWidth_;
        int screenHeight_;

        SDL_Window * window_;
        SDL_Renderer * renderer_;
        SDL_GLContext context_;
        Camera * camera_;

        GLuint programID_;

    public:
        Renderer();

        // accessors
        int screenWidth() const { return screenWidth_; }
        int screenHeight() const { return screenHeight_; }
        SDL_Window * window() const { return window_; }
        SDL_Renderer * renderer() const { return renderer_; }
        SDL_GLContext context() const { return context_;}
        Camera * camera() const { return camera_; }
        GLuint programID() { return programID_; }

        bool init();
        void update();
        void clear();
        void clear(Color color);
        void cleanUp();

        void renderTexture(SDL_Texture * source, SDL_Rect * offset, SDL_Rect * clip = nullptr);
        void renderTextureFrame(SDL_Texture * source, Frame * frame, SDL_Rect * offset, SDL_Rect * clip = nullptr);
        void renderTextureRotate(SDL_Texture * source, SDL_Rect * offset, SDL_Rect * clip , double angle);
        void applySurface(SDL_Surface * source, SDL_Surface * destination, SDL_Rect * offset, SDL_Rect * clip = nullptr);

        void drawRectangle(SDL_Rect rect, Color color);
        void drawLine(Point start, Point end, Color color);

        SDL_Surface * loadImage(std::string);
        SDL_Surface * loadImageAlpha(std::string);
        SDL_Texture * loadTexture(std::string);
        SDL_Texture * loadTextureAlpha(std::string);

        void drawLifeBar(Entity * entity, Frame * frame = nullptr);

        void warpMouse(const Vector2i position);
        void showCursor(bool show);

        bool windowFocused();

        bool initShader();
        void printProgramLog(GLuint program);
        void printShaderLog(GLuint program);

};

#endif
