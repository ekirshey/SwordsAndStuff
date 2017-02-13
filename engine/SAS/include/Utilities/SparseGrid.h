#pragma once
#include <vector>
#include <stdint.h>
#include <memory>
#include "Components/BoundingRectangleComponent.h"
#include "Components/PositionComponent.h"
#include "Components/CollisionComponent.h"
#include "UtilityStructures.h"
#include "Renderer.h"

class SparseGrid
{
public:
	SparseGrid(const SDL_Rect& boundary, int cellwidth, int cellheight);
	~SparseGrid();

	bool Insert(const QuadElement& entity);
	void clear();
	void Draw(SAS_System::Renderer* renderer);

	void QueryRange(const SDL_Rect& boundary, std::vector<QuadElement>& entitiesinrange) const;
private:
	SDL_Rect boundary_;

	// in pixels
	int cellwidth_;
	int cellheight_;

	// In "cells"
	int gridwidth_;
	int gridheight_;

	std::vector<QuadElements> grid_;
};

