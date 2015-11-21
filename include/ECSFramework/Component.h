#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstdint>

class Component
{
    public:
        virtual ~Component() {}
        virtual uint_fast64_t UniqueBits() const = 0;
};

#endif // COMPONENT_H
