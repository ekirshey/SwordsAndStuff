#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "../../include/ECSFramework/Component.h"
#include "../Config/ComponentDefines.h"

class InputComponent : public Component
{
    public:
        static const uint_fast64_t ID = InputComponentID;

        InputComponent() {}
        InputComponent(const PositionComponent& c) {}

        virtual ~InputComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

    private:

};

#endif // INPUTCOMPONENT_H
