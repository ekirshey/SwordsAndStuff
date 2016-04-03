#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include <memory>

#include "GameState.h"
#include "../../SDL/SDLManager.h"

//class SDLManager;
// NOTE For now im using SDLManager as a non-dynamic object since it doesnt seem to have to be one
class GameStateManager
{
    public:
        GameStateManager();
        virtual ~GameStateManager();

		void AddState(std::unique_ptr<GameState> state);

        void Run();
    private:
        void Update(int elapsedtime);
        bool Initialize();

        void RemoveStateAtIndex(int idx);
        void RemoveLastState() { 
			if (gamestates_.size() > 0) {
				activestate_--;
				gamestates_.pop_back();
			}
		}


        std::vector<std::unique_ptr<GameState>> gamestates_;
        unsigned int activestate_;
        bool gamerunning_;

        SDLManager sdlmanager_;

};

#endif // GAMESTATEMANAGER_H
