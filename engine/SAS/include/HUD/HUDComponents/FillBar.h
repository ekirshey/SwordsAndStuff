#ifndef FILLBAR_H
#define FILLBAR_H

#include "HUDComponent.h"
#include "SDLManager.h"

struct Color
{
    int red;
    int green;
    int blue;
    int alpha;
};

class FillBar : public HUDComponent
{
    public:
        FillBar();
        FillBar(float* trackedstat,SAS_Rendering::SDLManager* sdlmanager);
        virtual ~FillBar();
        void Update();
        void Render();
    private:
        float* trackedstat_;
        int currentfillpercent_;
        SDL_Rect backgroundrect_;
        SDL_Rect fillablerect_;
        SAS_Rendering::SDLManager* sdlmanager_;
        Color barcolor_;

};

#endif // FILLBAR_H
