#ifndef HUDCOMPONENT_H
#define HUDCOMPONENT_H

// Basic Interface for a HUD Component. I figured there arent many hud objects so we can minimalize the usage
// of an entire ECS system. It just seems like a fair amount of work/overhead for small gain. We will evaluate it
// in time. If the HUD starts overflowing with objects or something.

class HUDComponent
{
    public:
        virtual ~HUDComponent() {}
        virtual void Update() = 0; // Maybe...
        virtual void Render() = 0;
};

#endif // HUDCOMPONENT_H
