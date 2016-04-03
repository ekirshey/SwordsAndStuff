#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>

enum States {INITIALIZE, TRANSITIONIN, UPDATE, TRANSITIONOUT, EXIT};

class SDLManager;

class GameState
{
    public:
		GameState(bool persistent) : persistent_(persistent), nextstate_(nullptr) {}
        virtual ~GameState() {}

        // Default FSM for a state
        virtual void FiniteStateMachine(int elapsedtime)
        {
            switch(currentstate_)
            {
                case INITIALIZE:
                    InitializeState();
                    break;
                case TRANSITIONIN:
                    TransitionIntoState();
                    break;
                case UPDATE:
                    UpdateState(elapsedtime);
                    break;
                case TRANSITIONOUT:
                    TransitionFromState();
                    break;
                case EXIT:
                default:
                    break;
            }
        }

        void SetCurrentState(int state) {currentstate_ = state;}
        int GetCurrentState() {return currentstate_;}

		SDLManager* sdlmanager_;
		std::unique_ptr<GameState> nextstate_;
		bool persistent_;


    private:
        // Every state must handle init, update and exit
        virtual void InitializeState() = 0;
        virtual void UpdateState(int elapsedtime) = 0;
        // Not every state has to do these
        virtual void TransitionIntoState() = 0;
        virtual void TransitionFromState() = 0;

        
        int currentstate_;
};

#endif // GAMESTATE_H
