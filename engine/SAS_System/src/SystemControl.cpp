#include <iostream>
#include <SDL.h>
#include "SystemControl.h"
#include "Renderer.h"

namespace SAS_System {

	
	SystemControl::SystemControl(int screenwidth, int screenheight) {
		// Initialize the base SDL. The Renderer will take care of the rest
		std::cout << "Initialize SAS System..." << std::endl;
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError() << std::endl;
		}
		else
		{
			_renderer = std::make_unique<Renderer>(screenwidth, screenheight);
		}

	}

	SystemControl::~SystemControl() {
		SDL_Quit();
	}

	void SystemControl::ReadInput(Input* input) {

	}

	// Rendering functions
	void SystemControl::RenderFillRectangle(int X, int Y, int Width, int Height, SDL_Color color) {
		_renderer->RenderFillRectangle(X, Y, Width, Height, color);
	}

	void SystemControl::RenderFillRectangle(SDL_Rect rectangle, SDL_Color color) {
		_renderer->RenderFillRectangle(rectangle, color);
	}

	void SystemControl::RenderOutlineRectangle(int X, int Y, int Width, int Height, SDL_Color color) {
		_renderer->RenderOutlineRectangle(X, Y, Width, Height, color);
	}

	void SystemControl::RenderOutlineRectangle(SDL_Rect rectangle, SDL_Color color) {
		_renderer->RenderOutlineRectangle(rectangle, color);
	}

	void SystemControl::RenderLine(int x1, int y1, int x2, int y2, SDL_Color color) {
		_renderer->RenderLine(x1, y1, x2, y2, color);
	}
	
	void SystemControl::RenderText(const std::string& text, int x, int y, int fontsize, SDL_Color color, std::string fontpath) {
		_renderer->RenderText(text, x, y, fontsize, color, fontpath);
	}
	
	void SystemControl::RenderImage(const std::string& image, int x, int y, SDL_Rect* clip ) {
		_renderer->RenderImage(image, x, y, clip);
	}
	
	void SystemControl::RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
		_renderer->RenderImage(image, x, y, clip, angle, center, flip);
	}


	void SystemControl::Update() {
		_renderer->Update();
	}

	int SystemControl::CurrentTicks() {
		return SDL_GetTicks();
	}

	int SystemControl::ScreenWidth() const { return _renderer->ScreenWidth(); }
	int SystemControl::ScreenHeight() const { return _renderer->ScreenHeight(); }

}