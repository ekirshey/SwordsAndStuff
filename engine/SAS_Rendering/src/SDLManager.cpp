#include <iostream>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "SDLManager.h"

namespace SAS_Rendering {
	SDLManager::SDLManager() : window_(NULL), renderer_(NULL), activestream_(-1)
	{
		for (int i = 0; i < NUM_MOUSE_STATES; i++)
			mousestate_.push_back(false);
	}

	SDLManager::~SDLManager()
	{
		//Quit SDL subsystems
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	void log(void* userdata, int category, SDL_LogPriority priority, const char* message) {
		std::cout << "Log : " << message << std::endl;
	}

	bool SDLManager::Initialize()
	{
		bool returnvalue = true;
		std::cout << "Initialize SDL Manager" << std::endl;
		//Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError() << std::endl;
			returnvalue = false;
		}
		else
		{
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			{
				std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
				returnvalue = false;
			}

			//Create window
			window_ = SDL_CreateWindow("Cannon Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
			if (window_ == NULL)
			{
				std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
				returnvalue = false;
			}
			else
			{
				//Create renderer for window
				renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);

				if (renderer_ == NULL)
				{
					std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
					returnvalue = false;
				}
				else
				{
					//Initialize renderer color
					SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
					SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
					SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags))
					{
						std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
						returnvalue = false;
					}

					texturemanager_.SetRenderer(renderer_);
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());

			}
		}

		return returnvalue;
	}

	void SDLManager::Start()
	{
		std::cout << "Start SDL Timer and such" << std::endl;
	}

	void SDLManager::Render()
	{
		//Update screen

		SDL_RenderPresent(renderer_);
	}

	void SDLManager::ClearScreen()
	{
		//Clear The Screen
		SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer_);
	}

	bool SDLManager::ReadEventQueue()
	{
		bool returnvalue = false;
		//SDL_PumpEvents();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			// handle your event here
			switch (event.type) {
			case SDL_QUIT:
				/* Quit */
				return true;
				break;
			case SDL_TEXTINPUT:
				/* Add new text onto the end of our text */
				if (activestream_ >= 0) {
					if (recordstreams_[activestream_].AtMaxLength()) {
						recordstreams_[activestream_].stream->append(event.text.text);
					}
				}
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_BACKSPACE) {
					if (activestream_ >= 0) {
						if (recordstreams_[activestream_].stream->size() > 0) {
							recordstreams_[activestream_].stream->pop_back();
						}
					}
				}
				break;
			}
		}


		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			if (mousestate_[LEFT_PRESSED] || mousestate_[LEFT_MOUSEBUTTON_HELD]) {
				mousestate_[LEFT_MOUSEBUTTON_HELD] = true;
				mousestate_[LEFT_PRESSED] = false;
			}
			else {
				mousestate_[LEFT_PRESSED] = true;
				mousestate_[LEFT_MOUSEBUTTON_HELD] = false;
			}
		}
		else {
			mousestate_[LEFT_MOUSEBUTTON_HELD] = false;
			mousestate_[LEFT_PRESSED] = false;
		}

		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			if (mousestate_[RIGHT_PRESSED] || mousestate_[RIGHT_MOUSEBUTTON_HELD]) {
				mousestate_[RIGHT_MOUSEBUTTON_HELD] = true;
				mousestate_[RIGHT_PRESSED] = false;
			}
			else {
				mousestate_[RIGHT_PRESSED] = true;
				mousestate_[RIGHT_MOUSEBUTTON_HELD] = false;
			}
		}
		else {
			mousestate_[RIGHT_MOUSEBUTTON_HELD] = false;
			mousestate_[RIGHT_PRESSED] = false;
		}

		return returnvalue;

	}
	void SDLManager::Close()
	{
		//Destroy window
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);
		window_ = NULL;
		renderer_ = NULL;

		//Quit SDL subsystems
		//IMG_Quit();
		SDL_Quit();
	}

	// Render Functions
	void SDLManager::RenderFillRectangle(int X, int Y, int Width, int Height, SDL_Color color) {
		RenderFillRectangle(X, Y, Width, Height, color.r, color.g, color.b, color.a);
	}

	void SDLManager::RenderFillRectangle(SDL_Rect rectangle, SDL_Color color) {
		RenderFillRectangle(rectangle.x, rectangle.y, rectangle.w, rectangle.h, color.r, color.g, color.b, color.a);
	}

	void SDLManager::RenderOutlineRectangle(int X, int Y, int Width, int Height, SDL_Color color) {
		RenderOutlineRectangle(X, Y, Width, Height, color.r, color.g, color.b, color.a);
	}

	void SDLManager::RenderOutlineRectangle(SDL_Rect rectangle, SDL_Color color) {
		RenderOutlineRectangle(rectangle.x, rectangle.y, rectangle.w, rectangle.h, color.r, color.g, color.b, color.a);;
	}

	void SDLManager::RenderLine(int x1, int y1, int x2, int y2, SDL_Color color) {
		RenderLine(x1, y1, x2, y2, color.r, color.g, color.b, color.a);
	}

	void SDLManager::RenderFillRectangle(int X, int Y, int Width, int Height, Uint8 R, Uint8 G, Uint8 B, Uint8 A)
	{
		SDL_Rect rectangle = { X, Y, Width, Height };
		SDL_SetRenderDrawColor(renderer_, R, G, B, A);
		SDL_RenderFillRect(renderer_, &rectangle);
	}

	void SDLManager::RenderFillRectangle(SDL_Rect rectangle, Uint8 R, Uint8 G, Uint8 B, Uint8 A)
	{
		SDL_SetRenderDrawColor(renderer_, R, G, B, A);
		SDL_RenderFillRect(renderer_, &rectangle);
	}

	void SDLManager::RenderOutlineRectangle(int X, int Y, int Width, int Height, Uint8 R, Uint8 G, Uint8 B, Uint8 A)
	{
		SDL_Rect rectangle = { X, Y, Width, Height };
		SDL_SetRenderDrawColor(renderer_, R, G, B, A);
		SDL_RenderDrawRect(renderer_, &rectangle);
	}

	void SDLManager::RenderOutlineRectangle(SDL_Rect rectangle, Uint8 R, Uint8 G, Uint8 B, Uint8 A)
	{
		SDL_SetRenderDrawColor(renderer_, R, G, B, A);
		SDL_RenderDrawRect(renderer_, &rectangle);
	}

	void SDLManager::RenderLine(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A)
	{
		SDL_SetRenderDrawColor(renderer_, R, G, B, A);
		SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
	}

	void SDLManager::RenderImage(const std::string& image, int x, int y, SDL_Rect* clip)
	{
		//TODO ADD CULLING
		Texture* texture = texturemanager_.GetTexture(image);
		texture->Render(renderer_, x, y, clip);
	}

	void SDLManager::RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
	{
		Texture* texture = texturemanager_.GetTexture(image);
		texture->Render(renderer_, x, y, clip, angle, center, flip);
	}

	void SDLManager::RecordInput(int maxcharacters, std::string* stream) {
		activestringlength_ = 0;

		bool existingstream = false;
		for (int i = 0; i < recordstreams_.size(); i++) {
			if (recordstreams_[i].stream == stream) {
				existingstream = true;
				activestream_ = i;
			}
		}

		if (!existingstream) {
			recordstreams_.push_back(RecordStream(stream, maxcharacters));
			activestream_ = recordstreams_.size() - 1;
		}
	}

	void SDLManager::StopInput(std::string* stream) {
		for (int i = 0; i < recordstreams_.size(); i++) {
			if (recordstreams_[i].stream == stream) {
				recordstreams_.erase(recordstreams_.begin() + i);
			}
		}
	}

	void SDLManager::RenderText(std::string text, int x, int y, int fontsize, SDL_Color color, std::string fontpath)
	{
		if (text.size() > 0) {
			TTF_Font* font = TTF_OpenFont(fontpath.c_str(), fontsize);
			if (font == nullptr)
				std::cout << "Couldnt load font" << std::endl;
			else
			{
				SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), color);

				SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer_, surfaceMessage);

				SDL_Rect Message_rect; //create a rect
				Message_rect.x = x;  //controls the rect's x coordinate 
				Message_rect.y = y; // controls the rect's y coordinte
				Message_rect.w = surfaceMessage->w; // controls the width of the rect
				Message_rect.h = surfaceMessage->h; // controls the height of the rect

				activestringlength_ = surfaceMessage->w;

				SDL_RenderCopy(renderer_, Message, NULL, &Message_rect);

				TTF_CloseFont(font);
				SDL_FreeSurface(surfaceMessage);
				SDL_DestroyTexture(Message);
			}
		}
		else
			activestringlength_ = 0;
	}
}