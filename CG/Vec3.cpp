#include "Vec3.h"
#include <cmath>

float Vec3::length() {
	return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize(){
	float l = length();
	return Vec3(x / l, y / l, z / l);
}


float Vec3::dot(const Vec3& v) {
	return (x * v.x) + (y * v.y) + (z * v.z);
}

Vec3 Vec3::cross(const Vec3& v)
{
	Vec3 vec;
	vec.x = y * v.z - z * v.y;
	vec.y = z * v.x - x * v.z;
	vec.z = x * v.y - y * v.x;
	return vec;
}
