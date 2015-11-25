#pragma once
#include <vector>
#include <stdint.h>
#include <memory>
#include <SDL_rect.h>
#include "../Components/BoundingRectangleComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/CollisionComponent.h"
#include "UtilityStructures.h"
#include "../SDL/SDLManager.h"

class SparseGrid
{
public:
	SparseGrid(const SDL_Rect& boundary, int cellwidth, int cellheight);
	~SparseGrid();

	bool Insert(QuadElement entity);
	void clear();
	void Draw(SDLManager* sdlmanager);

	std::vector<QuadElement> QueryRange(const SDL_Rect& boundary) const;
private:
	SDL_Rect boundary_;

	// in pixels
	int cellwidth_;
	int cellheight_;

	// In "cells"
	int gridwidth_;
	int gridheight_;

	std::vector<std::vector<QuadElement>> grid_;
};

