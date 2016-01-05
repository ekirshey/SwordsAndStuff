#ifndef HUDMANAGER_H
#define HUDMANAGER_H

#include <vector>
#include <memory>
#include "HUDComponents/HUDComponent.h"

class Component;
class SDLManager;

class HUDManager
{
    public:
        HUDManager();
		HUDManager( SDLManager* sdlmanager);
        virtual ~HUDManager();
        void Update();
       
        void AddComponent(std::unique_ptr<HUDComponent> hudcomponent) { hudcomponents.push_back(std::move(hudcomponent)); }

    private:
		void Initialize();

        std::vector<std::unique_ptr<HUDComponent>> hudcomponents;
        SDLManager* sdlmanager_;
};

#endif // HUDMANAGER_H
