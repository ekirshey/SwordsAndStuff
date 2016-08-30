#ifndef HUDMANAGER_H
#define HUDMANAGER_H

#include <vector>
#include <memory>
#include "HUDComponents/HUDComponent.h"

class Component;
namespace SAS_Rendering {
	class SDLManager;
}

class HUDManager
{
    public:
        HUDManager();
		HUDManager( SAS_Rendering::SDLManager* sdlmanager);
        virtual ~HUDManager();
        void Update();
       
        void AddComponent(std::unique_ptr<HUDComponent> hudcomponent) { hudcomponents.push_back(std::move(hudcomponent)); }

    private:
		void Initialize();

        std::vector<std::unique_ptr<HUDComponent>> hudcomponents;
        SAS_Rendering::SDLManager* sdlmanager_;
};

#endif // HUDMANAGER_H
