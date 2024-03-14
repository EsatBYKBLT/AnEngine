#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex {
	Vertex() {}
	Vertex(const float& x, const float& y, const float& z, const float& r, const float& g, const float& b, const float& a, const float& s, const float& t) {
		Position = glm::vec3(x, y, z);
		Color = glm::vec4(r, g, b, a);
		TexCoords = glm::vec2(s, t);
	}
	glm::vec3 Position{};
	glm::vec4 Color{};
	glm::vec2 TexCoords{};
	//float TexIndex;

	static int getSize() { return sizeof(float) * 9; }
	static std::vector<float> serialize(const std::vector<Vertex>& vec){
		int N = vec.size() * getSize();

		std::vector<float> j;
		j.reserve(N);

		for (Vertex v : vec) {
			j.push_back(v.Position.x);
			j.push_back(v.Position.y);
			j.push_back(v.Position.z);

			j.push_back(v.Color.x);
			j.push_back(v.Color.y);
			j.push_back(v.Color.z);
			j.push_back(v.Color.w);

			j.push_back(v.TexCoords.x);
			j.push_back(v.TexCoords.y);
		}

		return j;
	}
};


class Shape{
protected:
	std::vector<Vertex> vertices{};
	std::vector<unsigned int> indices{};
public:
	std::vector<float> getVertices() { 
		auto a = Vertex::serialize(vertices);

		//std::cout << "Serialize:" << std::endl;
		//for(auto i : a)
		//	std::cout << i << " - ";

		return a;
	}
	std::vector<unsigned int> getIndices() {
		return indices;
	}
};

