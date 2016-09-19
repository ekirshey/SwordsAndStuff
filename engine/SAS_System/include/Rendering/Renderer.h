#pragma once
#include <SDL.h>
#include "SystemDefines.h"
#include "TextureManager.h"

namespace SAS_System {

	class Renderer
	{
	public:
		// I need to decide what to really do with this
		typedef enum
		{
			SAS_FLIP_NONE = 0x00000000,     /**< Do not flip */
			SAS_FLIP_HORIZONTAL = 0x00000001,    /**< flip horizontally */
			SAS_FLIP_VERTICAL = 0x00000002     /**< flip vertically */
		} SAS_RendererFlip;

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

		// Handle stream textures
		int DECLSPEC CreateTargetTexture(int width, int height);
		void DECLSPEC RenderToTargetTexture(const std::string& source, int targetid, int x, int y, SDL_Rect* clip = 0);
		void DECLSPEC RenderToTargetTexture(const std::string& source, int targetid, int x, int y, SDL_Rect* clip, 
			double angle, SDL_Point* center, SDL_RendererFlip flip);
		void DECLSPEC RenderTargetTexture(int targetid, int x, int y, SDL_Rect* clip = 0);
		void DECLSPEC RenderTargetTexture(int targetid, int x, int y, SDL_Rect* clip, 
			double angle, SDL_Point* center, SDL_RendererFlip flip);
		void DECLSPEC RenderTextToTarget(const std::string& text, int targetid, int x, int y, int fontsize, SDL_Color color, std::string fontpath);
		void DECLSPEC ClearTargetTexture(int targetid);

		void DECLSPEC Update();
		void DECLSPEC ClearScreen();

		int DECLSPEC ScreenWidth() const { return _screenwidth; }
		int DECLSPEC ScreenHeight() const { return _screenheight; }
	
	private:
		int _screenwidth;
		int _screenheight;
		SDL_Window* _window;
		SDL_Renderer* _renderer;

		std::unique_ptr<TextureManager> _texturemanager;


	};

}