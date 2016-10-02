#include "GUIUtils.h"

namespace SAS_GUI {
	namespace UTILS {
		bool isMouseOver(const SDL_Rect& windowrect, const SDL_Rect& position, int x, int y) {
			int relativeX = position.x + windowrect.x;
			int relativeY = position.y + windowrect.y;

			// Update the model based on input
			if (((x > relativeX) && (x < (position.w + relativeX))) &&
				((y > relativeY) && (y < (position.h + relativeY)))) {
				return true;
			}
			else
				return false;

		}
	}
}