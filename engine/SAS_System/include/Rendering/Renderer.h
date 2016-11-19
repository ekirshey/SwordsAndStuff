#pragma once
#include <SDL.h>
#include "SystemDefines.h"
#include "TextureManager.h"

namespace SAS_System {

	class Renderer
	{
	public:
		DECLSPEC Renderer(int screenwidth, int screenheight);
		DECLSPEC ~Renderer();

		// Basic shapes add stream -1 option
		void DECLSPEC RenderFillRectangle(int X, int Y, int Width, int Height, SDL_Color color);
		void DECLSPEC RenderFillRectangle(SDL_Rect rectangle, SDL_Color color);
		void DECLSPEC RenderOutlineRectangle(int X, int Y, int Width, int Height, SDL_Color color);
		void DECLSPEC RenderOutlineRectangle(SDL_Rect rectangle, SDL_Color color);
		void DECLSPEC RenderLine(int x1, int y1, int x2, int y2, SDL_Color color);
		void DECLSPEC RenderText(const std::string& text, int x, int y, int fontsize, SDL_Color color, std::string fontpath);

		// Textures from image file
		void DECLSPEC RenderImage(const std::string& image, int x, int y, SDL_Rect* clip = 0);
		void DECLSPEC RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, 
			double angle, SDL_Point* center, SDL_RendererFlip flip);

		void SetRenderDrawBlendMode(SDL_BlendMode blendmode);
		void FillRenderingTarget(SDL_Color color);

		// Handle stream textures
		int DECLSPEC CreateTargetTexture(int width, int height);
		int DECLSPEC CreateTargetTexture(int width, int height, Uint32 format, int access);
		void DECLSPEC SetRenderTarget(int targettexture);
		void DECLSPEC DefaultRenderTarget();
		void DECLSPEC RenderTargetTexture(int targetid, int x, int y, SDL_Rect* clip = 0);
		void DECLSPEC ClearTargetTexture(int targetid);
		void SetTextureBlendMode(int targettexture, SDL_BlendMode blendmode);
		
		void DECLSPEC Update();
		void DECLSPEC ClearScreen();

		int DECLSPEC ScreenWidth() const { return _screenwidth; }
		int DECLSPEC ScreenHeight() const { return _screenheight; }
	
	private:
		int _screenwidth;
		int _screenheight;
		//SDL stuff requires pointer
		SDL_Window* _window;
		SDL_Renderer* _renderer;

		std::unique_ptr<TextureManager> _texturemanager;

		// Keep track of render target mainly for debugging
		int _rendertarget;
	};

}