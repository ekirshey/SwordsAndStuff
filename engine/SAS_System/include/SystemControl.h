#pragma once
#include <memory>
#include <string>
#include "SystemDefines.h"

namespace SAS_System {
	class Renderer;
	class Input;

	DECLSPEC void InitializeSystem();
	DECLSPEC void ShutdownSystem();
	DECLSPEC int CurrentTicks();
	DECLSPEC void UpdateInput(Input* input);
	DECLSPEC void StartTextInput(int streamlength, std::string* stream);
	DECLSPEC void StopTextInput(std::string* stream);

}