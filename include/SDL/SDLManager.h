#ifndef SDLMANAGER_H
#define SDLMANAGER_H

#include <SDL.h>
#include "TextureManager.h"
//TODO Add necessary functions as I need them essentially

#define MOUSEBUTTONS 2
//Screen dimension constants TODO put stuff like this somewhere else
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;

enum {LEFT_MOUSEBUTTON, RIGHT_MOUSEBUTTON};

class SDLManager
{
    public:
        SDLManager();
        virtual ~SDLManager();

        bool Initialize();
        bool ReadEventQueue();
        void Start();   //TODO Needed?
        void ClearScreen();
        void Render();
        void Close();

        // Render Functions
        void RenderFillRectangle(int X, int Y, int Width, int Height, uint8_t R, uint8_t G, uint8_t B, uint8_t A);
        void RenderFillRectangle(SDL_Rect rectangle, uint8_t R, uint8_t G, uint8_t B, uint8_t A);
        void RenderOutlineRectangle(int X, int Y, int Width, int Height, uint8_t R, uint8_t G, uint8_t B, uint8_t A);
        void RenderOutlineRectangle(SDL_Rect rectangle, uint8_t R, uint8_t G, uint8_t B, uint8_t A);
		void RenderText(std::string text);
        void RenderLine();

        void RenderImage(const std::string& image, int x, int y, SDL_Rect* clip = 0);
        void RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip );

        const uint8_t* GetKeyBoardState() const {return SDL_GetKeyboardState(NULL);}
        bool* GetMouseState() const {return mousestate_;}

        SDL_Renderer* GetRenderer() {return renderer_;}
        SDL_Window* GetWindow() {return window_;}

    private:
        SDL_Window* window_;
        SDL_Renderer* renderer_;
        SDL_Event event;

        bool* mousestate_;
        TextureManager texturemanager_;
};

#endif // SDLMANAGER_H
