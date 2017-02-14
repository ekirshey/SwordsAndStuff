#pragma once

#include <vector>
#include <cstdint>
#include "SDL_rect.h"

class PositionComponent;
class VelocityComponent;

class Camera
{
    public:
        Camera();
        Camera(int gameworldwidth, int gameworldheight, SDL_Rect camerarect, PositionComponent* focusposition, VelocityComponent* focusvelocity);
        Camera(int gameworldwidth, int gameworldheight, SDL_Rect camerarect);

        virtual ~Camera();

        void Update();

        void setCameraPosition(int camerax, int cameray, int level)
        {
            _camerarect.x = camerax;
            _camerarect.y = cameray;
            _currentlevel = level;
        }

		void setFocus(PositionComponent* position, VelocityComponent* velocity) {
			_focusposition = position;
			_focusvelocity = velocity;
		}

        SDL_Rect GetCameraRect() const { return _camerarect;}

        int X() const {return _camerarect.x;}
        int Y() const {return _camerarect.y;}
        int Width() const {return _camerarect.w;}
        int Height() const {return _camerarect.h;}

    private:
        int _gameworldwidth;
        int _gameworldheight;
        int _currentlevel;
        SDL_Rect _camerarect;
		PositionComponent* _focusposition;
		VelocityComponent* _focusvelocity;
};

