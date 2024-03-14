#pragma once
#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shape.h"
#include "Cube.h"
#include "Cylinder.h"


class Actor {
public: // everything is public - for now - 
	Shape shape;

	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 transform; // model matrix 

	Actor() {
		location = glm::vec3(0, 0, 0);
		rotation = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);

		calculateTransform();
	}
	Actor(Shape shape) : Actor() {
		this->shape = shape;
	}

	void setLocation(glm::vec3 location) {
		this->location = location;
		calculateTransform();
	}
	void setLocation(float x, float y, float z) {
		setLocation(glm::vec3(x, y, z));
	}
	void setRotation(glm::vec3 rotation) {
		this->rotation = rotation;
		calculateTransform();
	}
	void setRotation(float x, float y, float z){
		setRotation(glm::vec3(x, y, z));
	}
	void setScale(glm::vec3 scale) {
		this->scale = scale;
		calculateTransform();
	}
	void setScale(float x, float y, float z) {
		setScale(glm::vec3(x, y, z));
	}

	glm::mat4 modelMatrix() {		
		return transform;
	}

	void calculateTransform() {
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, location);
		transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		transform = glm::scale(transform, scale);
	}

	std::vector<float> getPoints() { 
		return shape.getVertices(); 
	}
	std::vector<unsigned int> getIndicies() {
		return shape.getIndices();
	}
};

