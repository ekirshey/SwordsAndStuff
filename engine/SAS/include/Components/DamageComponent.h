#pragma once

#include "ECSFramework/Component.h"
#include "Config/ComponentDefines.h"
#include "Types/DamageAttributes.h"

struct DamageComponent : public Component {
        static const uint_fast64_t ID = DamageComponentID;

        DamageComponent(DamageAttributes attr, double dmg) : _attribute(attr), _damage(dmg) {}
        DamageComponent(const DamageComponent& c) : _attribute(c._attribute), _damage(c._damage){}

        ~DamageComponent() {}

        uint_fast64_t UniqueBits() const {return ID;}

		DamageAttributes _attribute;
		double _damage;


};
