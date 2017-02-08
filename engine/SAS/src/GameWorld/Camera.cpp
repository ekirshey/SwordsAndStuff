#include <math.h>
#include "../../include/GameWorld/Camera.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include <iostream>

Camera::Camera()
{
    //ctor
}

Camera::Camera(int gameworldwidth, int gameworldheight, SDL_Rect camerarect, PositionComponent* focusposition, VelocityComponent* focusvelocity)
	: _gameworldwidth(gameworldwidth)
	, _gameworldheight(gameworldheight)
	, _camerarect(camerarect)
	, _focusposition(focusposition)
	, _focusvelocity(focusvelocity)
{

}

Camera::Camera(int gameworldwidth, int gameworldheight, SDL_Rect camerarect)
	: _gameworldwidth(gameworldwidth)
	, _gameworldheight(gameworldheight)
	, _camerarect(camerarect)
{

}



Camera::~Camera()
{
    //dtor
}

void Camera::Update()
{
    int cameramovement;

    if ((_focusvelocity->XVelocity() < 0) && 
		(_focusposition->x_ - _camerarect.x) < _camerarect.w * .33 )
    {
        cameramovement = _camerarect.x - abs(_focusvelocity->XVelocity());
        if ( (cameramovement > 0) )
            _camerarect.x = cameramovement;
    }
	else if ((_focusvelocity->XVelocity() > 0) && 
		(_focusposition->x_ - _camerarect.x) > (_camerarect.w * .66))
	{
		cameramovement = (_camerarect.x + _focusvelocity->XVelocity());
		if ((cameramovement + _camerarect.w) < _gameworldwidth)
			_camerarect.x = cameramovement;
	}

	if ((_focusvelocity->YVelocity() < 0) &&
		(_focusposition->y_ - _camerarect.y) < _camerarect.h * .33)
	{
		cameramovement = _camerarect.y - abs(_focusvelocity->YVelocity());
		if ((cameramovement > 0))
			_camerarect.y = cameramovement;
	}
	else if ((_focusvelocity->YVelocity() > 0) &&
		(_focusposition->y_ - _camerarect.y) > (_camerarect.h * .66))
	{
		cameramovement = (_camerarect.y + _focusvelocity->YVelocity());
		if ((cameramovement + _camerarect.h) < _gameworldheight)
			_camerarect.y = cameramovement;
	}

}
