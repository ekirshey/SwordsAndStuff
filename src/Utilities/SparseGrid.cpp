#include "..\..\include\Utilities\SparseGrid.h"
#include <iostream>
#include <algorithm>


SparseGrid::SparseGrid(const SDL_Rect& boundary, int cellwidth, int cellheight) :
	boundary_(boundary), cellwidth_(cellwidth), cellheight_(cellheight), gridwidth_(boundary_.w / cellwidth_), gridheight_(boundary_.h / cellheight_)
{
	if ((boundary_.w % cellwidth_ != 0) ||
		(boundary_.h % cellheight_ != 0))
	{
		std::cout << "Incorrect Dimensions" << std::endl;
	}

	grid_.resize(gridwidth_*gridheight_);
	
}


SparseGrid::~SparseGrid()
{
}

bool SparseGrid::Insert(QuadElement entity)
{
	bool inserted = false;

	SDL_Rect rect = entity.boundingrectangle->Rectangle();
	// Check each corner of the rectangle

	if (!SDL_HasIntersection(&rect, &boundary_))
		return false;

	int gridleft = (rect.x / cellwidth_);
	int gridright = ((rect.x + rect.w) / cellwidth_);
	int gridtop = (rect.y / cellheight_);
	int gridbottom = ((rect.y + rect.h) / cellheight_);

	if ((gridleft >= 0 && gridright < gridwidth_) &&
			(gridtop >= 0 && gridbottom < gridheight_))
	{
		if (gridleft != gridright && gridtop != gridbottom)
		{
			for (int j = gridtop; j <= gridbottom; j++)
			{
				for (int i = gridleft; i <= gridright; i++)
					grid_[(gridwidth_*j) + i].push_back(entity);
			}
		}
		else if (gridleft != gridright)
		{
			for (int i = gridleft; i <= gridright; i++)
				grid_[(gridwidth_*gridtop) + i].push_back(entity);
		}
		else if (gridtop != gridbottom)
		{
			for (int j = gridtop; j <= gridbottom; j++)
				grid_[(gridwidth_*j) + gridleft].push_back(entity);
		}
		else
			grid_[(gridwidth_*gridtop) + gridleft].push_back(entity);
	}

	return inserted;
}

void SparseGrid::clear()
{
	grid_.clear();
	grid_.resize(gridwidth_*gridheight_);
}

void SparseGrid::Draw(SDLManager* sdlmanager)
{
	for (int j = 0; j < gridheight_; j++)
	{
		for (int i = 0; i < gridwidth_; i++)
		{
			sdlmanager->RenderOutlineRectangle(SDL_Rect{ i*cellwidth_, j*cellheight_,cellwidth_,cellheight_ }, 0xFF, 0x00, 0x00, 0xFF);
			//for (int z = 0; z < grid_[(gridwidth_*j) + i].size(); z++)
			//	sdlmanager->RenderOutlineRectangle(grid_[(gridwidth_*j) + i].at(z).boundingrectangle->Rectangle(), 0x00, 0x00, 0x00, 0xFF);
		}
	}
}

std::vector<QuadElement> SparseGrid::QueryRange(const SDL_Rect& boundary) const
{
	std::vector<QuadElement> entitiesinrange;

	// Check each corner of the rectangle

	if (!SDL_HasIntersection(&boundary, &boundary_))
		return entitiesinrange;

	int gridleft = (boundary.x / cellwidth_);
	int gridright = ((boundary.x + boundary.w) / cellwidth_);
	int gridtop = (boundary.y / cellheight_);
	int gridbottom = ((boundary.y + boundary.h) / cellheight_);

	if ((gridleft >= 0 && gridright < gridwidth_) &&
			(gridtop >= 0 && gridbottom < gridheight_))
	{
		if (gridleft != gridright && gridtop != gridbottom)
		{
			for (int j = gridtop; j <= gridbottom; j++)
			{
				for (int i = gridleft; i <= gridright; i++)
					entitiesinrange.insert(entitiesinrange.end(), grid_[(gridwidth_*j) + i].begin(), grid_[(gridwidth_*j) + i].end());
			}
		}
		else if (gridleft != gridright)
		{
			for (int i = gridleft; i <= gridright; i++)
				entitiesinrange.insert(entitiesinrange.end(), grid_[(gridwidth_*gridtop) + i].begin(), grid_[(gridwidth_*gridtop) + i].end());
		}
		else if (gridtop != gridbottom)
		{
			for (int j = gridtop; j <= gridbottom; j++)
				entitiesinrange.insert(entitiesinrange.end(), grid_[(gridwidth_*j) + gridleft].begin(), grid_[(gridwidth_*j) + gridleft].end());
		}
		else
			entitiesinrange.insert(entitiesinrange.end(), grid_[(gridwidth_*gridtop) + gridleft].begin(), grid_[(gridwidth_*gridtop) + gridleft].end());
	}

	//EKNOTE: Try to make this better...
	// Remove duplicates
	std::sort(entitiesinrange.begin(), entitiesinrange.end());
	entitiesinrange.erase(std::unique(entitiesinrange.begin(), entitiesinrange.end()), entitiesinrange.end());

	return entitiesinrange;
}
