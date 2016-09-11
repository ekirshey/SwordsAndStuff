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

		Renderer(int screenwidth, int screenheight);
		~Renderer();

		void RenderFillRectangle(int X, int Y, int Width, int Height, SDL_Color color);
		void RenderFillRectangle(SDL_Rect rectangle, SDL_Color color);
		void RenderOutlineRectangle(int X, int Y, int Width, int Height, SDL_Color color);
		void RenderOutlineRectangle(SDL_Rect rectangle, SDL_Color color);
		void RenderLine(int x1, int y1, int x2, int y2, SDL_Color color);
		void RenderText(const std::string& text, int x, int y, int fontsize, SDL_Color color, std::string fontpath);
		void RenderImage(const std::string& image, int x, int y, SDL_Rect* clip = 0);
		void RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

		void Update();

		int ScreenWidth() const { return _screenwidth; }
		int ScreenHeight() const { return _screenheight; }
	
	private:
		int _screenwidth;
		int _screenheight;
		SDL_Window* _window;
		SDL_Renderer* _renderer;

		std::unique_ptr<TextureManager> _texturemanager;


	};

}