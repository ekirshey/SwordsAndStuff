#pragma once
#include "Component.h"
#include "ContainerView.h"
#include "GUIMessaging.h"

namespace SAS_GUI {

	class Container : public Component {
		public:
			Container(int id, int itemtype, SDL_Rect position, const ContainerView& view);
			void Update(const SDL_Rect& windowrect, const SAS_System::Input& input, bool& hasFocus, int elapsedtime);
			void Render(SAS_System::Renderer* renderer);

			void ReceiveMessages(const std::vector<Message>& messages, int messagect);
			void SendInternalMessage(std::vector<Message>* messages);
			void SendExternalMessage(std::vector<Message>* messages);

		private:
			int _getHoveredItem(int relativex, int relativey);
			int _id;
			int _itemtype;
			int _hovereditem;
			int _selecteditem;
			bool _releasedItem;
			bool _itemlifted;
			SDL_Rect _position;
			ContainerView _view;
			std::vector <Payload> _items;
			int _openslot;

	};
}