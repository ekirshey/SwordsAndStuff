#pragma once
#include <memory>
#include <string>
#include "SystemDefines.h"
#include "Input.h"

namespace SAS_System{
	class Renderer;
}
namespace SAS_System {

	DECLSPEC void InitializeSystem();
	DECLSPEC void ShutdownSystem();
	DECLSPEC int CurrentTicks();
	DECLSPEC void UpdateInput(Input* input);

}