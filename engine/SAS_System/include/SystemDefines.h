#pragma once
#include <cstdint>
#include <SDL.h>

namespace SAS_System {

#if defined(__WIN32__)
	#define DECLSPEC __declspec(dllexport)
#else
	#define DECLSPEC
#endif
	
	//using SAS_Rect = SDL_Rect;
	//using SAS_Point = SDL_Point;
}
