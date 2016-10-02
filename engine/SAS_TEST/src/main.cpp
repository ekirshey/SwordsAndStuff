#include <iostream>
#include <memory>
#include "SystemControl.h"
#include "Renderer.h"
#include "GUIManager.h"
#include "GUIComponents/GUIWindow.h"
#include "GUIComponents/GUIButton.h"
#include "GUIComponents/DynamicText.h"
#include "Model.h"
#include "GUIDynamics/Dynamics.h"

struct SomeData {
	void dataFunc() {
		std::cout << _a << " " << _b << " " << _c << std::endl;
	}

	int _a;
	double _b;
	std::string _c;

	SomeData(int a, double b, std::string c) : _a(a), _b(b), _c(c) {}
};

class FooModel : public SAS_GUI::Model {
public:
	enum DataKeys {CVAL = 0};
	FooModel(SomeData* data)
		: _data(data)
	{}

	const std::string& getValue(int key) override {
		if (key == DataKeys::CVAL)
			return _data->_c;
		else
			return "N/A";
	}

	void callFunction(int key) override {
		someFunc();
	}

	void updateValue(int key, std::string value) override {

	}

private:
	void someFunc() {
		if (_data)
			_data->dataFunc();
	}

	SomeData* _data;
};




int main(int argc, char* argv[])
{
	SAS_System::InitializeSystem();
	SAS_System::Renderer renderer(600, 600);
	SAS_System::Input input;
	SAS_System::geti();

	SAS_GUI::GUIManager guimanager;
	SAS_GUI::ButtonView bv(SDL_Rect{ 200, 200, 60, 20 }, SDL_Rect{ 0,0,60,20 },
		"E:\\Github\\SwordsAndStuff\\media\\buttons\\startbutton.bmp");
	SAS_GUI::TextView tv(18, SDL_Color{ 255,0,0 }, "E:\\Github\\SwordsAndStuff\\media\\font.ttf", SDL_Rect{0,200,100,100});
	
	SomeData imp(5, 32.5, "someData");

	SAS_GUI::vec_pUpdate updatemods; 
	//updatemods.push_back(std::move(std::make_unique<SAS_GUI::VerticalBounceModule>(200)));
	//updatemods.push_back(std::move(std::make_unique<SAS_GUI::HorizontalBounceModule>(200)));
	
	SAS_GUI::vec_pInput inputmods; 
	inputmods.push_back(std::move(std::make_unique<SAS_GUI::HoverModule>(SDL_Rect{ 0,0,60,20 }, SDL_Rect{ 0,20,60,20 })));

	auto window = std::make_unique<SAS_GUI::GUIWindow>(&renderer, "mainmenu", SDL_Rect{ 0, 0, 1280, 640 }, "E:\\Github\\SwordsAndStuff\\media\\backgrounds\\mainmenubg.bmp", 
		"E:\\Github\\SwordsAndStuff\\media\\backgrounds\\mainmenubg.bmp", true);

	SAS_GUI::Dynamics i(
		std::move(updatemods),
		std::move(inputmods)
		);

	window->AddComponent<SAS_GUI::GUIButton>(bv, std::unique_ptr<SAS_GUI::Model>(new FooModel(&imp)), 0, std::move(i));
	window->AddComponent<SAS_GUI::DynamicText>(tv, std::unique_ptr<SAS_GUI::Model>(new FooModel(&imp)), FooModel::DataKeys::CVAL);

	guimanager.AddWindow(std::move(window));

	bool quit = false;
	std::string stream = "";
	int mousex, mousey;
	int textid = renderer.CreateTargetTexture(600, 600);
	int currenttime = 0;

	while (!quit) {
		SAS_System::seti(SAS_System::geti() + 1);
		currenttime = SAS_System::CurrentTicks();
		renderer.ClearScreen();
		SAS_System::UpdateInput(&input);
		quit = input.Quit();

		guimanager.Update(SAS_System::CurrentTicks(), input);
		guimanager.Render(&renderer);

#ifdef GUIONLYTEST

		renderer.ClearTargetTexture(textid);
		if (input.isKeyReleased(SDL_SCANCODE_A) ){
			std::cout << "Pressed A" << std::endl;
			input.startRecordingTextInput(10, &stream);
		}

		if (input.isKeyReleased(SDL_SCANCODE_L) ){
			std::cout << "Pressed A" << std::endl;
			input.stopRecordingTextInput(&stream);
		}

		if (input.leftMousePressed()) {
			std::cout << "Left Mouse pressed" << std::endl;
		}

		if (input.leftMouseReleased()) {
			std::cout << "Left Mouse released" << std::endl;
		}
		
		input.getMouseState(mousex, mousey);

		renderer.SetRenderTarget(textid);
		renderer.RenderText(std::to_string(mousex), 100, 200, 12, SDL_Color{ 255,0,0 }, "E:\\GitHub\\SwordsAndStuff\\media\\font.ttf");
		renderer.RenderText(std::to_string(mousey), 100, 250, 12, SDL_Color{ 255,0,0 }, "E:\\Github\\SwordsAndStuff\\media\\font.ttf");
		renderer.DefaultRenderTarget();

//		renderer.RenderTargetTexture(textid, 0, 0);

		renderer.RenderText(stream, 300, 200, 12, SDL_Color{ 255,0,0 }, "E:\\Github\\SwordsAndStuff\\media\\font.ttf");
		renderer.RenderFillRectangle(SDL_Rect{ 50, 50, 50, 50 }, SDL_Color{ 255, 0, 0, 255 });
		renderer.RenderText("FooBar", 100, 100, 12, SDL_Color{ 255,0,0,255 },"E:\\Github\\SwordsAndStuff\\media\\font.ttf");
		SDL_Rect r = { 0,0,50,50 };
		renderer.RenderImage("E:\\Github\\SwordsAndStuff\\media\\sprites\\Pawns.png", 300, 300, &r);
#endif

		renderer.Update();

		imp._c = std::to_string(1000/ (SAS_System::CurrentTicks() - currenttime));
	}

	return 0;
}
