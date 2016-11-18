#include "../../include/ECSFramework/ECSManager.h"
#include "../../include/Systems/RenderSystem.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/AngleComponent.h"
//#include "../../include/Components/BoundingRectangleComponent.h" 
#include "../../include/GameWorld/GameWorld.h"
#include "../../include/GameWorld/Camera.h"
#include <iostream>
#include <sstream>

RenderSystem::RenderSystem(std::string systemname, ECSManager* ecsmanager, SAS_System::Renderer* renderer) : 
	ProcessingSystem(systemname, ecsmanager), _renderer(renderer), _gameworld(nullptr)
{

}

RenderSystem::RenderSystem(std::string systemname, ECSManager* ecsmanager, SAS_System::Renderer* renderer, GameWorld* gameworld, Camera* camera) : 
	ProcessingSystem(systemname, ecsmanager), _renderer(renderer), _gameworld(gameworld), _camera(camera)
{
	_gameworld->BuildTileMapTexture(_renderer);

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
	std::ostringstream strs;
	if (FrameTime() > 0)
	{
		strs << 1000 / FrameTime();
		strs << " ";
		strs << GetECSManager()->EntityCount();
		std::string str = "FPS: " + strs.str();
		//_renderer->RenderText(str);
	}

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

	// Adjust cliprect for facing
	cliprect.x = cliprect.x + (positioncomponent->facing_ * cliprect.w);

	SDL_Rect cullrect = {positioncomponent->x_, positioncomponent->y_, cliprect.w, cliprect.h};

/*
	if (entity == 0)
	{
		std::vector<QuadElement> elements = _gameworld->SparseGridQueryRange(entityrect->Rectangle());

		for (int i = 0; i < elements.size(); i++)
		{
			SDL_Rect rect{ elements[i].boundingrectangle->Rectangle().x - _camera->x_,elements[i].boundingrectangle->Rectangle().y - _camera->y_,
				elements[i].boundingrectangle->Rectangle().w,elements[i].boundingrectangle->Rectangle().h };
			_renderer->RenderOutlineRectangle(rect, 0x00, 0x00, 0x00, 0xFF);
		}
	}
*/

    // TODO This implies that you NEED a camera. Is this true? I dont think it should be
	if (rendercomponent != nullptr)
	{
		if (SDL_HasIntersection(&cullrect, &camerarect))
		{
			if (rendercomponent->RenderAngle() != 0.0)
			{
				SDL_Point center = { (cliprect.w / 2), (cliprect.h / 2) };
				_renderer->RenderImage(rendercomponent->ImagePath(), positioncomponent->x_ - _camera->X(), positioncomponent->y_ - _camera->Y(), &cliprect, rendercomponent->RenderAngle(), &center, SDL_FLIP_NONE);
			}
			else
				_renderer->RenderImage(rendercomponent->ImagePath(), positioncomponent->x_ - _camera->X(), positioncomponent->y_ - _camera->Y(), &cliprect);
		}

	}

}

