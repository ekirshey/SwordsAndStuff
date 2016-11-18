#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include <memory>

#include "GameState.h"
#include "SystemControl.h"
#include "Renderer.h"

//class SDLManager;
// NOTE For now im using SDLManager as a non-dynamic object since it doesnt seem to have to be one
class Game
{
    public:
        Game(int x, int y);
        virtual ~Game();

		template<typename T, typename... Args>
		void AddState(bool persistence, int index,  Args&&... args) {
			auto stateimpl = std::make_unique<T>(std::forward<Args>(args)...);
			auto state = std::make_unique<GameState>(index, _renderer, _input, persistence, std::move(stateimpl));
			_gamestates[index] = std::move(state);
		}

        void Run();
    private:
        void Update(int elapsedtime);

        void RemoveStateAtIndex(int idx);

        std::vector<std::unique_ptr<GameState>> _gamestates;
        unsigned int _activestate;
        bool _gamerunning;

		SAS_System::Renderer _renderer;
		SAS_System::Input _input;

};

#endif // GAMESTATEMANAGER_H
