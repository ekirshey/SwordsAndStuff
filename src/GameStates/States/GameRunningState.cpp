#include <iostream>
#include "../../../include/GameStates/States/GameRunningState.h"
#include "../../../include/SDL/SDLManager.h"
#include "../../../include/SubSystems/MonsterSpawner.h"

#include "../../../include/Systems/RenderSystem.h"
#include "../../../include/Systems/InputSystem.h"
#include "../../../include/Systems/MovementSystem.h"
#include "../../../include/Systems/ShootingSystem.h"
#include "../../../include/Systems/CollisionSystem.h"
#include "../../../include/Systems/CameraSystem.h"
#include "../../../include/Systems/PlayerTargetingSystem.h"
#include "../../../include/Systems/SpellCreationSystem.h"
#include "../../../include/Systems/AISystem.h"
#include "../../../include/Systems/ScriptedEntitySystem.h"

#include "../../../include/Components/BoundingRectangleComponent.h"
#include "../../../include/Components/RenderComponent.h"
#include "../../../include/Components/PositionComponent.h"
#include "../../../include/Components/InputComponent.h"
#include "../../../include/Components/AngleComponent.h"
#include "../../../include/Components/VelocityComponent.h"
#include "../../../include/Components/SpellCastingComponent.h"
#include "../../../include/Components/SpellbookComponent.h"
#include "../../../include/Components/RPGStatsComponent.h"
#include "../../../include/Components/InventoryComponent.h"
#include "../../../include/Components/TargetingComponent.h"
#include "../../../include/Components/EquipmentComponent.h"

GameRunningState::GameRunningState()
{
    SetCurrentState(INITIALIZE);
}

GameRunningState::~GameRunningState()
{

}

void GameRunningState::InitializeState()
{
    SDL_Rect camerarect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

    // Create Game World and Camera
    gameworld_ = std::unique_ptr<GameWorld>(new GameWorld(3072,2560));
    gameworld_->BuildProceduralTileMap(32);
    camera_ = std::unique_ptr<Camera>(new Camera(gameworld_->Width(), gameworld_->Height(),camerarect ));

	// Set up Game Data
	spellbook_ = std::unique_ptr<GlobalSpellbook>(new GlobalSpellbook());
	// Name, Cast time, cooldown, duration (milliseconds)
	// Account for anchor orientation in script
	// Vector of vectors: each vector is the script steps for a facing
	std::vector<std::vector<ScriptStep>> spellscript = {
		{ ScriptStep(0,0,50), ScriptStep(-5,5,50), ScriptStep(-10,10,200) },
		{ ScriptStep(0,0,50), ScriptStep(-5,5,50), ScriptStep(-10,10,200) },
		{ ScriptStep(8,0,50), ScriptStep(13,5,50), ScriptStep(18,10,200) },
		{ ScriptStep(0,0,50), ScriptStep(-5,5,50), ScriptStep(-10,10,200) }
	};
	spellbook_->CreateSpell(0, "MELEE", 0, 100, 300, "../../../media/sprites/sword.png", spellscript);

	// Set up ECS. This was originally in some wrapper object and I dont know why I did that...
	ecsmanager_ = std::unique_ptr<ECSManager>(new ECSManager());
	InitializeECS();

	// GUI Setup HUD and GUI separate for now
    //hudmanager_ = std::unique_ptr<HUDManager>(new HUDManager(objectmanager_.get(), GetSDLManager()));
	//guimanager_ = std::unique_ptr<GUIManager>(new GUIManager(GetSDLManager(), "keymapfile.txt","guifile.txt"));

    SetCurrentState(TRANSITIONIN);
}

void GameRunningState::InitializeECS()
{
	SDL_Rect rect;
	std::string path;
	int priority = 0;
	int cameraindex = 0;

	ecsmanager_->GetQueues().AddQueue("SpellCreation");

	// Build systems and entities
	ecsmanager_->AddSystem(std::make_unique<InputSystem>(GetSDLManager()), priority++);
	//ecsmanager_->AddSystem(std::unique_ptr<AISystem>(new AISystem()), priority++);
	ecsmanager_->AddSystem(std::make_unique<MovementSystem>(gameworld_.get()), priority++);
	ecsmanager_->AddSystem(std::make_unique<ScriptedEntitySystem>(), priority++);	// Not 100% sure on the placement 
	ecsmanager_->AddSystem(std::make_unique<SpellCreationSystem>(ecsmanager_->GetQueues().GetQueue("SpellCreation")), priority++);
	ecsmanager_->AddSystem(std::make_unique<CollisionSystem>(gameworld_.get()), priority++);
	ecsmanager_->AddSystem(std::make_unique<PlayerTargetingSystem>(*GetSDLManager(), *gameworld_.get(), "..\\..\\..\\media\\reticule.png"), priority++);
	cameraindex = ecsmanager_->AddSystem(std::make_unique<CameraSystem>(camera_.get()), priority++);
	ecsmanager_->AddSystem(std::make_unique<RenderSystem>(GetSDLManager(), gameworld_.get(), camera_.get()), priority++);

	// Player
	int playerentity = ecsmanager_->CreateEntity();

	rect = { 0,0,26,26 }; // Removed top pixel due to a black line showing up when rotating
						  //path = "media\\sprites\\shooter.png";
	
	auto playerequipment = std::make_unique<EquipmentComponent>();
	playerequipment->AddEquipment(std::unique_ptr<Item>(new Item("sword", MAINHAND, 0, ItemStats(10, 20))));

	auto playerspellbook = std::make_unique<SpellbookComponent>();
	Spell test = spellbook_->GetSpell(0);
	playerspellbook->AddSpell(spellbook_->GetSpell(0));

	path = "../../../media/sprites/Player2.png";

	ecsmanager_->AddComponentToEntity<PositionComponent>(playerentity, (SCREEN_WIDTH / 2) - (34 / 2), 400);
	ecsmanager_->AddComponentToEntity<InputComponent>(playerentity);
	ecsmanager_->AddComponentToEntity<VelocityComponent>(playerentity, 0, 0);
	ecsmanager_->AddComponentToEntity<RenderComponent>(playerentity, path, rect, 0.0);
	ecsmanager_->AddComponentToEntity<BoundingRectangleComponent>(playerentity, (SCREEN_WIDTH / 2) - (34 / 2) + 8, 400 + 8, 24, 24); // TODO Magic Numbers
	ecsmanager_->AddComponentToEntity<SpellCastingComponent>(playerentity);
	ecsmanager_->AddComponentToEntity(playerentity, std::move(playerequipment));
	ecsmanager_->AddComponentToEntity<RPGStatsComponent>(playerentity);
	ecsmanager_->AddComponentToEntity(playerentity, std::move(playerspellbook));
	ecsmanager_->AddComponentToEntity<TargetingComponent>(playerentity);
	ecsmanager_->AssignEntityTag(playerentity, "PLAYER");

	CameraSystem* camerasystem = static_cast<CameraSystem*>(ecsmanager_->GetSystem(cameraindex));
	if (camerasystem != nullptr)
		camerasystem->SetFocus(playerentity);
	else
		std::cout << "Failed to set camera focus, camera doesnt exist" << std::endl;

	path = "../../../media/sprites/Pawns.png";
	// Monster
	int monsterentity;
	int mod;
	for (int j = 0; j < 10; j++)
		for (int i = 0; i < 10; i++)
		{
			monsterentity = ecsmanager_->CreateEntity();
			int mod = 0;
			if (j % 2 == 0) mod = 1;
			rect = { (i % 5) * 22,mod * 28,22,28 };
			ecsmanager_->AddComponentToEntity<PositionComponent>(monsterentity, (50 + i * 40) + i * 23, 50 + j * 29); // TODO MAgic numbers
			ecsmanager_->AddComponentToEntity<VelocityComponent>(monsterentity, 0, 0 );
			ecsmanager_->AddComponentToEntity<BoundingRectangleComponent>(monsterentity, (55 + i * 40) + i * 23, 55 + j * 29, 20, 21);//30,30
			ecsmanager_->AddComponentToEntity<RenderComponent>(monsterentity, path, rect, 0.0 );
			ecsmanager_->AssignEntityTag(monsterentity, "MONSTER");
			//std::cout << monsterentity << std::endl;
			// EKNOTE Would actually check this in the future even though for one frame idk if it matters
			//ecsmanager->AssignEntityTag(monsterentity, "ONSCREEN");
		}
	int i = 18;
	int j = 12;
	monsterentity = ecsmanager_->CreateEntity();
	int mod2 = 0;
	if (j % 2 == 0) mod2 = 1;
	rect = { (i % 5) * 22,mod2 * 28,22,28 };
	ecsmanager_->AddComponentToEntity<PositionComponent>(monsterentity, (50 + i * 40) + i * 23, 50 + j * 29 ); // TODO MAgic numbers
	ecsmanager_->AddComponentToEntity<VelocityComponent>(monsterentity, 0, 0 );
	ecsmanager_->AddComponentToEntity<BoundingRectangleComponent>(monsterentity, (55 + i * 40) + i * 23, 55 + j * 29, 20, 21);//30,30
																																 //ecsmanager->AddComponentToEntity(monsterentity, new CollisionComponent());
	ecsmanager_->AddComponentToEntity<RenderComponent>(monsterentity, path, rect, 0.0 );
	ecsmanager_->AssignEntityTag(monsterentity, "MONSTER");
	//std::cout << monsterentity << std::endl;
	// EKNOTE Would actually check this in the future even though for one frame idk if it matters
	//ecsmanager->AssignEntityTag(monsterentity, "ONSCREEN");

#ifdef FOO
	int treeentity;
	treeentity = ecsmanager->CreateEntity();
	rect = { 0,0,222,223 };
	path = "..\\..\\..\\media\\sprites\\tree.png";
	ecsmanager->AddComponentToEntity(treeentity, new PositionComponent(300, 300)); // TODO MAgic numbers
	ecsmanager->AddComponentToEntity(treeentity, new RenderComponent(path, rect));
	ecsmanager->AddComponentToEntity(treeentity, new BoundingRectangleComponent(411, 411, 40, 40));
	ecsmanager->AssignEntityTag(treeentity, "STATICOBJECT");
	std::cout << treeentity << std::endl;
#endif
}

void GameRunningState::TransitionIntoState()
{
    std::cout << "Game Running: Transition Into State" << std::endl;
    SetCurrentState(UPDATE);
}

void GameRunningState::UpdateState(int elapsedtime)
{
	ecsmanager_->Update(elapsedtime);
    //objectmanager_->Update(elapsedtime);
    //hudmanager_->Update();
}

void GameRunningState::TransitionFromState()
{
    std::cout << "Game Running: Transition From State" << std::endl;

    std::cout << "Game Running: Exit State" << std::endl;
    SetCurrentState(EXIT);
}



