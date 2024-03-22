#pragma once
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Vertex {

	glm::vec3 position{};
	glm::vec3 normal{};
	glm::vec4 color{};
	glm::vec2 tex_coords{};
	//float TexIndex;


	Vertex() {}
	Vertex(const float& x, const float& y, const float& z, const float& r, const float& g, const float& b, const float& a, const float& s, const float& t) {
		position = glm::vec3(x, y, z);
		color = glm::vec4(r, g, b, a);
		tex_coords = glm::vec2(s, t);
	}
	Vertex(
		glm::vec3 position = glm::vec3(0, 0, 0),
		glm::vec3 normal = glm::vec3(0, 0, 0),
		glm::vec4 color = glm::vec4(1, 1, 1, 1),
		glm::vec2 tex_coords = glm::vec2(0, 0)
	) : position{ position },normal{normal},color{color},tex_coords{tex_coords}
	{}


	static int getSize() { return sizeof(float) * 9; }
	static std::vector<float> serialize(const std::vector<Vertex>& vec){
		int N = vec.size() * getSize();

		std::vector<float> j;
		j.reserve(N);

		for (Vertex v : vec) {
			j.push_back(v.position.x);
			j.push_back(v.position.y);
			j.push_back(v.position.z);

			j.push_back(v.normal.x);
			j.push_back(v.normal.y);
			j.push_back(v.normal.z);

			j.push_back(v.color.x);
			j.push_back(v.color.y);
			j.push_back(v.color.z);
			j.push_back(v.color.w);

			j.push_back(v.tex_coords.x);
			j.push_back(v.tex_coords.y);
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

