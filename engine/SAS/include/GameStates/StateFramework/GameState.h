#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>
#include <iostream>
#include "SystemControl.h"
#include "Renderer.h"
#include "Input.h"

enum States {INITIALIZE, TRANSITIONIN, UPDATE, TRANSITIONOUT, EXIT};

class GameStateImpl {
	public:
		virtual ~GameStateImpl() {}

		// Every state must handle init and update
		virtual int InitializeState(SAS_System::Renderer& renderer, const SAS_System::Input& input) = 0;
		virtual int UpdateState(int elapsedtime, SAS_System::Renderer& renderer, const SAS_System::Input& input) = 0;
		// Not every state has to do these
		virtual int TransitionIntoState(SAS_System::Renderer& renderer) = 0;
		virtual int TransitionFromState(SAS_System::Renderer& renderer) = 0;
		virtual int NextState() = 0;
};

class GameState
{
	public:
		GameState(int stateid, SAS_System::Renderer& renderer, SAS_System::Input& input, bool persistent, std::unique_ptr<GameStateImpl> impl) 
			: _stateid(stateid)
			, _renderer(renderer)
			, _input(input)
			, _persistent(persistent)
			, _impl(std::move(impl))
			, _currentfsmstate(INITIALIZE)
		{

		}

		GameState(const GameState& g) = delete;

		virtual ~GameState() {}

		// Default FSM for a state
		int FiniteStateMachine(int elapsedtime)
		{
			int nextgamestate = _stateid;
			switch(_currentfsmstate)
			{
				case INITIALIZE:
					_currentfsmstate = _impl->InitializeState(_renderer, _input);
					break;
				case TRANSITIONIN:
					_currentfsmstate = _impl->TransitionIntoState(_renderer);
					break;
				case UPDATE:
					_currentfsmstate = _impl->UpdateState(elapsedtime, _renderer, _input);
					break;
				case TRANSITIONOUT:
					_currentfsmstate =_impl->TransitionFromState(_renderer);
					break;
				case EXIT:
					nextgamestate = _impl->NextState();
					if (_persistent)
						_currentfsmstate = TRANSITIONIN;
					else
						_currentfsmstate = INITIALIZE;
				default:
					break;
			}
			return nextgamestate;
		}

		bool IsPersistent() { return _persistent; }

	private:
		int _stateid;

		//System variables. References cause the class can't exist without them
		SAS_System::Renderer& _renderer;
		SAS_System::Input& _input;

		bool _persistent;

		std::unique_ptr<GameStateImpl> _impl;

		int _currentfsmstate;
};


#endif // GAMESTATE_H
