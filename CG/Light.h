#pragma once
#include "Vec3.h"

class Light
{
public:
	Light() :position{ 0,0,0 }, density{ 255 } {}
	Vec3 position; 
	float density;

};