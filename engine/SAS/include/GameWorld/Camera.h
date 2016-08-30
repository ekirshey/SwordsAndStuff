#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <cstdint>
#include "SDL_rect.h"

class PositionComponent;
class VelocityComponent;

class Camera
{
    public:
        Camera();
        Camera(int gameworldwidth, int gameworldheight, SDL_Rect camerarect);

        virtual ~Camera();

        void Update(const PositionComponent& focus, const VelocityComponent& focusvelocity);

        void setCameraPosition(int camerax, int cameray, int level)
        {
            camerarect_.x = camerax;
            camerarect_.y = cameray;
            currentlevel_ = level;
        }

        SDL_Rect GetCameraRect() { return camerarect_;}

        int X() {return camerarect_.x;}
        int Y() {return camerarect_.y;}
        int Width() {return camerarect_.w;}
        int Height() {return camerarect_.h;}

    private:
        int gameworldwidth_;
        int gameworldheight_;
        int currentlevel_;
        SDL_Rect camerarect_;
};

#endif // CAMERA_H
