#pragma once
#include <vector>
#include <iostream>

#include "Shape.h"
#include "Transform.h"


class Actor {
public: // everything is public - for now - 
	Shape shape;

	Transform transform;

	Actor() {}
	Actor(Shape shape) : Actor() {
		this->shape = shape;
	}


	std::vector<float> getPoints() { 
		return shape.getVertices(); 
	}
	std::vector<unsigned int> getIndicies() {
		return shape.getIndices();
	}
};

