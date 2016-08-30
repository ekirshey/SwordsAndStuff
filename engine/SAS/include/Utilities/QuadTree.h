#pragma once
#include <vector>
#include <stdint.h>
#include <memory>
#include <SDL_rect.h>
#include "../Components/BoundingRectangleComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/CollisionComponent.h"
#include "SDLManager.h"
#include "UtilityStructures.h"
// QuadTree class designed for the ECS

enum QuadNodes { NORTHWEST, NORTHEAST, SOUTHWEST, SOUTHEAST };
class QuadTree
{
public:
	QuadTree(const SDL_Rect& boundary);
	QuadTree(const SDL_Rect& boundary, int capacity, int maxlevels);
	~QuadTree();

	bool Insert(QuadElement entity);
	void clear();
	void Draw(SAS_Rendering::SDLManager* sdlmanager);

	std::vector<QuadElement> QueryRange(const SDL_Rect& boundary);

private:
	static constexpr int nodecount_ = 4;

	int capacity_;
	int maxlevels_;


	// Private constructor, only the tree itself can assign levels
	// User defined trees start at level 0
	QuadTree(const SDL_Rect& boundary, int currentlevel, int capacity, int maxlevels);

	int currentlevel_;
	SDL_Rect boundary_;

	std::vector<QuadElement> entities_;

	// Children
	std::vector<std::unique_ptr<QuadTree>> nodes_;

	void Subdivide();
};

