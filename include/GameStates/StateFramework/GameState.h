#ifndef GAMESTATE_H
#define GAMESTATE_H

enum States {INITIALIZE, TRANSITIONIN, UPDATE, TRANSITIONOUT, EXIT};

class SDLManager;

class GameState
{
    public:

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

        void SetSDLManager(SDLManager& sdlmanager) {sdlmanager_ = &sdlmanager;}
        SDLManager* GetSDLManager() {return sdlmanager_;}

        void SetCurrentState(int state) {currentstate_ = state;}
        int GetCurrentState() {return currentstate_;}

    private:
        // Every state must handle init, update and exit
        virtual void InitializeState() = 0;
        virtual void UpdateState(int elapsedtime) = 0;
        // Not every state has to do these
        virtual void TransitionIntoState() = 0;
        virtual void TransitionFromState() = 0;

        SDLManager* sdlmanager_;
        int currentstate_;
};

#endif // GAMESTATE_H
