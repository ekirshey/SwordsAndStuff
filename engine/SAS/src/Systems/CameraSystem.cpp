#include <vector>
#include <iostream>
#include "ECSFramework/ECSManager.h"
#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Systems/CameraSystem.h"
#include "GameWorld/Camera.h"

#define NOTARGET 0x7FFFFFFFFFFFFFFF

CameraSystem::CameraSystem(std::string systemname, ECSManager* ecsmanager, Camera* camera) : System(systemname, ecsmanager), camera_(camera),
	focus_(NOTARGET), focusposition_(nullptr), focusvelocity_(nullptr)
{
	SetSystemName("CameraSystem");
}

CameraSystem::~CameraSystem()
{
    //dtor
}

bool CameraSystem::SetFocus(uint_fast64_t focus)
{
	bool focusset = false;
	focus_ = focus;

	focusposition_ = GetEntityComponent<PositionComponent*>(focus_, PositionComponentID);
	focusvelocity_ = GetEntityComponent<VelocityComponent*>(focus_, VelocityComponentID);
	
	if (focusposition_ != nullptr && focusvelocity_ != nullptr)
		focusset = true;
	return focusset;

}

void CameraSystem::ProcessEntities()
{
	if (focus_ != NOTARGET)
		camera_->Update(*focusposition_, *focusvelocity_);
	else
		std::cout << "CAMERASYSTEM:: No Focus, should gracefully crash!" << std::endl;   
}
