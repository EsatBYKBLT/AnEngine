#pragma once
#include "Shape.h"
//#include <cmath>


class Cylinder : 
	public Shape
{
	void setCylinder(const float& radius, const float& depth, const int& N) {
		for (int i = 0; i <= N; i++){
			//double rad = 3.14159265 * (360) / 180;
			float x, y, z;
			x = radius * sin(6.28319 / N * i);
			z = radius * cos(6.28319 / N * i);
			y = depth / 2;
			vertices.push_back(Vertex(x, y, z, 1, 1, 1, 1, (float)i / N, 1));

			y = -depth / 2;
			vertices.push_back(Vertex(x, y, z, 1, 1, 1, 1, (float)i / N, 0));
		}


		// calculate indicies 
		for (int i = 0; i < N; i++) {
			int offsset = i * 2;
			indices.push_back(offsset);
			indices.push_back(offsset + 1);
			indices.push_back(offsset + 2);

			indices.push_back(offsset + 1);
			indices.push_back(offsset + 2);
			indices.push_back(offsset + 3);
		}

		// top surface
		int j = vertices.size();
		vertices.push_back(Vertex(0, depth / 2, 0, 1, 1, 1, 1, 0.5f, 0.5f));
		for (int i = 0; i <= N; i++) {
			float x, y, z;
			x = radius * sin(6.28319 / N * i);
			z = radius * cos(6.28319 / N * i);
			y = depth / 2;
			vertices.push_back(Vertex(x, y, z, 1, 1, 1, 1, (sin(6.28319 / N * i) + 1) / 2, (cos(6.28319 / N * i) + 1) / 2));
		}

		for (int i = 0, offsset = j + 1; i < N-1; i++) {
			indices.push_back(j);
			indices.push_back(offsset);
			indices.push_back(offsset + 1);
			offsset++;
		}
		// bottom surface
		j = vertices.size();
		vertices.push_back(Vertex(0, -depth / 2, 0, 1, 1, 1, 1, 0.5f, 0.5f));
		for (int i = 0; i <= N; i++) {
			float x, y, z;
			x = radius * sin(6.28319 / N * i);
			z = radius * cos(6.28319 / N * i);
			y = -depth / 2;
			vertices.push_back(Vertex(x, y, z, 1, 1, 1, 1, (sin(6.28319 / N * i) + 1) / 2, (cos(6.28319 / N * i) + 1) / 2));
		}

		for (int i = 0, offsset = j + 1; i < N-1; i++) {
			indices.push_back(j);
			indices.push_back(offsset );
			indices.push_back(offsset + 1);
			offsset++;
		}

		//vertices.push_back(Vertex(0, -depth / 2, 0, 1, 1, 1, 1, 0.5f, 0.5f));

	}

public:
	Cylinder() { setCylinder(100,100,16); }
	Cylinder(float radius,float depth, int N) {
		setCylinder(radius, depth, 16);
	}
};

