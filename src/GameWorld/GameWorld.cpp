#include "../../include/GameWorld/GameWorld.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/SDL/SDLManager.h"
#include "../../include/GameWorld/Camera.h"

#include <iostream>
GameWorld::GameWorld()
{
    //ctor
}

GameWorld::GameWorld(int width, int height) : width_(width), height_(height)
{
	//quadtree_ = std::unique_ptr<QuadTree>(new QuadTree(SDL_Rect{0,0,SCREEN_WIDTH,SCREEN_HEIGHT },4,6));
	sparsegrid_ = std::make_unique<SparseGrid>(SDL_Rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, SCREEN_WIDTH/32, SCREEN_HEIGHT/32);
}


GameWorld::~GameWorld()
{
    //dtor
}

void GameWorld::BuiltTileMapFromFile(int tilesize, std::string file)
{
    SDL_Rect cliprect = {96,0,tilesize,tilesize};

    // Manually building tiles here FOR NOW
    uniquetiles_.push_back(std::make_unique<Tile>(0,false,"..\\..\\..\\media\\tiles\\tileset.bmp",cliprect));
    cliprect.x = 64;
    cliprect.y = 32;
    uniquetiles_.push_back(std::make_unique<Tile>(1,false,"..\\..\\..\\media\\tiles\\tileset.bmp",cliprect));
    cliprect.x = 32;
    cliprect.y = 64;
    uniquetiles_.push_back(std::make_unique<Tile>(2,false,"..\\..\\..\\media\\tiles\\tileset.bmp",cliprect));

    tilemap_ = std::make_unique<TileMap>(width_/tilesize, height_/tilesize, tilesize,file,uniquetiles_);

}

void GameWorld::BuildProceduralTileMap(int tilesize)
{
    SDL_Rect cliprect = {608,288,tilesize,tilesize};
	
    // Manually building tiles here FOR NOW
    uniquetiles_.push_back(std::make_unique<Tile>(0,false,"..\\..\\..\\media\\tiles\\tileset2.png",cliprect));
    uniquetiles_.push_back(std::make_unique<Tile>(1,false,"..\\..\\..\\media\\tiles\\tileset2.png",cliprect));
    uniquetiles_.push_back(std::make_unique<Tile>(2,false,"..\\..\\..\\media\\tiles\\tileset2.png",cliprect));
    uniquetiles_.push_back(std::make_unique<Tile>(3,false,"..\\..\\..\\media\\tiles\\tileset2.png",cliprect));
	
    tilemap_ = std::make_unique<TileMap>(width_/tilesize, height_/tilesize, tilesize,uniquetiles_);
	
}

void GameWorld::Render(SDLManager* sdlmanager, Camera* camera)
{
    tilemap_->Render(sdlmanager,camera->GetCameraRect());
}

void GameWorld::Render(SDLManager* sdlmanager)
{
	tilemap_->Render(sdlmanager);
}