#pragma once

//https://www.pbr-book.org/4ed/Geometry_and_Transformations/Vectors#fragment-TupleLengthDefinition-0

class Vec3
{
public:
	float x, y, z;

	Vec3() :x{}, y{}, z{} {}
	Vec3(float x, float y, float z) :x{ x }, y{ y }, z{ z } {}

	float length();
	Vec3 normalize();

	float dot(const Vec3& v);
	Vec3 cross(const Vec3& v);


	friend Vec3 operator+(const Vec3& a, const Vec3& b) {
		return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend Vec3 operator-(const Vec3& a, const Vec3& b) {
		return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	friend Vec3 operator*(const Vec3& vec, const float& s) {
		return Vec3(vec.x * s, vec.y * s, vec.z * s);
	}
	friend Vec3 operator*(const float& s, const Vec3& vec) {
		return Vec3(s*vec.x, s*vec.y, s*vec.z);
	}

	// operator overloads 
	// sum, sub, scalar ops  
	//void CoordinateSystem
};

