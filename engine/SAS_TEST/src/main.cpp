#include <iostream>
#include <memory>
#include "SystemControl.h"
#include "Renderer.h"

struct A {
};

struct B : public A {
	B() : x(8) {}
	int x;
};


int main(int argc, char* argv[])
{
	std::vector<A*> v;
	{
		B b;
		v.push_back(&b);
		B* vb = static_cast<B*>(v[0]);
		std::cout << vb->x << std::endl;
	}
		B* vb = static_cast<B*>(v[0]);
		std::cout << vb->x << std::endl;
	SAS_System::InitializeSystem();
	SAS_System::Renderer renderer(600, 600);
	SAS_System::Input input;


	bool quit = false;
	std::string stream = "";
	int mousex, mousey;
	while (!quit) {
		renderer.ClearScreen();
		SAS_System::UpdateInput(&input);
		quit = input.Quit();
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

		renderer.RenderText(std::to_string(mousex), 100, 200, 12, SDL_Color{ 255,0,0 }, "E:\\GitHub\\SwordsAndStuff\\media\\font.ttf");
		renderer.RenderText(std::to_string(mousey), 100, 250, 12, SDL_Color{ 255,0,0 }, "E:\\GitHub\\SwordsAndStuff\\media\\font.ttf");

		renderer.RenderText(stream, 300, 200, 12, SDL_Color{ 255,0,0 }, "E:\\GitHub\\SwordsAndStuff\\media\\font.ttf");
		renderer.RenderFillRectangle(SDL_Rect{ 50, 50, 50, 50 }, SDL_Color{ 255, 0, 0, 255 });
		renderer.RenderText("FooBar", 100, 100, 12, SDL_Color{ 255,0,0,255 },"E:\\GitHub\\SwordsAndStuff\\media\\font.ttf");
		SDL_Rect r = { 0,0,50,50 };
		renderer.RenderImage("E:\\GitHub\\SwordsAndStuff\\media\\sprites\\Pawns.png", 300, 300, &r);
		renderer.Update();

	}

//	SAS_GUI::GUIManager guimanager(&sdlmanager);
	//SAS_GUI::GUIManager guimanager();
#ifdef FOO	
	auto window = std::make_unique<SAS_GUI::GUIWindow>(&sdlmanager, "mainmenu", SDL_Rect{ 0, 0, 1280, 640 }, "../../media//backgrounds/mainmenubg.bmp", "../../media/backgrounds/mainmenubg.bmp", true);
	guimanager.AddWindow(std::move(window));

	int currenttime = 0;
	int previoustime = 0;
	int framecounter = 0;
	bool gamerunning_ = true;
	// If everything initialized ok then enter main game loop
	if (sdlmanager.Initialize())
	{
		sdlmanager.Start();

		std::cout << "Finished GameStateManager Init" << std::endl;
		std::cout << "Entering Main Loop" << std::endl << std::endl;

		currenttime = SDL_GetTicks();
		// Main Game Loop
		while (gamerunning_)
		{
			previoustime = currenttime;
			currenttime = SDL_GetTicks();

			// Clear the Screen
			sdlmanager.ClearScreen();

			// Read the event queue so the state has the input
			if (sdlmanager.ReadEventQueue())
				gamerunning_ = false;   // Quit event was received
			else
			{
				guimanager.Update(currenttime - previoustime);
				sdlmanager.Render();
			}

			framecounter++;
			/*
			// REplaced with VSYNC
			int frameTicks = SDL_GetTicks() - currenttime;

			if( frameTicks < SCREEN_TICK_PER_FRAME )
			{
			//Wait remaining time
			SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
			}
			*/
		}   // End Main Loop

		sdlmanager.Close();
	}
#endif
	return 0;
}
