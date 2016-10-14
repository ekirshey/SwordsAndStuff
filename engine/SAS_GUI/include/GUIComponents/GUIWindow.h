#pragma once
#include <string>
#include <vector>
#include <memory>
#include "GUIComponent.h"
#include "Input/Input.h"
#include "Rendering/Renderer.h"
#include "GUIViews/WindowView.h"

namespace SAS_GUI {
	class GUIWindow
	{
	public:
		GUIWindow( SAS_System::Renderer* renderer, std::string windowname, const WindowView& view, bool open = false);

		~GUIWindow();

		void Update(int elapsedtime, const SAS_System::Input& input);
		void Render(SAS_System::Renderer* renderer);

		template<typename T, typename... Args>
		void AddComponent(Args&&... args) {
			guicomponents_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		}

		void AddComponent(std::unique_ptr<GUIComponent> component) {
			guicomponents_.push_back(std::move(component));
		}

		bool IsOpen() { return open_; }
		void OpenWindow() { open_ = true; }
		void CloseWindow() { open_ = false; }
		void ToggleWindow() { open_ = !open_; }

	private:
		std::string windowname_;
		WindowView view_;
		int tabindex_;

		std::vector<std::unique_ptr<GUIComponent>> guicomponents_;
		int guitexture_;
		bool open_;
	};

}