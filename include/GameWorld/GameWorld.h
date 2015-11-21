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

        int Width() {return width_;}
        int Height() {return height_;}

        void SetWidth(int width) {width_ = width;}
        void SetHeight(int height) {height_ = height;}

        void BuiltTileMapFromFile(int tilesize, std::string file);
        void BuildProceduralTileMap(int tilesize);

        TileMap* GetTileMap() const { return tilemap_.get();}

        void Render(SDLManager* sdlmanager, Camera* camera);
		void Render(SDLManager* sdlmanager);

		// Temp QuadTree functions
		bool QuadTreeInsert(QuadElement entity) { return quadtree_->Insert(entity); }
		std::vector<QuadElement> QuadTreeQueryRange(const SDL_Rect& rect) { return quadtree_->QueryRange(rect); }
		void ClearQuadTree() { quadtree_->clear(); }
		void DrawQuadTree(SDLManager* sdlmanager) { quadtree_->Draw(sdlmanager); }

		// Temp SparseGrid functions
		bool SparseGridInsert(QuadElement entity) { return sparsegrid_->Insert(entity); }
		std::vector<QuadElement> SparseGridQueryRange(const SDL_Rect& rect) { return sparsegrid_->QueryRange(rect); }
		void ClearSparseGrid() { sparsegrid_->clear(); }
		void DrawSparseGrid(SDLManager* sdlmanager) { sparsegrid_->Draw(sdlmanager); }
    private:
        // some sort of Tiled Map
        int width_;
        int height_;
        std::unique_ptr<TileMap> tilemap_;
        std::vector<std::unique_ptr<Tile>> uniquetiles_;
		std::unique_ptr<QuadTree> quadtree_;
		std::unique_ptr<SparseGrid> sparsegrid_;
};

#endif // GAMEWORLD_H
