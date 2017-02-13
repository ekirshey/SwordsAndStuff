#pragma once

#include "Components/PositionComponent.h"
#include "Components/VelocityComponent.h"
#include "Components/BoundingRectangleComponent.h"

// Items being stored inside of the quad
struct QuadElement
{
	uint_fast64_t entityid;
	VelocityComponent* velocitycomponent;
	PositionComponent* positioncomponent;
	BoundingRectangleComponent* boundingrectangle;

	bool operator==(const QuadElement& rhs) const
	{
		if (entityid != rhs.entityid)
			return false;
		return true;
	}

	bool operator<(const QuadElement& p) const {
		return entityid < p.entityid;
	}
	bool operator!=(const QuadElement& p) const { return !(*this == p); }
	bool operator> (const QuadElement& p) const { return p < *this; }
	bool operator>=(const QuadElement& p) const { return !(*this < p); }
	bool operator<=(const QuadElement& p) const { return !(p < *this); }
};

class QuadElements {
	
	public:
		QuadElements(int size) 
			: _size(0)
			, _elements(size)
		{

		}

		void insert(const QuadElement& ele) {
			if (_size < _elements.size())
				_elements[_size++] = ele;
			else
				std::cout << "how? " << std::endl;
		}

		void clear() {
			_size = 0;
		}

		void copyelements(std::vector<QuadElement>& elements) const{
			for (int i = 0; i < _size; i++) {
				elements.push_back(_elements[i]);
			}
		}

		std::vector<QuadElement>::const_iterator begin() const {
			return _elements.begin();
		}

		std::vector<QuadElement>::const_iterator end() const {
			if (_size > 0)
				return _elements.begin() + (_size - 1);
			else
				return _elements.begin();
		}
	private:
		int _size;
		std::vector<QuadElement> _elements;
};