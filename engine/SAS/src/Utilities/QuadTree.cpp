#include "..\..\include\Utilities\QuadTree.h"
#include <algorithm> 
#include <iostream>

QuadTree::QuadTree(const SDL_Rect& boundary) : boundary_(boundary), currentlevel_(0), capacity_(4), maxlevels_(4)
{
	nodes_.resize(nodecount_);
}

QuadTree::QuadTree(const SDL_Rect& boundary, int capacity, int maxlevels) : boundary_(boundary), currentlevel_(0), 
	capacity_(capacity), maxlevels_(maxlevels)
{
	nodes_.resize(nodecount_);
}

QuadTree::QuadTree(const SDL_Rect& boundary, int currentlevel, int capacity, int maxlevels) : 
	boundary_(boundary), currentlevel_(currentlevel), capacity_(capacity), maxlevels_(maxlevels)
{
	nodes_.resize(nodecount_);
}

QuadTree::~QuadTree()
{
}


bool QuadTree::Insert(QuadElement entity)
{

	if ( ( !SDL_HasIntersection(&boundary_, &entity.boundingrectangle->Rectangle())) || 
		(entity.boundingrectangle->width_ * entity.boundingrectangle->height_) >  (boundary_.w * boundary_.h))
		return false;
	
	if (nodes_[NORTHWEST].get() != nullptr)
	{
		for (int i = 0; i < nodecount_; i++)
			nodes_[i]->Insert(entity);
	}
	else
	{
		entities_.push_back(entity);

		if ( (entities_.size() <= capacity_) || ( currentlevel_+1 > maxlevels_) )
			return true;
		
		Subdivide();

		for (int i = 0; i < nodecount_; i++)
		{
			for (int j = 0; j < entities_.size(); j++)
				nodes_[i]->Insert(entities_[j]);
		}
		entities_.clear();
		
		return true;
	}

	return false;

}

void QuadTree::Subdivide()
{
	nodes_[NORTHWEST] = std::unique_ptr<QuadTree>(new QuadTree(SDL_Rect{ boundary_.x,
																		 boundary_.y, 
																		 boundary_.w / 2, 
																		 boundary_.h / 2 } , currentlevel_ + 1, capacity_, maxlevels_));

	nodes_[NORTHEAST] = std::unique_ptr<QuadTree>(new QuadTree(SDL_Rect{ boundary_.x + (boundary_.w / 2),
																		 boundary_.y, 
																		 boundary_.w / 2, 
																		 boundary_.h / 2 } , currentlevel_ + 1, capacity_, maxlevels_));

	nodes_[SOUTHWEST] = std::unique_ptr<QuadTree>(new QuadTree(SDL_Rect{ boundary_.x,
																		 boundary_.y + (boundary_.h / 2), 
																		 boundary_.w / 2, 
																		 boundary_.h / 2 } , currentlevel_ + 1, capacity_, maxlevels_));

	nodes_[SOUTHEAST] = std::unique_ptr<QuadTree>(new QuadTree(SDL_Rect{ boundary_.x + (boundary_.w / 2),
																		 boundary_.y + (boundary_.h / 2),
																		 boundary_.w / 2,
																		 boundary_.h / 2 } , currentlevel_ + 1, capacity_, maxlevels_));
}

void QuadTree::clear()
{
	//EKTEMP idk what happens if you call reset on a unique_ptr with unique_ptrs
	entities_.clear();
	for (int i = 0; i < nodecount_; i++)
		nodes_[i].reset();
}

void QuadTree::Draw(SAS_System::Renderer* renderer)
{
	renderer->RenderOutlineRectangle(boundary_, SDL_Color{ 0xFF, 0x00, 0x00, 0xFF });
/*
	for (int i = 0; i < entities_.size(); i++)
	{
		//std::cout << entities_[i].entityid << " ";
		sdlmanager->RenderOutlineRectangle(entities_[i].boundingrectangle->Rectangle(), 0x00, 0x00, 0x00, 0xFF);
	}
*/
	if (nodes_[NORTHWEST] != nullptr)
	{
		for (int i = 0; i < nodecount_; i++)
			nodes_[i]->Draw(renderer);
	}
}

std::vector<QuadElement> QuadTree::QueryRange(const SDL_Rect& boundary)
{
	std::vector<QuadElement> entitiesinrange;

	if (!SDL_HasIntersection(&boundary_, &boundary))
		return entitiesinrange;

	if (nodes_[NORTHWEST].get() != nullptr)
	{
		std::vector<QuadElement> nodeentities;
		for (int i = 0; i < nodecount_; i++)
		{
			nodeentities = nodes_[i]->QueryRange(boundary);
			if (nodeentities.size() > 0)
			{
				entitiesinrange.insert(entitiesinrange.end(), nodeentities.begin(), nodeentities.end());
				nodeentities.clear();
			}
		}
	}
	else
		entitiesinrange = entities_;

	
	return entitiesinrange;
}