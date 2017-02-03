#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Component.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "GUIViews/WindowView.h"

namespace SAS_GUI {
	class Window
	{
	public:
		Window(SDL_Rect position, SAS_System::Renderer* renderer, std::string windowname, const WindowView& view, bool open = false);

		~Window();

		bool Update(int elapsedtime, const SAS_System::Input& input, std::vector<Message> receiveQueue, int queuesize);
		void Render(SAS_System::Renderer* renderer);

		template<typename T, typename... Args>
		void AddComponent(Args&&... args) {
			_guicomponents.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		}

		void AddComponent(std::unique_ptr<Component> component) {
			_guicomponents.push_back(std::move(component));
		}

		bool IsOpen() { return _open; }
		void OpenWindow() { _open = true; }
		void CloseWindow() { _open = false; }
		void ToggleWindow() { _open = !_open; }

		std::string WindowName() { return _windowname; }

		// For internal use
		void _registerInternalGUIQueue(std::vector<Message>* internalqueue) { _internalGUIQueue = internalqueue; }
		void _registerExternalGUIQueue(std::vector<Message>* externalqueue) { _externalGUIQueue = externalqueue; }
	private:
		SDL_Rect _position;
		std::string _windowname;
		WindowView _view;
		std::vector<Message>* _internalGUIQueue;
		std::vector<Message>* _externalGUIQueue;

		std::vector<std::unique_ptr<Component>> _guicomponents;
		int _guitexture;
		bool _open;
	};

}