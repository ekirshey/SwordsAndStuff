#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <memory>
#include "TileMap.h"
#include "Tile.h"
#include "Utilities/QuadTree.h"
#include "Utilities/SparseGrid.h"

class SDLManager;

class Camera;
class GameWorld
{
    public:
        GameWorld();
		GameWorld(SAS_System::Renderer& renderer, int width, int height, std::string mediaroot);

		GameWorld(const GameWorld&) = default;
		GameWorld& operator=(const GameWorld&) = default;

		~GameWorld();

        void BuiltTileMapFromFile(int tilesize, std::string file);
        void BuildProceduralTileMap(int tilesize);

        TileMap* GetTileMap() const { return _tilemap.get();}

		void Render(SAS_System::Renderer* sdlmanager, const SDL_Rect* camera);

		// Temp SparseGrid functions
		bool SparseGridInsert(QuadElement entity) { return _sparsegrid->Insert(entity); }
		std::vector<QuadElement> SparseGridQueryRange(const SDL_Rect& rect) const { return _sparsegrid->QueryRange(rect); }
		void ClearSparseGrid() { _sparsegrid->clear(); }
		void DrawSparseGrid(SAS_System::Renderer* renderer) { _sparsegrid->Draw(renderer); }

		void BuildTileMapTexture(SAS_System::Renderer* renderer);

    private:
		int _width;
		int _height;
		std::string _mediaroot;
		int _tilemaptexture;

        // some sort of Tiled Map
        std::unique_ptr<TileMap> _tilemap;
        std::vector<Tile> _uniquetiles;
		std::unique_ptr<SparseGrid> _sparsegrid;
};

#endif // GAMEWORLD_H
