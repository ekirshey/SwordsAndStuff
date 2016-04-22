#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include "../../include/GameWorld/TileMap.h"
#include "../../include/SDL/SDLManager.h"
#include "../../include/GameWorld/Tile.h"


TileMap::TileMap(int mapwidth, int mapheight, int tilesize, std::string filetoload, const std::vector<Tile> &uniquetiles) :
     mapwidth_(mapwidth), mapheight_(mapheight), tilesize_(tilesize)
{
    std::cout << mapwidth_ << " " << mapheight_ << std::endl;
    tilemap_.resize(mapwidth_*mapheight_);

    if ( !LoadMapFromFile(filetoload, uniquetiles) )
        std::cout << "Failed to Load Tile Map: Cascading errors Someday " << std::endl;
}

TileMap::TileMap(int mapwidth, int mapheight, int tilesize, const std::vector<Tile> &uniquetiles) :
     mapwidth_(mapwidth), mapheight_(mapheight), tilesize_(tilesize)
{
    std::cout << mapwidth_ << " " << mapheight_ << std::endl;
    tilemap_.resize(mapwidth_*mapheight_);

    if ( !LoadMapProcedurally(uniquetiles) )
        std::cout << "Failed to Load Tile Map: Cascading errors Someday " << std::endl;
}

TileMap::~TileMap()
{
    //dtor
}

bool TileMap::LoadMapProcedurally(const std::vector<Tile> &uniquetiles)
{
    int totalcenterpoints = 0;
    int centerpointcounter = 0;
    int samplessincelastcenter = 1;
    int centerpointchance = 0;
    int centerindex;
    std::vector<std::vector<int>> clusters;
    int tiletype = 0;
    std::vector<int> centerpoints;

    std::srand(std::time(0));
    // Get total center points
    totalcenterpoints = std::rand() % 20 + 15;
    clusters.resize(totalcenterpoints);
    for ( int i = 0; i < totalcenterpoints; i++)
    {
        int x = std::rand() % mapwidth_;
        int y = std::rand() % mapheight_;
        int index = (y*mapwidth_) + x;
        tiletype = std::rand() % uniquetiles.size();
        centerpoints.push_back(index);
        tilemap_[index] = uniquetiles[tiletype];
    }

    std::cout << "-----BEGIN PROCEDURAL ALG-----" <<std::endl;

    for (int i = 0; i < tilemap_.size(); i++)
    {
        int mindistance = 1000000;
        int closestpoint = 0;
        int distance;
        int tilex = (i%mapwidth_);
        int tiley = ((i-tilex)/mapwidth_);
        for (int j = 0; j < centerpoints.size(); j++)
        {
            int centerx = (centerpoints[j]%mapwidth_);
            int centery = ((centerpoints[j]-centerx)/mapwidth_);
            distance = sqrt((double)( (centerx-tilex)*(centerx-tilex) + (centery-tiley)*(centery-tiley)));
            //std::cout << tilex << " " << tiley << " " <<  centerx << " " << centery << " " << distance << std::endl;
            if ( distance < mindistance)
            {
                mindistance = distance;
                closestpoint = centerpoints[j];
                centerindex = j;

            }
        }

        clusters[centerindex].push_back(i);
        tilemap_[i] = tilemap_[closestpoint];
        //std::cout << closestpoint << " " << tilemap_[closestpoint]->ID() << " " << tilemap_[i]->ID() << std::endl;
    }

    std::cout << "ENDING PROCEDURAL ALG" << std::endl;
    return true;
}


bool TileMap::LoadMapFromFile(std::string filename, const std::vector<Tile> &uniquetiles)
{
	bool tilesLoaded = true;
	char id;
    int i = 0;
	std::ifstream file(filename.c_str());


	if (file)
	{
        std::cout << "Loading Map File " << filename << std::endl;
        while (file >> id)
        {
            if ( id != '\n' && id != ',')
                tilemap_[i++] = uniquetiles.at((int)(id - '0'));

            if ( i == (mapwidth_ * mapheight_))
                break;
        }
	}
	else
	{
		std::cout << "Unable to load map file " << filename << std::endl;
		tilesLoaded = false;
	}

	file.close();

	return tilesLoaded;
}

void TileMap::Render(SDLManager* sdlmanager, SDL_Rect boundsrect)
{
    int col, row;
    SDL_Rect tilerect;

    int xlowerbound = boundsrect.x/tilesize_;
    int xupperbound = ceil(double((boundsrect.x + boundsrect.w)/tilesize_))+1;
    int ylowerbound = boundsrect.y/tilesize_;
    int yupperbound = ceil(double((boundsrect.y + boundsrect.h)/tilesize_));

    if (xupperbound >= mapwidth_)
        xupperbound = mapwidth_;

    if (yupperbound >= mapheight_)
        yupperbound = mapheight_;

    if (ylowerbound < 0)
        ylowerbound = 0;

    if (xlowerbound < 0)
        xlowerbound = 0;

    for (int i = xlowerbound; i < xupperbound; i++)
    {
        for(int j = ylowerbound; j < yupperbound; j++)
        {
            //if ( tilemap_[(j*mapwidth_) + i ] != nullptr)
            //{
                SDL_Rect cliprect = tilemap_[ (j*mapwidth_) + i ].Cliprect();

                col = tilesize_*i - boundsrect.x;
                row = tilesize_*j;
				//http://stackoverflow.com/questions/22132531/fastest-way-to-render-a-tiled-map-with-sdl2
				//http://stackoverflow.com/questions/20730900/creating-a-new-texture-from-several-textures-sdl-2
                sdlmanager->RenderImage(tilemap_[i].Imagepath(),col,row,&cliprect);
            //}
        }
    }

}

void TileMap::Render(SDLManager* sdlmanager)
{
	int col, row;
	SDL_Rect tilerect;

	for (int i = 0; i < mapwidth_; i++)
	{
		for (int j = 0; j < mapheight_; j++)
		{
			//if (tilemap_[(j*mapwidth_) + i] != nullptr)
			//{
				SDL_Rect cliprect = tilemap_[(j*mapwidth_) + i].Cliprect();

				col = tilesize_*i;
				row = tilesize_*j;
				//http://stackoverflow.com/questions/22132531/fastest-way-to-render-a-tiled-map-with-sdl2
				//http://stackoverflow.com/questions/20730900/creating-a-new-texture-from-several-textures-sdl-2
				sdlmanager->RenderImage(tilemap_[i].Imagepath(), col, row, &cliprect);
			//}

		}
	}

}

