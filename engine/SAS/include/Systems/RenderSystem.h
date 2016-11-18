#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "ProcessingSystem.h"
#include "Renderer.h"

class GameWorld;
class Camera;

class RenderSystem : public ProcessingSystem
{
    public:
        static const uint_fast64_t COMPONENTIDS = 0x5;      // This means the System operates on all Entities with a "1" Component. In this example thats position
                                                            // Unlike the component ID this can be duplicated
        RenderSystem(std::string systemname, ECSManager* ecsmanager, SAS_System::Renderer* renderer);
        RenderSystem(std::string systemname, ECSManager* ecsmanager, SAS_System::Renderer* renderer, GameWorld* gameworld, Camera* camera);
        ~RenderSystem();

        uint_fast64_t ComponentBits() {return RenderSystem::COMPONENTIDS;}    // TODO: Is this necessary or is just accessing the variable directly better?

        void ProcessEntity(uint_fast64_t entity);
        void SetSDLManager(SAS_System::Renderer* renderer) {_renderer = renderer;}

        void BeforeObjectProcessing();
        void AfterObjectProcessing();
    private:
		SAS_System::Renderer* _renderer;
        GameWorld* _gameworld;
        Camera* _camera;
};

#endif // RENDERSYSTEM_H
