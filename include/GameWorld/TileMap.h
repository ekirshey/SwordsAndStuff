#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>
#include <memory>
#include "SDL_rect.h"

class Tile;
class SDLManager;

class TileMap
{
    public:
        TileMap(int mapwidth, int mapheight, int tilesize) : mapwidth_(mapwidth), mapheight_(mapheight), tilesize_(tilesize)
        {
            tilemap_.resize(mapwidth*mapheight);
        }

        // Map from a file
        TileMap(int mapwidth, int mapheight, int tilesize, std::string filetoload, const std::vector<std::unique_ptr<Tile>> &uniquetiles);

        // Procedural Map
        TileMap(int mapwidth, int mapheight, int tilesize, const std::vector<std::unique_ptr<Tile>> &uniquetiles);

        virtual ~TileMap();

        bool LoadMapFromFile(std::string filename, const std::vector<std::unique_ptr<Tile>> &uniquetiles);
        bool LoadMapProcedurally(const std::vector<std::unique_ptr<Tile>> &uniquetiles);

        void Render(SDLManager* sdlmanager, SDL_Rect boundsrect);
		void Render(SDLManager* sdlmanager);
    private:
        int mapwidth_;      // In Tiles
        int mapheight_;     // In Tiles
        int tilesize_;      // In pixels
        std::vector<Tile*> tilemap_;
};

#endif // TILEMAP_H
