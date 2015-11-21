#include <iostream>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "../../include/SDL/SDLManager.h"

SDLManager::SDLManager()
{
    window_ = NULL;
    renderer_ = NULL;

    mousestate_ = new bool[2];
    mousestate_[LEFT_MOUSEBUTTON] = false;
    mousestate_[RIGHT_MOUSEBUTTON] = false;
}

SDLManager::~SDLManager()
{
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

    delete mousestate_;
}

bool SDLManager::Initialize()
{
    bool returnvalue = true;
    std::cout << "Initialize SDL Manager" <<std::endl;

    	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL could not initialize! SDL_Error: %s\n" << SDL_GetError() << std::endl;
		returnvalue = false;
	}
	else
	{
        //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
			returnvalue = false;
		}

		//Create window
		window_ = SDL_CreateWindow( "Cannon Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		if( window_ == NULL )
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			returnvalue = false;
		}
		else
        {
            //Create renderer for window
			renderer_ = SDL_CreateRenderer( window_,  -1, SDL_RENDERER_ACCELERATED );
			if( renderer_ == NULL )
			{
				std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				returnvalue = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer_, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_MOD);
				SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
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
    
    SDL_RenderPresent( renderer_ );
}

void SDLManager::ClearScreen()
{
    //Clear The Screen
    SDL_SetRenderDrawColor(renderer_, 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(renderer_);
}

bool SDLManager::ReadEventQueue()
{
    bool returnvalue = false;

     //Handle events on queue
    while( SDL_PollEvent( &event ) != 0 )
    {
        //User requests quit
        if( event.type == SDL_QUIT )
            returnvalue = true;

        /* If a button on the mouse is pressed. */
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            /* If the left button was pressed. */
            if (event.button.button == SDL_BUTTON_LEFT)
                mousestate_[LEFT_MOUSEBUTTON] = true;
            if (event.button.button == SDL_BUTTON_RIGHT)
                mousestate_[RIGHT_MOUSEBUTTON] = true;

        }

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            /* If the left button was pressed. */
            if (event.button.button == SDL_BUTTON_LEFT)
                mousestate_[LEFT_MOUSEBUTTON] = false;
            if (event.button.button == SDL_BUTTON_RIGHT)
                mousestate_[RIGHT_MOUSEBUTTON] = false;

        }
    }

    return returnvalue;

}
void SDLManager::Close()
{
	//Destroy window
	SDL_DestroyRenderer( renderer_ );
	SDL_DestroyWindow( window_ );
	window_ = NULL;
	renderer_ = NULL;

	//Quit SDL subsystems
	//IMG_Quit();
	SDL_Quit();
}

// Render Functions
void SDLManager::RenderFillRectangle(int X, int Y, int Width, int Height, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    SDL_Rect rectangle = {X, Y, Width, Height};
    SDL_SetRenderDrawColor(renderer_, R,G,B,A);
    SDL_RenderFillRect( renderer_, &rectangle );
}

void SDLManager::RenderFillRectangle(SDL_Rect rectangle, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    SDL_SetRenderDrawColor(renderer_, R,G,B,A);
    SDL_RenderFillRect( renderer_, &rectangle );
}

void SDLManager::RenderOutlineRectangle(int X, int Y, int Width, int Height, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    SDL_Rect rectangle = {X, Y, Width, Height};
    SDL_SetRenderDrawColor(renderer_, R,G,B,A);
    SDL_RenderDrawRect( renderer_, &rectangle );
}

void SDLManager::RenderOutlineRectangle(SDL_Rect rectangle, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    SDL_SetRenderDrawColor(renderer_, R,G,B,A);
    SDL_RenderDrawRect( renderer_, &rectangle );
}

void SDLManager::RenderImage(const std::string& image, int x, int y, SDL_Rect* clip)
{
    //TODO ADD CULLING
    Texture* texture = texturemanager_.GetTexture(image);
    texture->Render(renderer_,x,y, clip);
}

void SDLManager::RenderImage(const std::string& image, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    Texture* texture = texturemanager_.GetTexture(image);
    texture->Render(renderer_,x,y, clip, angle, center, flip);
}

void SDLManager::RenderText(std::string text)
{
	// Debug FPS
	TTF_Font* font = TTF_OpenFont("..\\..\\..\\media\\font.ttf", 24);
	if (font == nullptr)
		std::cout << "Couldnt load font" << std::endl;
	else
	{
		SDL_Color White = { 255, 0, 0 };

		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), White);

		SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer_, surfaceMessage);

		SDL_Rect Message_rect; //create a rect
		Message_rect.x = 0;  //controls the rect's x coordinate 
		Message_rect.y = 0; // controls the rect's y coordinte
		Message_rect.w = surfaceMessage->w; // controls the width of the rect
		Message_rect.h = surfaceMessage->h; // controls the height of the rect

		SDL_RenderCopy(renderer_, Message, NULL, &Message_rect);

		TTF_CloseFont(font);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);
	}
}