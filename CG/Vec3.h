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


	// operator overloads 
	// sum, sub, scalar ops  
	//void CoordinateSystem
};

