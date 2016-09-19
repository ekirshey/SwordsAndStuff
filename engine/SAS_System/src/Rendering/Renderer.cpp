#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Renderer.h"

namespace SAS_System {

	Renderer::Renderer(int screenwidth, int screenheight) 
		: _screenwidth(screenwidth)
		, _screenheight(screenheight)
		, _window(nullptr)
		, _renderer(nullptr)
		, _texturemanager(nullptr)
		{
			uint32_t initstatus = SDL_WasInit(SDL_INIT_VIDEO);
			// SDL Needs to be initialized first, so check that
			if (!(initstatus & SDL_INIT_VIDEO)) {
				//Initialize SDL
				std::cerr << "SDL was not initialized! The SystemControl wrapper should of set it up" << std::endl;
				abort();
			}

			// Initialize rendering
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
				abort();
			}

			//Create window
			_window = SDL_CreateWindow("Cannon Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenwidth, _screenheight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
			if (_window == NULL)
			{
				std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			}
			else
			{
				//Create renderer for window
				_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

				if (_renderer == NULL)
				{
					std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
					abort();
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
					SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
						abort();
					}

					/// Everything initialized properly so build the TextureManager
					_texturemanager = std::make_unique<TextureManager>(_renderer);

				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1) {
					std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: %s\n" << TTF_GetError() << std::endl;
					abort();
				}
			}
	}

	Renderer::~Renderer() {
		TTF_Quit();
		IMG_Quit();

	}

	void Renderer::RenderFillRectangle(int X, int Y, int Width, int Height, SDL_Color color) {
		SDL_Rect rectangle = { X, Y, Width, Height };
		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(_renderer, &rectangle);

	}

	void Renderer::RenderFillRectangle(SDL_Rect rectangle, SDL_Color color) {	
		RenderFillRectangle(rectangle.x, rectangle.y, rectangle.w, rectangle.h, color);
	}

	void Renderer::RenderOutlineRectangle(int X, int Y, int Width, int Height, SDL_Color color) {
		SDL_Rect rectangle = { X, Y, Width, Height };
		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRect(_renderer, &rectangle);
	}
	
	void Renderer::RenderOutlineRectangle(SDL_Rect rectangle, SDL_Color color) {
		RenderOutlineRectangle(rectangle.x, rectangle.y, rectangle.w, rectangle.h, color);
	}

	void Renderer::RenderLine(int x1, int y1, int x2, int y2, SDL_Color color) {
		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
	}

	void Renderer::RenderTextToTarget(const std::string& text, int targetid, int x, int y, int fontsize, SDL_Color color, std::string fontpath) {
		Texture* desttexture = _texturemanager->GetTargetTexture(targetid);

		if (desttexture != nullptr) {
			desttexture->SetAsRenderTarget(_renderer);
			RenderText(text, x, y, fontsize, color, fontpath);
			SDL_SetRenderTarget(_renderer, NULL);
		}
	}

	void Renderer::RenderText(const std::string& text, int x, int y, int fontsize, SDL_Color color, std::string fontpath) {
		if (text.size() > 0) {
			TTF_Font* font = TTF_OpenFont(fontpath.c_str(), fontsize);
			if (font == nullptr)
				std::cout << "Couldnt load font" << std::endl;
			else
			{
				SDL_Color sdlcolor = {color.r, color.g, color.b, color.a};
				SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), sdlcolor);

				SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);

				SDL_Rect Message_rect; //create a rect
				Message_rect.x = x;  //controls the rect's x coordinate 
				Message_rect.y = y; // controls the rect's y coordinte
				Message_rect.w = surfaceMessage->w; // controls the width of the rect
				Message_rect.h = surfaceMessage->h; // controls the height of the rect

				SDL_RenderCopy(_renderer, Message, NULL, &Message_rect);

				TTF_CloseFont(font);
				SDL_FreeSurface(surfaceMessage);
				SDL_DestroyTexture(Message);
			}
		}
	}

	int Renderer::CreateTargetTexture(int width, int height) {
		return _texturemanager->CreateTargetTexture(width, height);
	}

	void Renderer::RenderToTargetTexture(const std::string& source, int targetid, int x, int y, SDL_Rect* clip) {
		Texture* desttexture = _texturemanager->GetTargetTexture(targetid);
		Texture* sourcetexture = _texturemanager->GetTexture(source);

		if (desttexture != nullptr) {
			desttexture->SetAsRenderTarget(_renderer);
			sourcetexture->Render(_renderer, x, y, clip);
			SDL_SetRenderTarget(_renderer, NULL);
		}
	}

	void Renderer::RenderToTargetTexture(const std::string& source, int targetid, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
		Texture* desttexture = _texturemanager->GetTargetTexture(targetid);
		Texture* sourcetexture = _texturemanager->GetTexture(source);

		if (desttexture != nullptr) {
			desttexture->SetAsRenderTarget(_renderer);
			sourcetexture->Render(_renderer, x, y, clip, angle, center, flip);
			SDL_SetRenderTarget(_renderer, NULL);
		}
	}

	void Renderer::ClearTargetTexture(int targetid) {
		Texture* desttexture = _texturemanager->GetTargetTexture(targetid);

		if (desttexture != nullptr) {
			desttexture->SetAsRenderTarget(_renderer);
			SDL_RenderClear(_renderer);
			SDL_SetRenderTarget(_renderer, NULL);
		}
	}

	void Renderer::RenderTargetTexture(int targetid, int x, int y, SDL_Rect* clip) {
		Texture* texture = _texturemanager->GetTargetTexture(targetid);
		if ( texture != nullptr)
			texture->Render(_renderer, x, y, clip);
	}

	void Renderer::RenderTargetTexture(int targetid, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
		Texture* texture = _texturemanager->GetTargetTexture(targetid);
		if ( texture != nullptr)
			texture->Render(_renderer, x, y, clip, angle, center, flip);
	}

	void Renderer::RenderImage(const std::string& image, int x, int y, SDL_Rect* clip) {
		Texture* texture = _texturemanager->GetTexture(image);
		texture->Render(_renderer, x, y, clip);
	}

	void Renderer::RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
		Texture* texture = _texturemanager->GetTexture(image);
		texture->Render(_renderer, x, y, clip, angle, center, flip);
	}

	void Renderer::ClearScreen() {
		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(_renderer);
	}

	void Renderer::Update() {
		SDL_RenderPresent(_renderer);
	}

}
