#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <string>
#include <vector>
#include "../ECSFramework/ECSManager.h"

class SDLManager;
class GameWorld;
class Camera;

class ObjectManager
{
    public:
        ObjectManager();
		ObjectManager(SDLManager* sdlmanager, GameWorld* gameworld, Camera* camera);
        virtual ~ObjectManager();

        void Update(int elapsedtime);
        
        Component* GetPlayerComponent(uint_fast64_t componentid);
        std::vector<Component*> GetAllPlayerComponents();

        ECSManager* GetECSManager() {return &ecsmanager_;}
    private:
		void Initialize(SDLManager* sdlmanager, GameWorld* gameworld, Camera* camera);

        ECSManager ecsmanager_;
};

#endif // OBJECTMANAGER_H
