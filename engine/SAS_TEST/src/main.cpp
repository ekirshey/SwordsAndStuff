#include <iostream>
#include <memory>
#include "SystemControl.h"
#include "Renderer.h"
#include "GUIManager.h"
#include "GUIComponents/GUIWindow.h"
#include "GUIComponents/GUIButton.h"
#include "GUIComponents/TextBox.h"
#include "GUIComponents/DynamicText.h"
#include "Model.h"
#include "GUIDynamics/Dynamics.h"

const std::string laptoppath  = "C:\\cygwin64\\home\\prome\\code\\SwordsAndStuff\\";
const std::string desktoppath = "D:\\Github\\SwordsAndStuff\\";

#ifdef LAPTOP
	std::string path = laptoppath;
#else
	std::string path = desktoppath;
#endif


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

std::unique_ptr<SAS_GUI::Model> FooModelFactory(SomeData* data) {
	return std::unique_ptr<SAS_GUI::Model>(new FooModel(data));
}


int main(int argc, char* argv[])
{
	SAS_System::InitializeSystem();
	SAS_System::Renderer renderer(600, 600);
	SAS_System::Input input;

	SAS_GUI::GUIManager guimanager;
	SAS_GUI::ButtonView bv(SDL_Rect{ 200, 200, 60, 20 }, SDL_Rect{ 0,0,60,20 },
		path + "media\\buttons\\startbutton.bmp");
	SAS_GUI::TextView tv(18, SDL_Color{ 255,0,0 }, path + "media\\font.ttf", SDL_Rect{0,200,100,100});
	
	SomeData imp(5, 32.5, "someData");

	SAS_GUI::vec_pUpdate updatemods; 
	//updatemods.push_back(std::move(std::make_unique<SAS_GUI::VerticalBounceModule>(200)));
	//updatemods.push_back(std::move(std::make_unique<SAS_GUI::HorizontalBounceModule>(200)));
	
	SAS_GUI::vec_pInput inputmods; 
	inputmods.push_back(std::make_unique<SAS_GUI::HoverModule>(SDL_Rect{ 0,0,60,20 }, SDL_Rect{ 0,20,60,20 }));
	SAS_GUI::WindowView wv(SDL_Rect{ 0,0,600,600 }, SDL_Rect{0,0,1280,640}, path + "media\\backgrounds\\mainmenubg.bmp");
	auto window = std::make_unique<SAS_GUI::GUIWindow>(&renderer, "mainmenu", wv,  true);

	window->AddComponent<SAS_GUI::GUIButton>(bv, FooModelFactory(&imp), 0, SAS_GUI::Dynamics(std::move(updatemods), std::move(inputmods)));
	window->AddComponent<SAS_GUI::DynamicText>(tv, FooModelFactory(&imp), FooModel::DataKeys::CVAL);

	tv.position = SDL_Rect{ 400, 200, 60, 20 };
	window->AddComponent<SAS_GUI::TextBox>(tv);

	tv.position = SDL_Rect{ 400, 300, 60, 20 };
	window->AddComponent<SAS_GUI::TextBox>(tv);
	
	tv.position = SDL_Rect{ 400, 400, 60, 20 };
	window->AddComponent<SAS_GUI::TextBox>(tv);

	tv.position = SDL_Rect{ 400, 500, 60, 20 };
	window->AddComponent<SAS_GUI::TextBox>(tv);

	SAS_GUI::WindowView wv2(SDL_Rect{ 400,400,200,200 }, SDL_Rect{0,0,200,200}, path + "media\\backgrounds\\somemenu.bmp");
	auto window2 = std::make_unique<SAS_GUI::GUIWindow>(&renderer, "somewindow", wv2,  true);

	// Relative to window position? going with yes for now
	// What makes more sense?
	tv.position = SDL_Rect{ 20, 20, 60, 20 };
	window2->AddComponent<SAS_GUI::TextBox>(tv);

	guimanager.AddWindow(std::move(window));
	guimanager.AddWindow(std::move(window2));

	bool quit = false;
	std::string stream = "";
	int mousex, mousey;
	int textid = renderer.CreateTargetTexture(600, 600);
	int currenttime = 0;

	while (!quit) {
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
