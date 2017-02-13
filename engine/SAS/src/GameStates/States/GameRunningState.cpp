#include <iostream>
#include "GameStates/States/GameRunningState.h"
#include "SubSystems/MonsterSpawner.h"
#include "Config/GameDefines.h"

#include "Systems/RenderSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/SpellCreationSystem.h"
#include "Systems/MeleeSystem.h"
#include "Systems/AISystem.h"
#include "Systems/ScriptedEntitySystem.h"
#include "Systems/EquipmentSystem.h"
#include "Systems/InventorySystem.h"
#include "Systems/TimeToLiveSystem.h"

#include "Components/BoundingRectangleComponent.h"
#include "Components/RenderComponent.h"
#include "Components/PositionComponent.h"
#include "Components/InputComponent.h"
#include "Components/AngleComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/SpellCastingComponent.h"
#include "Components/SpellbookComponent.h"
#include "Components/StatsComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/EquipmentComponent.h"

#include "Types/MessageTypes.h"

#include "Types/DamageAttributes.h"
#include "GameMechanics/StatGenerator.h"

// GUI Components
#include "GUIComponents/Container.h"

#include "Types/PlayerInfo.h"


using namespace Items;
GameRunningState::GameRunningState(const GeneralConfig& config, PlayerInfo* playerinfo)
	: _generalconfig(config)
	, _nextstate(GameStates::MAINMENU_IDX)
	, _playerinfo(playerinfo)
{
}

GameRunningState::~GameRunningState()
{

}

int GameRunningState::InitializeState(SAS_System::Renderer& renderer, const SAS_System::Input& input) {
	SDL_Rect camerarect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    // Create Game World and Camera
    _gameworld = std::make_unique<GameWorld>(renderer, 3072,2560, _generalconfig.mediaroot);
    _gameworld->BuildProceduralTileMap(32);
	_gameworld->BuildTileMapTexture(&renderer);

    _camera = std::make_unique<Camera>(3072, 2560, camerarect);

	_itemdatabase = std::make_unique<Items::ItemDatabase>();

	// Set up Game Data
	_spellbook = std::make_unique<GlobalSpellbook>();
	// Name, Cast time, cooldown, duration (milliseconds)
	// Account for anchor orientation in script
	// Vector of vectors: each vector is the script steps for a facing
	_spellbook->CreateSpellShape<Projectile>(0, 10);
	_spellbook->CreateSpellComponent<SpellDamage>(0, DamageAttributes::FIRE, 50.0);
	_spellbook->CreateSpell(0, "PROJECTILE", 0, false, 250, 1000, _generalconfig.mediaroot + "sprites/sword.png", 0, std::vector<int>{0});
/*
	ScriptedMotion::Script spellscript = {
		{ ScriptStep(0,0,50), ScriptStep(-5,5,50), ScriptStep(-10,10,200) },
		{ ScriptStep(0,0,50), ScriptStep(-5,5,50), ScriptStep(-10,10,200) },
		{ ScriptStep(8,0,50), ScriptStep(13,5,50), ScriptStep(18,10,200) },
		{ ScriptStep(0,0,50), ScriptStep(-5,5,50), ScriptStep(-10,10,200) }
	};
	_spellbook->CreateSpell(0, "MELEE", 0, 100, 300, _generalconfig.mediaroot + "sprites/sword.png", spellscript);
*/

	// Set up ECS. This was originally in some wrapper object and I dont know why I did that...
	_ecsmanager = std::make_unique<ECSManager>();
	this->initializeECS(renderer, input);

	// Set up the gui
	_guimanager = std::make_unique<SAS_GUI::GUIManager>();
	SAS_GUI::WindowView wv(SDL_Rect{0,0,400,400}, _generalconfig.mediaroot + "backgrounds\\inventory.bmp");
	auto invwin = std::make_unique<SAS_GUI::Window>(SDL_Rect{ 100,100,400,400 }, &renderer, "inventory", wv,  false);

	SAS_GUI::ContainerView cv(SDL_Rect{ 0,0,400,200}, 2, 5, 16, 16, 19, 8, _generalconfig.mediaroot + "backgrounds\\inventorycontainer.bmp");
	invwin->AddComponent<SAS_GUI::Container>(1, 1, SDL_Rect{ 0,200,400,200 }, cv);

	SAS_GUI::WindowView wv2(SDL_Rect{0,0,400,400}, _generalconfig.mediaroot + "backgrounds\\inventory.bmp");
	auto invwin2 = std::make_unique<SAS_GUI::Window>(SDL_Rect{ 700,100,400,400 }, &renderer, "inventory", wv2,  false);

	SAS_GUI::ContainerView cv2(SDL_Rect{ 0,0,400,200}, 2, 5, 16, 16, 19, 8, _generalconfig.mediaroot + "backgrounds\\inventorycontainer.bmp");
	invwin2->AddComponent<SAS_GUI::Container>(2, 1, SDL_Rect{ 0,200,400,200 }, cv2);

	_guimanager->AddWindow(std::move(invwin), SDL_SCANCODE_I);
	_guimanager->AddWindow(std::move(invwin2), SDL_SCANCODE_G);
	
	return TRANSITIONIN;
}

void GameRunningState::initializeECS(SAS_System::Renderer& renderer, const SAS_System::Input& input)
{
	SDL_Rect rect;
	std::string path;
	int priority = 0;
	int cameraindex = 0;

	_ecsmanager->AddQueue("SpellCreation");
	_ecsmanager->AddQueue("EquipmentManagement");
	_ecsmanager->AddQueue("InventoryManagement");

	// Build systems and entities
	//_ecsmanager->AddSystem(std::unique_ptr<AISystem>(new AISystem()), priority++);
	_ecsmanager->AddSystem<TimeToLiveSystem>("TTLSystem", priority++);
	_ecsmanager->AddSystem<MovementSystem>("MovementSystem", priority++, _gameworld.get());
	_ecsmanager->AddSystem<ScriptedEntitySystem>("ScriptedEntitySystem", priority++);	// Not 100% sure on the placement 
	_ecsmanager->AddSystem<SpellCreationSystem>("SpellCreationSystem", priority++, _ecsmanager->GetQueue("SpellCreation"));
	_ecsmanager->AddSystem<CollisionSystem>("CollisionSystem", priority++, _gameworld.get());
	//_ecsmanager->AddSystem<PlayerTargetingSystem>("PlayerTargetingSystem", priority++, _gameworld.get() , "..\\..\\..\\reticule.png");
	_ecsmanager->AddSystem<EquipmentSystem>("EquipmentSystem", priority++, _ecsmanager->GetQueue("EquipmentManagement"));
	_ecsmanager->AddSystem<InventorySystem>("InventorySystem", priority++, _ecsmanager->GetQueue("InventoryManagement"));
	_ecsmanager->AddSystem<RenderSystem>("RenderSystem", priority++, &renderer, _gameworld.get(), _camera.get());
	// Player
	_player = _ecsmanager->CreateEntity();
	auto targetreticuleid = _ecsmanager->CreateEntity();
	_inputhandler = std::make_unique<PlayerInput>(_player, targetreticuleid, _gameworld.get());
	
	// Build target reticule
	SDL_Rect targetrect = { 0,0,26,26 };
	_ecsmanager->AddComponentToEntity<PositionComponent>(targetreticuleid, -100, -100); 
	_ecsmanager->AddComponentToEntity<RenderComponent>(targetreticuleid, _generalconfig.mediaroot + "reticule.png", targetrect, 0.0);

	rect = { 0,0,26,26 }; // Removed top pixel due to a black line showing up when rotating
						  //path = "sprites\\shooter.png";

	auto playerspellbook = std::make_unique<SpellbookComponent>();
	GlobalSpellbook::SpellReference test = _spellbook->GetSpell(0);
	if (test != nullptr)
		playerspellbook->AddSpell(0, test);

	path = _generalconfig.mediaroot + "sprites/Player2.png"; 
	StatGenerator generator("something");
	StatsComponent stats = generator.GenerateStats(_playerinfo->mainstats);

	_ecsmanager->AddComponentToEntity<PositionComponent>(_player, (SCREEN_WIDTH / 2) - (34 / 2), 400);
	_ecsmanager->AddComponentToEntity<InputComponent>(_player);
	_ecsmanager->AddComponentToEntity<VelocityComponent>(_player, 0, 0);
	_ecsmanager->AddComponentToEntity<RenderComponent>(_player, path, rect, 0.0);
	_ecsmanager->AddComponentToEntity<BoundingRectangleComponent>(_player, (SCREEN_WIDTH / 2) - (34 / 2) + 8, 400 + 8, 24, 24); // TODO Magic Numbers
	_ecsmanager->AddComponentToEntity<SpellCastingComponent>(_player);
	_ecsmanager->AddComponentToEntity<EquipmentComponent>(_player);
	_ecsmanager->AddComponentToEntity<InventoryComponent>(_player, 10);
	_ecsmanager->AddComponentToEntity<StatsComponent>(_player, stats);
	_ecsmanager->AddComponentToEntity(_player, std::move(playerspellbook));
	_ecsmanager->AssignEntityTag(_player, "PLAYER");

	///////////////////////////////////////
	// Initialize camera to focus on player
	auto playerpos = _ecsmanager->GetEntityComponent<PositionComponent*>(_player, PositionComponentID);
	auto playervel = _ecsmanager->GetEntityComponent<VelocityComponent*>(_player, VelocityComponentID);
	_camera->setFocus(playerpos, playervel);

/* Example of adding an item
	Items::Item* itemptr = _itemdatabase->CreateItem(
		Items::ItemStats(),
		Items::ItemProperties(),
		Items::ItemLore("sword", "sharp sword"),
		Items::ItemTriggers());

	_ecsmanager->SendMessage<ItemMessage>("InventoryManagement", _player, itemptr, ADDITEM);

*/

	path = _generalconfig.mediaroot + "sprites/Pawns.png";
	// Monster
	int monsterentity;
	for (int j = 0; j < 10; j++)
		for (int i = 0; i < 10; i++)
		{
			monsterentity = _ecsmanager->CreateEntity();
			int mod = 0;
			if (j % 2 == 0) mod = 1;
			rect = { (i % 5) * 22,mod * 28,22,28 };
			_ecsmanager->AddComponentToEntity<PositionComponent>(monsterentity, (50 + i * 40) + i * 23, 50 + j * 29); // TODO MAgic numbers
			_ecsmanager->AddComponentToEntity<VelocityComponent>(monsterentity, 0, 0 );
			_ecsmanager->AddComponentToEntity<BoundingRectangleComponent>(monsterentity, (55 + i * 40) + i * 23, 55 + j * 29, 20, 21);//30,30
			_ecsmanager->AddComponentToEntity<RenderComponent>(monsterentity, path, rect, 0.0 );
			_ecsmanager->AddComponentToEntity<StatsComponent>(monsterentity, stats);
			_ecsmanager->AssignEntityTag(monsterentity, "MONSTER");
			//std::cout << monsterentity << std::endl;
			// EKNOTE Would actually check this in the future even though for one frame idk if it matters
			//ecsmanager->AssignEntityTag(monsterentity, "ONSCREEN");
		}
	int i = 18;
	int j = 12;
	monsterentity = _ecsmanager->CreateEntity();
	int mod2 = 0;
	if (j % 2 == 0) mod2 = 1;
	rect = { (i % 5) * 22,mod2 * 28,22,28 };
	_ecsmanager->AddComponentToEntity<PositionComponent>(monsterentity, (50 + i * 40) + i * 23, 50 + j * 29 ); // TODO MAgic numbers
	_ecsmanager->AddComponentToEntity<VelocityComponent>(monsterentity, 0, 0 );
	_ecsmanager->AddComponentToEntity<BoundingRectangleComponent>(monsterentity, (55 + i * 40) + i * 23, 55 + j * 29, 20, 21);//30,30
																																 //ecsmanager->AddComponentToEntity(monsterentity, new CollisionComponent());
	_ecsmanager->AddComponentToEntity<RenderComponent>(monsterentity, path, rect, 0.0 );
	_ecsmanager->AssignEntityTag(monsterentity, "MONSTER");
	//std::cout << monsterentity << std::endl;
	// EKNOTE Would actually check this in the future even though for one frame idk if it matters
	//ecsmanager->AssignEntityTag(monsterentity, "ONSCREEN");

#ifdef FOO
	int treeentity;
	treeentity = ecsmanager->CreateEntity();
	rect = { 0,0,222,223 };
	path = "..\\..\\..\\sprites\\tree.png";
	ecsmanager->AddComponentToEntity(treeentity, new PositionComponent(300, 300)); // TODO MAgic numbers
	ecsmanager->AddComponentToEntity(treeentity, new RenderComponent(path, rect));
	ecsmanager->AddComponentToEntity(treeentity, new BoundingRectangleComponent(411, 411, 40, 40));
	ecsmanager->AssignEntityTag(treeentity, "STATICOBJECT");
	std::cout << treeentity << std::endl;
#endif
}

int GameRunningState::UpdateState(int elapsedtime, SAS_System::Renderer& renderer, const SAS_System::Input& input) {
	int ret = UPDATE;
	int errorcode;

	if (_ecsmanager->GetStatus(errorcode) && !input.isKeyPressed(SDL_SCANCODE_ESCAPE)) {	// State test

		if (input.isKeyPressed(SDL_SCANCODE_1) || input.isKeyPressed(SDL_SCANCODE_2) || 
			input.isKeyPressed(SDL_SCANCODE_3) || input.isKeyPressed(SDL_SCANCODE_4)) {
			SAS_GUI::Message msg;
			SAS_GUI::Payload data;
			data.cliprect = SDL_Rect{ 0,0,16,16 };
			data.type = 1;
			data.description = "test";
			if (input.isKeyPressed(SDL_SCANCODE_1))
				data.texture = _generalconfig.mediaroot + "sprites\\swordicon.bmp";
			else
				data.texture = _generalconfig.mediaroot + "sprites\\shieldicon.bmp";

			if (input.isKeyPressed(SDL_SCANCODE_3) || input.isKeyPressed(SDL_SCANCODE_4))
				msg.destid = 2;
			else
				msg.destid = 1;

			msg.messagetype = SAS_GUI::MESSAGETYPE::ADD;
			msg.senderid = 2;
			msg.data = data;
			_guimanager->ReceiveMessage(msg);
		}
		_inputhandler->UpdateInput(_ecsmanager.get(), input);
		// Move the camera
		_camera->Update();
		// Update ECS
		_ecsmanager->Update(elapsedtime);

		// GUI Manager update
		_guimanager->Update(elapsedtime, input);
		_guimanager->Render(&renderer);
	}
	else {
		ret = TRANSITIONOUT;
	}

//#ifdef DEBUGINFO
	//renderer.RenderText(std::to_string(_ecsmanager->EntityCount()), renderer.ScreenWidth()-150, 60, 20, SDL_Color{ 255,255,255,255 }, "F:\\github\\SwordsAndStuff\\media\\font.TTF");
//#endif
	return ret;
}

int GameRunningState::TransitionIntoState(SAS_System::Renderer& renderer) {
    std::cout << "Game Running: Transition Into State" << std::endl;
	return UPDATE;
}


int GameRunningState::TransitionFromState(SAS_System::Renderer& renderer) {
    std::cout << "Game Running: Transition From State" << std::endl;

    std::cout << "Game Running: Exit State" << std::endl;
	return EXIT;
}
