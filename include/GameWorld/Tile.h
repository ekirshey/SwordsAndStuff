#ifndef TILE_H
#define TILE_H

#include <string>
#include "SDL_rect.h"

class Tile
{
    public:
        Tile(int id, bool collidable, std::string imagepath, SDL_Rect cliprect) : id_(id), collidable_(collidable), imagepath_(imagepath), cliprect_(cliprect) {}
        virtual ~Tile() {}

        void SetID(int id) {id_ = id;}
        void SetCollidable(bool collidable) {collidable_ = collidable;}
        void SetImagepath(std::string imagepath) {imagepath_ = imagepath;}
        void SetClipRect(SDL_Rect cliprect) {cliprect_ = cliprect;}

        int ID() {return id_;}
        bool Collidable() {return collidable_;}
        std::string Imagepath() {return imagepath_;}
        SDL_Rect Cliprect() {return cliprect_;}

    private:
        int id_;
        bool collidable_;
        std::string imagepath_;
        SDL_Rect cliprect_;
};

#endif // TILE_H
