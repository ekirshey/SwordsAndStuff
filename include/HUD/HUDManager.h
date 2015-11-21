#ifndef HUDMANAGER_H
#define HUDMANAGER_H

#include <vector>
#include <memory>
#include "HUDComponents/HUDComponent.h"
#include "../ECSFramework/ObjectManager.h"

class Component;
class SDLManager;

class HUDManager
{
    public:
        HUDManager();
		HUDManager(ObjectManager* objectmanager, SDLManager* sdlmanager);
        virtual ~HUDManager();
        void Update();
       
        void AddComponent(std::unique_ptr<HUDComponent> hudcomponent) { hudcomponents.push_back(std::move(hudcomponent)); }

        void SetObjectManager(ObjectManager* objectmanager) {objectmanager_ = objectmanager;}
    private:
		void Initialize();

        std::vector<std::unique_ptr<HUDComponent>> hudcomponents;
        SDLManager* sdlmanager_;
        ObjectManager* objectmanager_;
};

#endif // HUDMANAGER_H
