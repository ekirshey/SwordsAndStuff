#include <vector>
#include <iostream>
#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Systems/CameraSystem.h"
#include "../../include/GameWorld/Camera.h"

#define NOTARGET 0x7FFFFFFFFFFFFFFF

CameraSystem::CameraSystem(Camera* camera) : camera_(camera),
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
