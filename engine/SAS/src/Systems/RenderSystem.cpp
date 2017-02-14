#include "ECSFramework/ECSManager.h"
#include "Systems/RenderSystem.h"
#include "Components/RenderComponent.h"
#include "Components/PositionComponent.h"
#include "Components/AngleComponent.h"
//#include "../../include/Components/BoundingRectangleComponent.h" 
#include "GameWorld/GameWorld.h"
#include "GameWorld/Camera.h"
#include "Geometry.h"
#include <iostream>
#include <sstream>

RenderSystem::RenderSystem(std::string systemname, ECSManager* ecsmanager, SAS_System::Renderer* renderer) : 
	ProcessingSystem(systemname, ecsmanager), _renderer(renderer), _gameworld(nullptr)
{

}

RenderSystem::RenderSystem(std::string systemname, ECSManager* ecsmanager, SAS_System::Renderer* renderer, GameWorld* gameworld, Camera* camera) : 
	ProcessingSystem(systemname, ecsmanager), _renderer(renderer), _gameworld(gameworld), _camera(camera)
{
	//_gameworld->BuildTileMapTexture(_renderer);

	SetSystemName("RenderSystem");
}

RenderSystem::~RenderSystem()
{
    //dtor
}

void RenderSystem::BeforeObjectProcessing()
{
	SDL_Rect camerarect = _camera->GetCameraRect();

	// Render tilemap texture
	_gameworld->Render(_renderer, &camerarect);

}

void RenderSystem::AfterObjectProcessing()
{
	//_gameworld->DrawSparseGrid(_renderer);
}

void RenderSystem::ProcessEntity(uint_fast64_t entity)
{
    SDL_Rect camerarect = _camera->GetCameraRect();
    RenderComponent* rendercomponent = nullptr;
    PositionComponent* positioncomponent = nullptr;
    AngleComponent* anglecomponent = nullptr;
    BoundingRectangleComponent* entityrect;

    // Get Relevant Component Data
    positioncomponent = GetEntityComponent<PositionComponent*>(entity,PositionComponent::ID);
    rendercomponent = GetEntityComponent<RenderComponent*>(entity,RenderComponent::ID);
    anglecomponent = GetEntityComponent<AngleComponent*>(entity,AngleComponent::ID);
    entityrect = GetEntityComponent<BoundingRectangleComponent*>(entity,BoundingRectangleComponent::ID);

    SDL_Rect cliprect = rendercomponent->ClipRect();

	SDL_Rect cullrect = {positioncomponent->_x, positioncomponent->_y, cliprect.w, cliprect.h};


    // TODO This implies that you NEED a camera. Is this true? I dont think it should be
	if (rendercomponent != nullptr)
	{
		if (SDL_HasIntersection(&cullrect, &camerarect))
		{
			//if (entityrect != nullptr)
			//	_renderer->RenderOutlineRectangle(entityrect->Rectangle(), SDL_Color{ 0x00, 0x00, 0x00, 0xFF });
			if (positioncomponent->_angle != 0.0)
			{
				SDL_Point center = { (cliprect.w / 2), (cliprect.h / 2) };
				_renderer->RenderImage(rendercomponent->ImagePath(), positioncomponent->_x - _camera->X(), positioncomponent->_y - _camera->Y(), &cliprect, positioncomponent->_angle + 90.0, center, SDL_FLIP_NONE);
			}
			else {
				_renderer->RenderImage(rendercomponent->ImagePath(), positioncomponent->_x - _camera->X(), positioncomponent->_y - _camera->Y(), &cliprect);
			}
		}

	}

}

