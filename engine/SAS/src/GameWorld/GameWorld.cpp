#include <iostream>
#include "GameWorld/GameWorld.h"
#include "Components/PositionComponent.h"
#include "GameWorld/Camera.h"
#include "Config/GameDefines.h"
GameWorld::GameWorld()
{
    //ctor
}

GameWorld::GameWorld(SAS_System::Renderer& renderer, int width, int height, std::string mediaroot) 
	: _width(width)
	, _height(height)
	, _mediaroot(mediaroot)
{
	//quadtree_ = std::unique_ptr<QuadTree>(new QuadTree(SDL_Rect{0,0,SCREEN_WIDTH,SCREEN_HEIGHT },4,6));
	_sparsegrid = std::make_unique<SparseGrid>(SDL_Rect{ 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }, SCREEN_WIDTH/32, SCREEN_HEIGHT/32);
	_tilemaptexture = renderer.CreateTargetTexture(_width, _height);
}


GameWorld::~GameWorld()
{
}

void GameWorld::BuildTileMapTexture(SAS_System::Renderer* renderer) {
	/*
	_tilemaptexture = SDL_CreateTexture(sdlmanager->GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, _width, _height);

	SDL_SetRenderTarget(sdlmanager->GetRenderer(), _tilemaptexture);

	_tilemap->Render(sdlmanager);

	SDL_SetRenderTarget(sdlmanager->GetRenderer(), NULL);
	*/

	renderer->SetRenderTarget(_tilemaptexture);
	_tilemap->Render(renderer);
	renderer->DefaultRenderTarget();
}

void GameWorld::BuiltTileMapFromFile(int tilesize, std::string file)
{
    SDL_Rect cliprect = {96,0,tilesize,tilesize};

    // Manually building tiles here FOR NOW
    _uniquetiles.push_back(Tile(0,false,_mediaroot+"media\\tiles\\tileset.bmp",cliprect));
    cliprect.x = 64;
    cliprect.y = 32;
    _uniquetiles.push_back(Tile(1,false,_mediaroot+"media\\tiles\\tileset.bmp",cliprect));
    cliprect.x = 32;
    cliprect.y = 64;
    _uniquetiles.push_back(Tile(2,false,_mediaroot+"media\\tiles\\tileset.bmp",cliprect));

    _tilemap = std::make_unique<TileMap>(_width/tilesize, _height/tilesize, tilesize,file, _uniquetiles);

}

void GameWorld::BuildProceduralTileMap(int tilesize)
{
    SDL_Rect cliprect = {608,288,tilesize,tilesize};
	
    // Manually building tiles here FOR NOW
    _uniquetiles.push_back(Tile(0,false,_mediaroot+"media\\tiles\\tileset2.png",cliprect));
    _uniquetiles.push_back(Tile(1,false,_mediaroot+"media\\tiles\\tileset2.png",cliprect));
    _uniquetiles.push_back(Tile(2,false,_mediaroot+"media\\tiles\\tileset2.png",cliprect));
    _uniquetiles.push_back(Tile(3,false,_mediaroot+"media\\tiles\\tileset2.png",cliprect));
	
    _tilemap = std::make_unique<TileMap>(_width/tilesize, _height/tilesize, tilesize,_uniquetiles);
	
}

void GameWorld::Render(SAS_System::Renderer* renderer, const SDL_Rect* camera)
{
	renderer->RenderTargetTexture(_tilemaptexture, 0, 0, camera);
}
