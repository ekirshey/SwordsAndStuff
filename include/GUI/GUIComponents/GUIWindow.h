#pragma once
#include <string>
#include <vector>
#include <memory>
#include "SDL_Rect.h"
#include "GUIComponent.h"

class GUIWindow
{
public:
	GUIWindow(std::string windowname, SDL_Rect windowrect, 
		std::string focusedwindowtexture, std::string unfocusedwindowtextur);
	~GUIWindow();

	void Update();

private:
	bool windowopen_;
	std::string windowname_;
	SDL_Rect windowrect_;

	// Textures
	std::string focusedwindowtexture_;
	std::string unfocusedwindowtexture_;

	// Window Components
	std::vector<std::unique_ptr<GUIComponent>> guicomponents_;
};

