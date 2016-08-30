#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>
#include <iostream>

enum States {INITIALIZE, TRANSITIONIN, UPDATE, TRANSITIONOUT, EXIT};

namespace SAS_Rendering{
	class SDLManager;
}

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

		void AssignSDLManager(SAS_Rendering::SDLManager* sdlmanager) {
			if (sdlmanager != nullptr)
				sdlmanager_ = sdlmanager;
			else
				std::cout << "Bad SDLManager" << std::endl;
		}

		bool HasNextState() {
			return nextstate_ != nullptr;
		}
		
		void AddNextState(std::unique_ptr<GameState> nextstate) { nextstate_ = std::move(nextstate); }

		bool IsPersistent() { return persistent_; }

		// Source
		std::unique_ptr<GameState> PopNextState() { return std::move(nextstate_); }

		SAS_Rendering::SDLManager* GetSDLManager() { return sdlmanager_; }

	private:
		SAS_Rendering::SDLManager* sdlmanager_;
		std::unique_ptr<GameState> nextstate_;
		bool persistent_;

		// Every state must handle init, update and exit
		virtual void InitializeState() = 0;
		virtual void UpdateState(int elapsedtime) = 0;
		// Not every state has to do these
		virtual void TransitionIntoState() = 0;
		virtual void TransitionFromState() = 0;

		
		int currentstate_;
};

#endif // GAMESTATE_H
