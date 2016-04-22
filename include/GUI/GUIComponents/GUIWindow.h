#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SDL_Rect.h"
#include "GUIComponent.h"
#include "../../SDL/SDLManager.h"

class GUIWindow
{
public:
	GUIWindow(SDLManager* sdlmanager, std::string windowname, SDL_Rect windowrect,
		std::string focusedwindowtexture, std::string windowtexture, bool open = false);
	~GUIWindow();

	void Update(int elapsedtime);
	
	template<typename T, typename... Args>
	void AddComponent(Args... args) {
		guicomponents_.push_back(std::make_unique<T>(args...));
	}

	bool IsOpen() { return open_; }
	void OpenWindow() { open_ = true; }
	void CloseWindow() { open_ = false; }
	void ToggleWindow() { open_ = !open_; }

private:
	bool open_;
	std::string windowname_;
	SDL_Rect windowrect_;

	// Textures
	std::string focusedwindowtexture_;
	std::string windowtexture_;

	SDLManager* sdlmanager_;
	SDL_Texture* guitexture_;
	std::vector<std::unique_ptr<GUIComponent>> guicomponents_;
};

