#pragma once

#include <SDL.h>
#include <string>

namespace SAS_System {
	class Texture
	{
	public:
		//Initializes variables
		Texture();
		Texture(std::string path, SDL_Renderer* renderer);
		Texture(int width, int height, SDL_Renderer* renderer);
		
			//Deallocates memory
		~Texture();

		// Builds a blank "stream" texture
		bool CreateStreamTexture(int width, int height, SDL_Renderer* renderer);

		//Loads image at specified path
		bool LoadFromFile(std::string path, SDL_Renderer* renderer);

		//Deallocates texture
		void Free();

		//Renders texture at given point
		void Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);
		void Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

		// Set as render target, for if being streamed to
		void SetAsRenderTarget(SDL_Renderer* renderer);

		//Gets image dimensions
		int Width() const { return width_; }
		int Height() const { return height_; }

		SDL_Texture* GetTexture() const { return texture_; }

	private:
		//The actual hardware texture
		SDL_Texture* texture_;

		//Image dimensions
		int width_;
		int height_;
	};

}