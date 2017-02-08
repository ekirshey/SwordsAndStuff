#include "Input.h"

namespace SAS_System {
	Input::Input() 
		: _quit(false)
		, _activestringlength(0)
		, _activestream(-1)
	{
		_toupdate = std::make_unique<std::vector<Input::KeyState*>>();
		for (int i = 0; i < MAXKEYS; i++) {
			_activekeys[i] = KeyState::STILL;
		}
	}

	Input::~Input() {
	}

	bool Input::isKeyPressed(int key) const {
		return _activekeys[key] == KeyState::PRESSED;
	}

	bool Input::isKeyReleased(int key) const {
		return _activekeys[key] == KeyState::RELEASED;
	}

	bool Input::leftMousePressed() const {
		return _activekeys[MouseButtons::LEFT] == KeyState::PRESSED;
	}

	bool Input::leftMouseReleased() const {
		return _activekeys[MouseButtons::LEFT] == KeyState::RELEASED;
	}

	bool Input::Quit() {
		return _quit;
	}


	void Input::getMouseState(int& x, int& y) const{
		x = _mousex;
		y = _mousey;
	}

	void Input::setMouseState(int&x, int& y) {
		_mousex = x;
		_mousey = y;
	}

	void Input::updateTextInput(const char* text) {
		if (_activestream >= 0) {
			if (_recordstreams[_activestream].AtMaxLength()) {
				_recordstreams[_activestream].stream->append(text);
			}
		}
	}

	void Input::handleBackspace() {
		if (_activestream >= 0) {
			if (_recordstreams[_activestream].stream->size() > 0) {
				_recordstreams[_activestream].stream->pop_back();
			}
		}
	}

	void Input::startRecordingTextInput(int maxcharacters, std::string* stream) {
		_activestringlength = 0;

		bool existingstream = false;
		for (size_t i = 0; i < _recordstreams.size(); i++) {
			if (_recordstreams[i].stream == stream) {
				existingstream = true;
				_activestream = i;
			}
		}

		if (!existingstream) {
			_recordstreams.push_back(RecordStream(stream, maxcharacters));
			_activestream = _recordstreams.size() - 1;
		}
	}
	
	void Input::stopRecordingTextInput(std::string* stream) {
		for (size_t i = 0; i < _recordstreams.size(); i++) {
			if (_recordstreams[i].stream == stream) {
				_recordstreams.erase(_recordstreams.begin() + i);
				_activestream = -1;
			}
		}
	}

	void Input::updateKeyState(int key, KeyState state) {
		_activekeys[key] = state;
		_toupdate->push_back(&_activekeys[key]);
	}

	void Input::updateMouseState(uint8_t button, KeyState state) {
		switch (button) {
			case SDL_BUTTON_LEFT:
				updateKeyState(Input::MouseButtons::LEFT, state);
				break;
			case SDL_BUTTON_RIGHT:
				updateKeyState(Input::MouseButtons::RIGHT, state);
				break;
		}
	}

	void Input::clear() {
		for (uint32_t i = 0; i < _toupdate->size(); i++) {
			*_toupdate->at(i) = KeyState::STILL;
			_toupdate->pop_back();
		}
	}

	void Input::setQuitState(bool quit) {
		_quit = quit;
	}


}