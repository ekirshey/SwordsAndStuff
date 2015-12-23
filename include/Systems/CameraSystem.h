#ifndef CAMERASYSTEM_H
#define CAMERASYSTEM_H

#include "../ECSFramework/System.h"

/* Note: Camera is unique and does not expand upon a processingsystem or any other sub system. This is because it doesnt act specifically
on the list of entities and just on the player and the camera */

class Camera;
class PositionComponent;
class VelocityComponent;

class CameraSystem : public System
{
    public:
        static const uint_fast64_t COMPONENTIDS = 0x00;      // No ids cause it just grabs the component
        CameraSystem(ECSManager* ECSManager, Camera* camera);
        ~CameraSystem();

        uint_fast64_t ComponentBits() {return CameraSystem::COMPONENTIDS;}    // TODO: Is this necessary or is just accessing the variable directly better?

        void ProcessEntities();
		bool SetFocus(uint_fast64_t focus);
    private:
        Camera* camera_;
		uint_fast64_t focus_;
		PositionComponent* focusposition_;
		VelocityComponent* focusvelocity_;
};
#endif // CAMERASYSTEM_H
