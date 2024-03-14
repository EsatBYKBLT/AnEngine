#pragma once
#include "Shape.h"

class Cube :
    public Shape
{
	void setCube(const float& size) {
		vertices = {
			Vertex(-size, -size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
			Vertex( size, -size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
			Vertex( size,  size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
			Vertex(-size,  size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),

			Vertex(-size, -size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
			Vertex( size, -size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
			Vertex( size,  size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
			Vertex(-size,  size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),

			Vertex(-size,  size , size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
			Vertex(-size,  size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
			Vertex(-size, -size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
			Vertex(-size, -size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),

			Vertex( size,  size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
			Vertex( size,  size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
			Vertex( size, -size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
			Vertex( size, -size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),

			Vertex(-size, -size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
			Vertex( size, -size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
			Vertex( size, -size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
			Vertex(-size, -size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),

			Vertex(-size,  size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
			Vertex( size,  size, -size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
			Vertex( size,  size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
			Vertex(-size,  size,  size, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		};
		// calculate indicies 
		for (int i = 0; i < 6; i++) {
			int offsset = i * 4;
			indices.push_back(offsset);
			indices.push_back(offsset + 1);
			indices.push_back(offsset + 2);

			indices.push_back(offsset);
			indices.push_back(offsset + 2);
			indices.push_back(offsset + 3);
		}
	}

public:
    Cube() {
		setCube(100.0f);
    }
	Cube(const float& size) {
		setCube(size);
	}
};

