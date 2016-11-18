#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>
#include <memory>
#include "Renderer.h"

class Tile;
namespace SAS_Rendering {
	class SDLManager;
}

class TileMap
{
    public:
        TileMap(int mapwidth, int mapheight, int tilesize) : mapwidth_(mapwidth), mapheight_(mapheight), tilesize_(tilesize)
        {
            tilemap_.resize(mapwidth*mapheight);
        }

        // Map from a file
        TileMap(int mapwidth, int mapheight, int tilesize, std::string filetoload, const std::vector<Tile> &uniquetiles);

        // Procedural Map
        TileMap(int mapwidth, int mapheight, int tilesize, const std::vector<Tile> &uniquetiles);

        virtual ~TileMap();

        bool LoadMapFromFile(std::string filename, const std::vector<Tile> &uniquetiles);
        bool LoadMapProcedurally(const std::vector<Tile> &uniquetiles);

        void Render(SAS_System::Renderer* renderer, SDL_Rect boundsrect);
		void Render(SAS_System::Renderer* renderer);
    private:
        int mapwidth_;      // In Tiles
        int mapheight_;     // In Tiles
        int tilesize_;      // In pixels
        std::vector<Tile> tilemap_;
};

#endif // TILEMAP_H
