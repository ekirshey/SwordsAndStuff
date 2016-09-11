#pragma once
#include <memory>
#include <string>
#include "Input.h"
#include "SystemDefines.h"

namespace SAS_System{
	class Renderer;
}
namespace SAS_System {

	//RAII Wrapper around SDL, possibly OpenGL in the future
	class SystemControl {
		public:
			DECLSPEC SystemControl(int screenwidth, int screenheight);
			DECLSPEC ~SystemControl();

			void DECLSPEC ReadInput(Input* input);
			
			// Rendering functions
			void DECLSPEC RenderFillRectangle(int X, int Y, int Width, int Height, SDL_Color color);
			void DECLSPEC RenderFillRectangle(SDL_Rect rectangle, SDL_Color color);
			void DECLSPEC RenderOutlineRectangle(int X, int Y, int Width, int Height, SDL_Color color);
			void DECLSPEC RenderOutlineRectangle(SDL_Rect rectangle, SDL_Color color);
			void DECLSPEC RenderLine(int x1, int y1, int x2, int y2, SDL_Color color);
			void DECLSPEC RenderText(const std::string& text, int x, int y, int fontsize = 12, SDL_Color color = { 0,0,0,255 }, std::string fontpath = "..\\..\\..\\media\\font.ttf");
			void DECLSPEC RenderImage(const std::string& image, int x, int y, SDL_Rect* clip = 0);
			void DECLSPEC RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

			void DECLSPEC Update();
			
			int DECLSPEC ScreenWidth() const;
			int DECLSPEC ScreenHeight() const;
			
			int DECLSPEC CurrentTicks();

		private:
			std::unique_ptr<Renderer> _renderer;

	};

}