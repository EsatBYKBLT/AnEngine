#pragma once
#include "Shape.h"

class Cube :
    public Shape
{
	void setCube(const float& size) {
		vertices = {
			Vertex(glm::vec3(-size, -size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 0.0f)),
			Vertex(glm::vec3( size, -size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 0.0f)),
			Vertex(glm::vec3( size,  size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 1.0f)),
			Vertex(glm::vec3(-size,  size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 1.0f)),

			Vertex(glm::vec3(-size, -size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 0.0f)),
			Vertex(glm::vec3( size, -size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 0.0f)),
			Vertex(glm::vec3( size,  size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 1.0f)),
			Vertex(glm::vec3(-size,  size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 1.0f)),

			Vertex(glm::vec3(-size,  size , size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 0.0f)),
			Vertex(glm::vec3(-size,  size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 1.0f)),
			Vertex(glm::vec3(-size, -size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 1.0f)),
			Vertex(glm::vec3(-size, -size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 0.0f)),

			Vertex(glm::vec3( size,  size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 0.0f)),
			Vertex(glm::vec3( size,  size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 1.0f)),
			Vertex(glm::vec3( size, -size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 1.0f)),
			Vertex(glm::vec3( size, -size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 0.0f)),

			Vertex(glm::vec3(-size, -size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 1.0f)),
			Vertex(glm::vec3( size, -size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 1.0f)),
			Vertex(glm::vec3( size, -size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 0.0f)),
			Vertex(glm::vec3(-size, -size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 0.0f)),

			Vertex(glm::vec3(-size,  size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 1.0f)),
			Vertex(glm::vec3( size,  size, -size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 1.0f)),
			Vertex(glm::vec3( size,  size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 1.0f, 0.0f)),
			Vertex(glm::vec3(-size,  size,  size), glm::vec3( 1.0f, 1.0f, 1.0f), glm::vec4(1,1,1,1), glm::vec2( 0.0f, 0.0f)),
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

