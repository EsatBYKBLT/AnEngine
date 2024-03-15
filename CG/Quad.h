#pragma once
#include "Shape.h"
class Quad :
    public Shape
{
	void setQuad(const float& size) {
		vertices = {
			Vertex(-size, -size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
			Vertex(size, -size, -size, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
			Vertex(size,  size, -size, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f),
			Vertex(-size,  size, -size, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f),

		};

		indices.push_back(0);
		indices.push_back(0 + 1);
		indices.push_back(0 + 2);
						 
		indices.push_back(0);
		indices.push_back(0 + 2);
		indices.push_back(0 + 3);
		
	}

public:
	Quad() {
		setQuad(100.0f);
	}
	Quad(const float& size) {
		setQuad(size);
	}
};

