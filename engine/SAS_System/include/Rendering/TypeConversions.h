#pragma once
#include "Renderer.h"
#include "Geometry.h"

namespace SAS_System {
	SDL_Point SASPointToSDLPoint(const SAS_Utils::Point& p) {
		return SDL_Point{ p.x(), p.y() };
	}
}
