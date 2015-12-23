#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#include <string>
#include <SDL.h>
#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class RenderComponent : public Component
{
    public:
        static const uint_fast64_t ID = RenderComponentID;

		RenderComponent() { clip_ = { 0,0,0,0 }; imagepath_ = nullptr; }
        RenderComponent(std::string path, SDL_Rect cliprect) : imagepath_(path), clip_(cliprect) {}
        RenderComponent(const RenderComponent& c) :  imagepath_(c.ImagePath()), clip_(c.ClipRect()) {}

        ~RenderComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

        std::string ImagePath() const {return imagepath_;}
        SDL_Rect ClipRect() const {return clip_;}

        void SetPath(std::string path) { imagepath_ = path;}
        void SetClipRect(SDL_Rect cliprect) { clip_ = cliprect;}

    private:
        std::string imagepath_;
        SDL_Rect clip_;


};
#endif // RENDERCOMPONENT_H
