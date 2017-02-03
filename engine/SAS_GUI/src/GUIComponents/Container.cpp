#include "Container.h"
#include "GUIUtils.h"
#include <iostream>

namespace SAS_GUI {

	Container::Container(int id, int itemtype, SDL_Rect position, const ContainerView& view)
		: _id(id)
		, _itemtype(itemtype)
		, _hovereditem(-1)
		, _selecteditem(-1)
		, _releasedItem(false)
		, _itemlifted(false)
		, _cursor(nullptr)
		, _clearCursor(false)
		, _position(position)
		, _view(view)
		, _items(_view.maxHorizontalSlots * _view.maxVerticalSlots)
		, _openslot(0)
	{

	}

	int Container::_getHoveredItem(int relativex, int relativey) {
		// Get the hovered/selected item
		// A better way??
		int xindex, yindex;
		int retval = -1;
		double x_d = static_cast<double>(relativex) / (_view.slotWidth + _view.horizontalSlotSeparation);
		int xremainder = ((x_d - static_cast<int>(x_d)) * (_view.slotWidth + _view.horizontalSlotSeparation));
		if ( xremainder >= _view.horizontalSlotSeparation) {
			xindex = static_cast<int>(x_d);
			double y_d = static_cast<double>(relativey) / (_view.slotHeight + _view.verticalSlotSeparation);
			int yremainder = ((y_d - static_cast<int>(y_d)) * (_view.slotHeight + _view.verticalSlotSeparation));
			if (yremainder >= _view.verticalSlotSeparation) {
				yindex = static_cast<int>(y_d);
				int tempselection = (yindex*_view.maxHorizontalSlots) + xindex;
				if (tempselection < _items.size())  {
					retval = tempselection;
				}
			}
		}
		return retval;
	}

	void Container::Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime) {
		int x, y;
		bool released = false;
		_releasedItem = false;
		input.getMouseState(x, y);
		// Deferred clear so any other container can still use the cursor contents
		if (_clearCursor) {
			if (!_cursor->locked) {
				_cursor->clear = true;
			}
			_clearCursor = false;
		}
		if (UTILS::isMouseOver(windowrect, _position, x, y)) {
			int relx = x - windowrect.x - _position.x;
			int rely = y - windowrect.y - _position.y;

			_hovereditem = _getHoveredItem(relx, rely);
			// Is item being held?
			if (_selecteditem != -1) {
				if (!input.leftMouseReleased()) {
					_hovereditem = -1;
					if (_cursor->clear) {
						_cursor->clear = false;
						_cursor->data = _items[_selecteditem];
					}
					_itemlifted = true;
					return;
				}
				else {
					_itemlifted = false;
					released = true;
					Payload temp;
					_cursor->locked = false;
					if (_hovereditem != -1 && _hovereditem < _items.size()) {
						temp = _items[_hovereditem];
						_items[_hovereditem] = _items[_selecteditem];
						_items[_selecteditem].type = EMPTY_PAYLOAD;
						if (temp.type != EMPTY_PAYLOAD) {
							_cursor->data = temp;
							_cursor->locked = true;
						}
						else {
							_clearCursor = true;
						}
					}

					_releasedItem = true;
				}
			}
			else if (!_cursor->clear && input.leftMouseReleased()) {
				// Received an item from a different container
				if (_hovereditem != -1) {
					if (_items[_hovereditem].type != EMPTY_PAYLOAD) {
						Payload temp;
						temp = _items[_hovereditem];
						_items[_hovereditem] = _cursor->data;
						_cursor->data = temp;
						_cursor->locked = true;
					}
					else {
						_items[_hovereditem] = _cursor->data;
						_cursor->locked = false;
						_clearCursor = true;
					}
				}
				else {
					_clearCursor = true;
				}

			}

			_selecteditem = -1;
			if (input.leftMousePressed() && _hovereditem != -1 
				&& _items[_hovereditem].type != EMPTY_PAYLOAD) 
			{
				_selecteditem = _hovereditem;
			}
		}
		else {
			_hovereditem = -1;
			if (_selecteditem != -1 && input.leftMouseReleased()) {
				_items[_selecteditem].type = EMPTY_PAYLOAD;
				if (_selecteditem < _openslot)
					_openslot = _selecteditem;
				_selecteditem = -1;
				_itemlifted = false;
				_releasedItem = true;
				// Only clear the cursor if you are in full control of where it's going. That is
				// why I'm not clearing it here.
			}
		}
	}

	void Container::Render(SAS_System::Renderer* renderer) {
		// Build container texture
		renderer->RenderImage(_view.texture, _position.x, _position.y, &_view.cliprect);

		// Optimize to a single texture?
		for (int i = 0; i < _items.size(); i++) {
			int row = (i / _view.maxHorizontalSlots);
			int xshift = i - (row*_view.maxHorizontalSlots);
			// Don't render if lifted item
			if ( (i != _selecteditem || !_itemlifted) && _items[i].type != EMPTY_PAYLOAD) {
				renderer->RenderImage(_items[i].texture
					, _position.x + _view.slotWidth * (xshift)+_view.horizontalSlotSeparation * (xshift + 1)
					, row*_view.slotHeight + _position.y + _view.verticalSlotSeparation * (row + 1)
					, &_items[i].cliprect);
			}
		}

		// Render selection box
		if ((_hovereditem != -1 && _items[_hovereditem].type != EMPTY_PAYLOAD) && !_itemlifted) {
			int row = (_hovereditem / _view.maxHorizontalSlots);
			int xshift = _hovereditem - (row*_view.maxHorizontalSlots);
			renderer->RenderOutlineRectangle(SDL_Rect{
												 _position.x + _view.slotWidth * (xshift) + _view.horizontalSlotSeparation * (xshift+1)
												, row*_view.slotHeight + _position.y + _view.verticalSlotSeparation * (row+1)
												, _view.slotWidth
												, _view.slotHeight
											}
											, SDL_Color{255,255,255,255});
		}
		
	}


	void Container::ReceiveMessages(const std::vector<Message>& messages, int messagect) {
		for (int i = 0; i < messagect; i++) {
			if (messages[i].destid == _id) {
				if (messages[i].data.type == _itemtype) {
					if (messages[i].messagetype == MESSAGETYPE::ADD) {
						if (_openslot < _items.size()) {
							while (_items[_openslot].type != EMPTY_PAYLOAD) _openslot++;
							_items[_openslot] = messages[i].data;
						}
					}
				}
			}
		}
	}

	void Container::RegisterCursor(Cursor* cursor) {
		_cursor = cursor;
	}

	void Container::SendExternalMessage(std::vector<Message>* messages) {

	}
}