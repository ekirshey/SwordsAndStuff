#include <math.h>
#include "../../include/GameWorld/Camera.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include <iostream>

Camera::Camera()
{
    //ctor
}

Camera::Camera(int gameworldwidth, int gameworldheight, SDL_Rect camerarect) :
    gameworldwidth_(gameworldwidth), gameworldheight_(gameworldheight), currentlevel_(0), camerarect_(camerarect)
{

}

Camera::~Camera()
{
    //dtor
}

void Camera::Update(const PositionComponent& focus, const VelocityComponent& focusvelocity)
{
    int cameramovement;

    if ((focusvelocity.XVelocity() < 0) && 
		(focus.X() - camerarect_.x) < camerarect_.w * .33 )
    {
        cameramovement = camerarect_.x - abs(focusvelocity.XVelocity());
        if ( (cameramovement > 0) )
            camerarect_.x = cameramovement;
    }
	else if ((focusvelocity.XVelocity() > 0) && 
		(focus.X() - camerarect_.x) > (camerarect_.w * .66))
	{
		cameramovement = (camerarect_.x + focusvelocity.XVelocity());
		if ((cameramovement + camerarect_.w) < gameworldwidth_)
			camerarect_.x = cameramovement;
	}

	if ((focusvelocity.YVelocity() < 0) &&
		(focus.Y() - camerarect_.y) < camerarect_.h * .33)
	{
		cameramovement = camerarect_.y - abs(focusvelocity.YVelocity());
		if ((cameramovement > 0))
			camerarect_.y = cameramovement;
	}
	else if ((focusvelocity.YVelocity() > 0) &&
		(focus.Y() - camerarect_.y) > (camerarect_.h * .66))
	{
		cameramovement = (camerarect_.y + focusvelocity.YVelocity());
		if ((cameramovement + camerarect_.h) < gameworldheight_)
			camerarect_.y = cameramovement;
	}

}
