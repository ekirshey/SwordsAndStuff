#include "..\..\include\GUI\GUIManager.h"
#include "..\..\include\SDL\SDLManager.h"

GUIManager::GUIManager()
{
}

GUIManager::GUIManager(SDLManager* sdlmanager, std::string keymapfile, std::string guifile) : sdlmanager_(sdlmanager)
{
	Initialize(keymapfile, guifile);
}

GUIManager::~GUIManager()
{
}

void GUIManager::Update()
{

}

void GUIManager::Initialize(std::string keymapfile, std::string guifile)
{
	// Build Windows


	// Load Keymap Data
}