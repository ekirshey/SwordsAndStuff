#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL.h>
#include "Geometry.h"
#include "Voronoi.h"

void fillTexture(SDL_Renderer *renderer, SDL_Texture *texture, int r, int g, int b, int a)
{
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, NULL);
}

void prepareForRendering(SDL_Renderer *renderer)
{
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
}

void checkSdlError()
{
	const char *sdlError = SDL_GetError();
	if (sdlError && *sdlError)
	{
		::std::cout << "SDL ERROR: " << sdlError << ::std::endl;
	}
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_HAPTIC);

	SDL_Window *window = SDL_CreateWindow("SDL test",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		720, 740,
		SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	const int width = 750;
	const int height = 750;

	::std::vector<SDL_Texture*> textures;

	SDL_Texture *redTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	textures.push_back(redTexture);

	SDL_Texture *greenTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	textures.push_back(greenTexture);

	SDL_Texture *purpleTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	textures.push_back(purpleTexture);

	// Here is setting the blend mode for each and every used texture:
	for (int i = 0; i < textures.size(); ++i)
	{
		SDL_SetTextureBlendMode(textures[i], SDL_BLENDMODE_BLEND);
	}

	int purpleAlpha = 0;

	fillTexture(renderer, redTexture, 255, 0, 0, 255);
	fillTexture(renderer, greenTexture, 0, 255, 0, 128);
	fillTexture(renderer, purpleTexture, 255, 0, 255, purpleAlpha);

	prepareForRendering(renderer);

	std::vector<SAS_Utils::Point> points;
	SAS_Utils::VoronoiDiagram vd;
	points.push_back(SAS_Utils::Point(50,50));
	points.push_back(SAS_Utils::Point(100,200));
	points.push_back(SAS_Utils::Point(500,400));
	SAS_Utils::GenerateVoronoi(points, vd);
	bool running = true;
	while (running)
	{
		SDL_Rect rect;
		rect.w = width;
		rect.h = height;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		for (int i = 0; i < points.size(); i++) {
			int x = points[i].x();
			int y = points[i].y();
			SDL_RenderDrawPoint(renderer, points[i].x(), points[i].y());

		}

		//SDL_RenderDrawLine(renderer, 0, 0, 100, 100);
		for (SAS_Utils::VoronoiDiagram::const_edge_iterator it = vd.edges().begin();
			it != vd.edges().end(); ++it) {
			if (it->is_primary() && it->is_linear()) {
				auto c1 = it->cell();
				auto idx1 = c1->source_index();
				auto c2 = it->twin()->cell();
				auto idx2 = c2->source_index();
				SAS_Utils::Point o((points[idx1].x() + points[idx2].x() *0.5), (points[idx1].y() + points[idx2].y() *0.5));
				SAS_Utils::Point d((points[idx1].y() - points[idx2].y()), (points[idx1].x() - points[idx2].x()));
				double side = 720;
				double koef = side / (std::max)(fabs(d.x()), fabs(d.y()));
				SAS_Utils::Point p1;
				if (it->vertex0() == NULL) {
					p1.x(o.x() - d.x() * koef);
					p1.y(o.y() - d.y() * koef);
				}
				else {
					p1.x(it->vertex0()->x());
					p1.y(it->vertex0()->y());
				}

				SAS_Utils::Point p2;
				if (it->vertex1() == NULL) {
					p2.x(o.x() + d.x() * koef);
					p2.y(o.y() + d.y() * koef);
				}
				else {
					p2.x(it->vertex1()->x());
					p2.y(it->vertex1()->y());
				}
				SDL_RenderDrawLine(renderer, p1.x(), p1.y(), p2.x(), p2.y());
			}
		}

		SDL_RenderPresent(renderer);

		// Process events
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) == 1)
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
			}


			checkSdlError();
		}
	}

	for (int i = 0; i < textures.size(); ++i)
	{
		SDL_DestroyTexture(textures[i]);
	}
	textures.clear();

	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();

	checkSdlError();

	return 0;
}
#ifdef FOO
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
	auto window = std::make_unique<SAS_GUI::Window>(&renderer, "mainmenu", wv,  true);

	window->AddComponent<SAS_GUI::Button>(bv, SAS_GUI::Dynamics(std::move(updatemods), std::move(inputmods)), 
		[&imp]() {
			imp.dataFunc(); 
		}
	);

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
	auto window2 = std::make_unique<SAS_GUI::Window>(&renderer, "somewindow", wv2,  true);

	// Relative to window position? going with yes for now
	// What makes more sense?
	tv.position = SDL_Rect{ 20, 20, 60, 20 };
	window2->AddComponent<SAS_GUI::TextBox>(tv);

	auto wp = guimanager.AddWindow(std::move(window));
	guimanager.AddWindow(std::move(window2), SDL_SCANCODE_A);

	bv.position = SDL_Rect{300,300,60,20};
	std::function<void()> window_close = [wp]() {wp->CloseWindow(); };
	auto closebutton = std::make_unique<SAS_GUI::Button>(bv, window_close);
	// why models instead of just return string callbacks and void(void) callbacks?

	//closebutton->AddObserver(window_close);
	wp->AddComponent(std::move(closebutton));

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
#endif
