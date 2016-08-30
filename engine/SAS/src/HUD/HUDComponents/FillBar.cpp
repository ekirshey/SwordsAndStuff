#include "FillBar.h"
#include <iostream>

Color red = {0xFF, 0x00, 0x00, 0xFF};
Color green = {0x00, 0xFF, 0x00, 0xFF};
Color yellow = {0xFF, 0xF2, 0x00, 0xFF};

FillBar::FillBar()
{
    currentfillpercent_ = 100;
}

FillBar::FillBar(float* trackedstat, SAS_Rendering::SDLManager* sdlmanager) : trackedstat_(trackedstat), sdlmanager_(sdlmanager)
{
    currentfillpercent_ = *trackedstat_;

    // Set up Rects
    backgroundrect_.x = 10;
    backgroundrect_.y = 500;
    backgroundrect_.w = 210;
    backgroundrect_.h = 35;

    fillablerect_.x = 20;
    fillablerect_.y = 510;
    fillablerect_.w = 200;
    fillablerect_.h = 25;

    barcolor_ = green;
}

FillBar::~FillBar()
{
    //dtor
}

void FillBar::Update()
{
    currentfillpercent_ = (*trackedstat_) * 2;

    if (currentfillpercent_ <= (.75 * 200))
        barcolor_ = yellow;
    if (currentfillpercent_ <= (.25 * 200))
        barcolor_ = red;

    if (currentfillpercent_ > 0)
        fillablerect_.w = currentfillpercent_;
    else
        fillablerect_.w = 1;

}

void FillBar::Render()
{
    //TODO Not rendering on top? why????
    sdlmanager_->RenderFillRectangle(fillablerect_,barcolor_.red,barcolor_.green,barcolor_.blue,barcolor_.alpha);

}
