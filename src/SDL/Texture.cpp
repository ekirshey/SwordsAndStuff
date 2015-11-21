#include <SDL_image.h>
#include <iostream>
#include "../../include/SDL/Texture.h"

Texture::Texture()
{
	//Initialize
	texture_ = NULL;
	width_ = 0;
	height_ = 0;
}

Texture::Texture(std::string path, SDL_Renderer* renderer )
{
    //Initialize
	texture_ = NULL;
	width_ = 0;
	height_ = 0;

    LoadFromFile(path,renderer);
}

Texture::~Texture()
{
	//Deallocate
	Free();
}

void Texture::Free()
{
	//Free texture if it exists
	if( texture_ != NULL )
	{
		SDL_DestroyTexture( texture_ );
		texture_ = NULL;
		width_ = 0;
		height_ = 0;
	}
}

bool Texture::LoadFromFile( std::string path, SDL_Renderer* renderer )
{
	//Get rid of preexisting texture
	Free();

	//The final texture
	SDL_Texture* newtexture = NULL;

	//Load image at specified path
	std::cout << "Loading " << path.c_str() << std::endl;
	SDL_Surface* loadedsurface = IMG_Load( path.c_str() );
	if( loadedsurface == NULL )
		std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
	else
	{
		//Color key image
		SDL_SetColorKey( loadedsurface, SDL_TRUE, SDL_MapRGB( loadedsurface->format, 0xF0, 0x84, 0xFF ) );

		//Create texture from surface pixels
        newtexture = SDL_CreateTextureFromSurface( renderer, loadedsurface );
		if( newtexture == NULL )
		{
			std::cout << "Unable to create texture from " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			width_ = loadedsurface->w;
			height_ = loadedsurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedsurface );
	}

	//Return success
	texture_ = newtexture;
	return texture_ != NULL;

}


void Texture::Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderquad = { x, y, width_, height_ };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderquad.w = clip->w;
		renderquad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( renderer, texture_, clip, &renderquad );
}

void Texture::Render( SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderquad = { x, y, width_, height_ };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderquad.w = clip->w;
		renderquad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, texture_, clip, &renderquad, angle, center, flip );
}
