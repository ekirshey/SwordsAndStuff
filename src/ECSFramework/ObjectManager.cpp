#include <iostream>
#include <vector>
#include "../../include/ECSFramework/ObjectManager.h"
#include "../../include/SDL/SDLManager.h"
#include "../../include/GameWorld/GameWorld.h"
#include "../../include/GameWorld/Camera.h"
#include "../../include/Systems/RenderSystem.h"
#include "../../include/Systems/InputSystem.h"
#include "../../include/Systems/MovementSystem.h"
#include "../../include/Systems/ShootingSystem.h"
#include "../../include/Systems/CollisionSystem.h"
#include "../../include/Systems/CameraSystem.h"
#include "../../include/Systems/PlayerTargetingSystem.h"
#include "../../include/Components/BoundingRectangleComponent.h"
#include "../../include/Components/RenderComponent.h"
#include "../../include/Components/PositionComponent.h"
#include "../../include/Components/InputComponent.h"
#include "../../include/Components/AngleComponent.h"
#include "../../include/Components/VelocityComponent.h"
#include "../../include/Components/ShootingComponent.h"
#include "../../include/Components/RPGStatsComponent.h"
#include "../../include/Components/InventoryComponent.h"
#include "../../include/Components/TargetingComponent.h"


ObjectManager::ObjectManager()
{
	//ctor
}

ObjectManager::ObjectManager(SDLManager* sdlmanager, GameWorld* gameworld, Camera* camera)
{
	Initialize(sdlmanager, gameworld, camera);
}

ObjectManager::~ObjectManager()
{
	//dtor
}

void ObjectManager::Initialize(SDLManager* sdlmanager, GameWorld* gameworld, Camera* camera)
{
	SDL_Rect rect;
	std::string path;
	int priority = 0;
	int cameraindex = 0;

	// Build systems and entities
	ecsmanager_.AddSystem(new InputSystem(&ecsmanager_, sdlmanager ),priority++);
	ecsmanager_.AddSystem(new MovementSystem(&ecsmanager_, gameworld), priority++);
	ecsmanager_.AddSystem(new CollisionSystem(&ecsmanager_, gameworld), priority++);
	ecsmanager_.AddSystem(new PlayerTargetingSystem(&ecsmanager_, *sdlmanager, *gameworld, "..\\..\\..\\media\\reticule.png"), priority++);	
	cameraindex = ecsmanager_.AddSystem(new CameraSystem(&ecsmanager_,camera), priority++);
	ecsmanager_.AddSystem(new RenderSystem(&ecsmanager_, sdlmanager, gameworld, camera), priority++);

	// Player
	int playerentity = ecsmanager_.CreateEntity();
	rect = { 0,0,26,26 }; // Removed top pixel due to a black line showing up when rotating
						  //path = "media\\sprites\\shooter.png";
	path = "..\\..\\..\\media\\Wikimedia\\Player2.png";
	ecsmanager_.AddComponentToEntity(playerentity, new PositionComponent((SCREEN_WIDTH / 2) - (34 / 2), 400));
	ecsmanager_.AddComponentToEntity(playerentity, new InputComponent());
	ecsmanager_.AddComponentToEntity(playerentity, new VelocityComponent(0, 0));
	ecsmanager_.AddComponentToEntity(playerentity, new RenderComponent(path, rect));
	ecsmanager_.AddComponentToEntity(playerentity, new BoundingRectangleComponent((SCREEN_WIDTH / 2) - (34 / 2) + 8, 400 + 8, 24, 24)); // TODO Magic Numbers
	//ecsmanager_.AddComponentToEntity(playerentity, new CollisionComponent());
	ecsmanager_.AddComponentToEntity(playerentity, new RPGStatsComponent());
	ecsmanager_.AddComponentToEntity(playerentity, new TargetingComponent());
	ecsmanager_.AssignEntityTag(playerentity, "PLAYER");
	std::cout << playerentity << std::endl;
	
	
	CameraSystem* camerasystem = static_cast<CameraSystem*>(ecsmanager_.GetSystem(cameraindex));
	if (camerasystem != nullptr)
		camerasystem->SetFocus(playerentity);
	else
		std::cout << "Failed to set camera focus, camera doesnt exist" << std::endl;
		
	
	path =  "..\\..\\..\\media\\Wikimedia\\Pawns.png";
	// Monster
	int monsterentity;
	int mod;
	for (int j = 0; j < 10; j++)
		for (int i = 0; i < 10; i++)
		{
			monsterentity = ecsmanager_.CreateEntity();
			int mod = 0;
			if (j % 2 == 0) mod = 1;
			rect = { (i % 5) * 22,mod * 28,22,28 };
			ecsmanager_.AddComponentToEntity(monsterentity, new PositionComponent((50+i*40) + i * 23, 50 + j * 29)); // TODO MAgic numbers
			ecsmanager_.AddComponentToEntity(monsterentity, new VelocityComponent(0, 0));
			ecsmanager_.AddComponentToEntity(monsterentity, new BoundingRectangleComponent((55 + i*40) + i * 23, 55 + j * 29, 20, 21));//30,30
			//ecsmanager_.AddComponentToEntity(monsterentity, new CollisionComponent());
			ecsmanager_.AddComponentToEntity(monsterentity, new RenderComponent(path, rect));
			ecsmanager_.AssignEntityTag(monsterentity, "MONSTER");
			//std::cout << monsterentity << std::endl;
			// EKNOTE Would actually check this in the future even though for one frame idk if it matters
			//ecsmanager_.AssignEntityTag(monsterentity, "ONSCREEN");
		}
	int i = 18;
	int j = 12;
	monsterentity = ecsmanager_.CreateEntity();
	int mod2 = 0;
	if (j % 2 == 0) mod2 = 1;
	rect = { (i % 5) * 22,mod2 * 28,22,28 };
	ecsmanager_.AddComponentToEntity(monsterentity, new PositionComponent((50 + i * 40) + i * 23, 50 + j * 29)); // TODO MAgic numbers
	ecsmanager_.AddComponentToEntity(monsterentity, new VelocityComponent(0, 0));
	ecsmanager_.AddComponentToEntity(monsterentity, new BoundingRectangleComponent((55 + i * 40) + i * 23, 55 + j * 29, 20, 21));//30,30
																																 //ecsmanager_.AddComponentToEntity(monsterentity, new CollisionComponent());
	ecsmanager_.AddComponentToEntity(monsterentity, new RenderComponent(path, rect));
	ecsmanager_.AssignEntityTag(monsterentity, "MONSTER");
	//std::cout << monsterentity << std::endl;
	// EKNOTE Would actually check this in the future even though for one frame idk if it matters
	//ecsmanager_.AssignEntityTag(monsterentity, "ONSCREEN");

#ifdef FOO
	int treeentity;
	treeentity = ecsmanager_.CreateEntity();
	rect = { 0,0,222,223 };
	path = "..\\..\\..\\media\\sprites\\tree.png";
	ecsmanager_.AddComponentToEntity(treeentity, new PositionComponent(300, 300)); // TODO MAgic numbers
	ecsmanager_.AddComponentToEntity(treeentity, new RenderComponent(path, rect));
	ecsmanager_.AddComponentToEntity(treeentity, new BoundingRectangleComponent(411,411,40,40));
	ecsmanager_.AssignEntityTag(treeentity, "STATICOBJECT");
	std::cout << treeentity << std::endl;
#endif
}

void ObjectManager::Update(int elapsedtime)
{
	ecsmanager_.Update(elapsedtime);
}

Component* ObjectManager::GetPlayerComponent(uint_fast64_t componentid)
{
	std::vector<uint_fast64_t> entity = ecsmanager_.GetAssociatedEntities("PLAYER"); // Returns a vector but theres only one player (atm)
	return ecsmanager_.GetEntityComponent(entity[0], componentid);
}

std::vector<Component*> ObjectManager::GetAllPlayerComponents()
{
	std::vector<Component*> playercomponents;

	std::vector<uint_fast64_t> entity = ecsmanager_.GetAssociatedEntities("PLAYER"); // Returns a vector but theres only one player (atm)
	if (entity.size() > 0)
		playercomponents = ecsmanager_.GetAllEntityComponents(entity[0]);
	return playercomponents;
}
