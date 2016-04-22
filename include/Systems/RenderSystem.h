#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ProcessingSystem.h"
#include "../SDL/SDLManager.h"

class SDLManager;
class GameWorld;
class Camera;

class RenderSystem : public ProcessingSystem
{
    public:
        static const uint_fast64_t COMPONENTIDS = 0x5;      // This means the System operates on all Entities with a "1" Component. In this example thats position
                                                            // Unlike the component ID this can be duplicated
        RenderSystem(SDLManager* sdlmanager);
        RenderSystem(SDLManager* sdlmanager, GameWorld* gameworld, Camera* camera);
        ~RenderSystem();

        uint_fast64_t ComponentBits() {return RenderSystem::COMPONENTIDS;}    // TODO: Is this necessary or is just accessing the variable directly better?

        void ProcessEntity(uint_fast64_t entity);
        void SetSDLManager(SDLManager* sdlmanager) {sdlmanager_ = sdlmanager;}

        void BeforeObjectProcessing();
        void AfterObjectProcessing();
    private:
        SDLManager* sdlmanager_;
        GameWorld* gameworld_;
        Camera* camera_;
};

#endif // RENDERSYSTEM_H
