#pragma once
#include "Shape.h"
#include "iostream"
class Sphere :
    public Shape
{

	void setSphere(const float& radius, const int& segments, const int& rings) {
		for (int i = 0; i <= rings; i++) {
			// we calculate the height and the radius of rings
			float radian = 6.28319/2 * i/rings;//(-90 + (180 / rings)) * 0.0174533;
			float ring_radius = sin(radian) * radius;
			float depth = cos(radian) * radius;
			//std::cout << radian <<"\t" << depth << "\t" << ring_radius << std::endl;

			// we calculate point on the ring
			for (int j = 0; j <= segments; j++) {
				//double rad = 3.14159265 * (360) / 180;
				float x, y, z;
				x = ring_radius * sin(6.28319 / segments * j);
				z = ring_radius * cos(6.28319 / segments * j);
				y = depth;
				vertices.push_back(Vertex(x, depth, z, 1, 1, 1, 1, (float)j / segments, (float)i / rings));
			}
		}

		for (int i = 0; i < rings; i++) {
			for (int j = 0; j < segments; j++) {
				int offsset = i * (segments + 1);

				indices.push_back(offsset+j+0);
				indices.push_back(offsset+j+1);
				indices.push_back(offsset+j+0 + (segments+1));

				indices.push_back(offsset+j+1);
				indices.push_back(offsset+j+0 + (segments+1));
				indices.push_back(offsset+j+1 + (segments+1));
			}
		}
	}

public:
	Sphere() { setSphere(100, 32, 16); }
	Sphere(float radius, float depth, int N) {
		setSphere(radius, 32, 16);
	}
};

