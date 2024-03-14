#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//class Vec3 {
//	float x, y, z;
//	Vec3() :x{}, y{}, z{} {}
//	Vec3(float x, float y, float z) :x{ x }, y{ y }, z{ z } {}
//};
//
//class Vec2 {
//	float x, y;
//	Vec2() :x{}, y{} {}
//	Vec2(float x, float y, float z) :x{ x }, y{ y } {}
//};

class Vertex{
	glm::vec3 location;
	//float r, g, b, a;
	float s, t;
	
};

