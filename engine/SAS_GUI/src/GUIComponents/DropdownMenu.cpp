#include <iostream>
#include "DropdownMenu.h"
#include "GUIUtils.h"

namespace SAS_GUI {
	DropdownMenu::DropdownMenu(SAS_System::Renderer& renderer, SDL_Rect position, const DropdownMenuView& dropdownview, std::vector<std::string> menuitems) 
		: _position(position)
		, _dropdownview(dropdownview)
		, _menuitems(menuitems)
		, _dropdowntextureid(-1)
		, _dropdownopen(false)
		, _selectedvalue(0)
		, _hoveredvalue(0)
		, _hovered(false)
		, _menuposition(SDL_Rect{_position.x, _position.y + _position.h, _position.w, static_cast<int>(_dropdownview.textview.fontsize * _menuitems.size())})
	{
		_dropdowntextureid = renderer.CreateTargetTexture(_menuposition.w, _menuposition.h);
		renderer.SetTextureBlendMode(_dropdowntextureid, SDL_BLENDMODE_BLEND);
		renderer.SetRenderTarget(_dropdowntextureid);
		
		// Clear texture
		renderer.FillRenderingTarget(SDL_Color{0,0,0,0});

		// When rendering to a texture you use coordinates relative to the new texture
		for (int i = 0; i < _menuitems.size(); i++) {
			renderer.RenderText(_menuitems[i], 0 , _dropdownview.textview.fontsize * i, 
				_dropdownview.textview.fontsize, 
				_dropdownview.textview.fontcolor, 
				_dropdownview.textview.fontpath);
		}
		
		renderer.DefaultRenderTarget();
	}

	void DropdownMenu::Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) {
		int x;
		int y;
		input.getMouseState(x, y);
		
		_hovered = false;
		if (_dropdownopen) {
			if (UTILS::isMouseOver(windowrect, _menuposition, x, y)) {
				_hoveredvalue = (y - _menuposition.y) / _dropdownview.textview.fontsize;
				_hovered = true;
				if (input.leftMouseReleased()) {
					_dropdownopen = false;
					_selectedvalue = _hoveredvalue;
				}
			}
		}

		if (UTILS::isMouseOver(windowrect, _position, x, y)) {
			_hoveredvalue = -1;
			_hovered = true;
		}

		// Update the model based on input
		if (input.leftMouseReleased()) {
			if (UTILS::isMouseOver(windowrect, _position, x, y)) {
				_dropdownopen = true;
			}
			else 
				_dropdownopen = false;
		}
	}

	void DropdownMenu::Render(SAS_System::Renderer* renderer) {
		renderer->RenderFillRectangle(_position , _dropdownview.menucolor);
		if (_hovered && _hoveredvalue == -1) 
			renderer->RenderFillRectangle(_position, _dropdownview.highlightcolor);
		renderer->RenderText(_menuitems[_selectedvalue], _position.x, _position.y,
						_dropdownview.textview.fontsize, 
						_dropdownview.textview.fontcolor, 
						_dropdownview.textview.fontpath);

		if (_dropdownopen) {
			renderer->RenderFillRectangle(_menuposition, _dropdownview.dropdowncolor);
			// Render highlight
			if (_hovered && _hoveredvalue > -1) {
				auto highlight = _menuposition;
				highlight.y = _menuposition.y + (_hoveredvalue * _dropdownview.textview.fontsize);
				highlight.h = _dropdownview.textview.fontsize;
				renderer->RenderFillRectangle(highlight, _dropdownview.highlightcolor);
			}
			renderer->RenderTargetTexture(_dropdowntextureid, _menuposition.x, _menuposition.y);

		}
	}
}