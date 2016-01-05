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

RenderSystem::RenderSystem(SDLManager* sdlmanager) : sdlmanager_(sdlmanager), gameworld_(nullptr)
{
	SetSystemName("RenderSystem");
}

RenderSystem::RenderSystem( SDLManager* sdlmanager, GameWorld* gameworld, Camera* camera)
    : sdlmanager_(sdlmanager), gameworld_(gameworld), camera_(camera)
{
	tilemap_ = SDL_CreateTexture(sdlmanager_->GetRenderer(), SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, gameworld_->Width(), gameworld_->Height());
	SDL_SetRenderTarget(sdlmanager_->GetRenderer(), tilemap_);

	gameworld_->Render(sdlmanager_);	// Build map texture
	SDL_SetRenderTarget(sdlmanager_->GetRenderer(), NULL);

	SetSystemName("RenderSystem");
}

RenderSystem::~RenderSystem()
{
    //dtor
}

void RenderSystem::BeforeObjectProcessing()
{
/* EKTEMP Render Info no real reason its here
	SDL_RendererInfo x;
	SDL_GetRendererInfo(sdlmanager_->GetRenderer(), &x);
	std::cout << x.name << " " << x.flags<< std::endl;
*/
	//GetECSManager()->ClearTagVector("ONSCREEN"); // Rebuild the onscreen list

    //if ( gameworld_ != nullptr && camera_ != nullptr)
    //    gameworld_->Render(sdlmanager_,camera_);
	SDL_Rect destrect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	SDL_Rect camerarect = camera_->GetCameraRect();

	SDL_RenderCopy(sdlmanager_->GetRenderer(), tilemap_, &camerarect, NULL);

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
		sdlmanager_->RenderText(str);
	}

	//gameworld_->DrawSparseGrid(sdlmanager_);
}

void RenderSystem::ProcessEntity(uint_fast64_t entity)
{

    SDL_Rect camerarect = camera_->GetCameraRect();
    RenderComponent* rendercomponent = nullptr;
    PositionComponent* positioncomponent = nullptr;
    AngleComponent* anglecomponent = nullptr;
    BoundingRectangleComponent* entityrect;

    // Get Relevant Component Data
    positioncomponent = GetEntity<PositionComponent*>(entity,PositionComponent::ID);
    rendercomponent = GetEntity<RenderComponent*>(entity,RenderComponent::ID);
    anglecomponent = GetEntity<AngleComponent*>(entity,AngleComponent::ID);
    entityrect = GetEntity<BoundingRectangleComponent*>(entity,BoundingRectangleComponent::ID);

    SDL_Rect cliprect = rendercomponent->ClipRect();

	SDL_Rect cullrect = {positioncomponent->X(), positioncomponent->Y(), cliprect.w, cliprect.h};

	if (entity == 0)
	{
		std::vector<QuadElement> elements = gameworld_->SparseGridQueryRange(entityrect->Rectangle());

		for (int i = 0; i < elements.size(); i++)
		{
			SDL_Rect rect{ elements[i].boundingrectangle->Rectangle().x - camera_->X(),elements[i].boundingrectangle->Rectangle().y - camera_->Y(),
				elements[i].boundingrectangle->Rectangle().w,elements[i].boundingrectangle->Rectangle().h };
			sdlmanager_->RenderOutlineRectangle(rect, 0x00, 0x00, 0x00, 0xFF);
		}
	}

    // TODO This implies that you NEED a camera. Is this true? I dont think it should be
	if (rendercomponent != nullptr)
	{
		if (SDL_HasIntersection(&cullrect, &camerarect))
		{
			if (rendercomponent->RenderAngle() != 0.0)
			{
				SDL_Point center = { (cliprect.w / 2), (cliprect.h / 2) };
				sdlmanager_->RenderImage(rendercomponent->ImagePath(), positioncomponent->X() - camera_->X(), positioncomponent->Y() - camera_->Y(), &cliprect, rendercomponent->RenderAngle(), &center, SDL_FLIP_NONE);
			}
			else
				sdlmanager_->RenderImage(rendercomponent->ImagePath(), positioncomponent->X() - camera_->X(), positioncomponent->Y() - camera_->Y(), &cliprect);
		}

	}

}

