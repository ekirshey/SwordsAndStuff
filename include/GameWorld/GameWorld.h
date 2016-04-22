#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
#include "TileMap.h"
#include "Tile.h"
#include "../Utilities/QuadTree.h"
#include "../Utilities/SparseGrid.h"

class SDLManager;

class Camera;
class GameWorld
{
    public:
        GameWorld();
        GameWorld(int width, int height);
        virtual ~GameWorld();

        void BuiltTileMapFromFile(int tilesize, std::string file);
        void BuildProceduralTileMap(int tilesize);

        TileMap* GetTileMap() const { return tilemap_.get();}

		void Render(SDLManager* sdlmanager, const SDL_Rect* camera);

		// Temp SparseGrid functions
		bool SparseGridInsert(QuadElement entity) { return sparsegrid_->Insert(entity); }
		std::vector<QuadElement> SparseGridQueryRange(const SDL_Rect& rect) const { return sparsegrid_->QueryRange(rect); }
		void ClearSparseGrid() { sparsegrid_->clear(); }
		void DrawSparseGrid(SDLManager* sdlmanager) { sparsegrid_->Draw(sdlmanager); }

		void BuildTileMapTexture(SDLManager* sdlmanager);

		int width_;
		int height_;
    private:
		SDL_Texture* tilemaptexture_;

        // some sort of Tiled Map
        std::unique_ptr<TileMap> tilemap_;
        std::vector<Tile> uniquetiles_;
		std::unique_ptr<SparseGrid> sparsegrid_;
};

#endif // GAMEWORLD_H
