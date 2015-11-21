#include "..\..\..\include\GUI\GUIComponents\GUIWindow.h"

GUIWindow::GUIWindow(std::string windowname, SDL_Rect windowrect,
	std::string focusedwindowtexture, std::string unfocusedwindowtexture) 
	: windowname_(windowname), windowrect_(windowrect), 
	focusedwindowtexture_(focusedwindowtexture), unfocusedwindowtexture_(unfocusedwindowtexture),
	windowopen_(false)
{

}


GUIWindow::~GUIWindow()
{
}
