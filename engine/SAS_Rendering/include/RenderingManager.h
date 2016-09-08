#pragma once

#include <iostream>
#include <SDL.h>
#include "TextureManager.h"
//TODO Add necessary functions as I need them essentially

namespace SAS_Rendering {
#define MOUSEBUTTONS 2
#define NUM_MOUSE_STATES 4

	//Screen dimension constants TODO put stuff like this somewhere else
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 640;

	enum {
		LEFT_MOUSEBUTTON_HELD,
		RIGHT_MOUSEBUTTON_HELD,
		LEFT_PRESSED,
		RIGHT_PRESSED
	};

	class RenderingManager
	{
	public:
		RenderingManager();
		~RenderingManager();

		// implicit
		RenderingManager(const RenderingManager&) = delete;
		RenderingManager& operator=(const RenderingManager&) = delete;

		bool Initialize();
		bool ReadEventQueue();
		void Start();   //TODO Needed?
		void ClearScreen();
		void Render();
		void Close();

		// Render Functions
		void RenderFillRectangle(int X, int Y, int Width, int Height, SDL_Color color);
		void RenderFillRectangle(SDL_Rect rectangle, SDL_Color color);
		void RenderOutlineRectangle(int X, int Y, int Width, int Height, SDL_Color color);
		void RenderOutlineRectangle(SDL_Rect rectangle, SDL_Color color);
		void RenderLine(int x1, int y1, int x2, int y2, SDL_Color color);

		void RenderFillRectangle(int X, int Y, int Width, int Height, Uint8 R, Uint8 G, Uint8 B, Uint8 A);
		void RenderFillRectangle(SDL_Rect rectangle, Uint8 R, Uint8 G, Uint8 B, Uint8 A);
		void RenderOutlineRectangle(int X, int Y, int Width, int Height, Uint8 R, Uint8 G, Uint8 B, Uint8 A);
		void RenderOutlineRectangle(SDL_Rect rectangle, Uint8 R, Uint8 G, Uint8 B, Uint8 A);
		void RenderLine(int x1, int y1, int x2, int y2, Uint8 R, Uint8 G, Uint8 B, Uint8 A);

		void RenderText(std::string text, int x, int y, int fontsize = 12, SDL_Color color = { 0,0,0,255 }, std::string fontpath = "..\\..\\..\\media\\font.ttf");

		void RenderImage(const std::string& image, int x, int y, SDL_Rect* clip = 0);
		void RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

		const uint8_t* GetKeyBoardState() const { return SDL_GetKeyboardState(NULL); }
		const std::vector<bool>& GetMouseState() const { return mousestate_; }

		SDL_Renderer* GetRenderer() { return renderer_; }
		SDL_Window* GetWindow() { return window_; }

		void RecordInput(int maxcharacters, std::string* stream);
		void StopInput(std::string* stream);

		int ActiveStringLength() const { return activestringlength_; }

	private:
		Renderer* renderer;	// Polymorphic wrapper type
		SDL_Window* window_;
		SDL_Renderer* renderer_;
		SDL_Event event;

		std::vector<bool> mousestate_;
		TextureManager texturemanager_;

		std::vector<RecordStream> recordstreams_;
		int activestringlength_;
		int activestream_;

	};

}