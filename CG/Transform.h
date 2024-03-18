#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Transform
{
	bool isChanged = false; 

	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 transform; // model matrix 

	void calculateTransform() {
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, location);
		transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		transform = glm::scale(transform, scale);
	}

public:
	Transform() {
		location = glm::vec3(0, 0, 0);
		rotation = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);

		calculateTransform();
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
	void setRotation(float x, float y, float z) {
		setRotation(glm::vec3(x, y, z));
	}
	void setScale(glm::vec3 scale) {
		this->scale = scale;
		calculateTransform();
	}
	void setScale(float x, float y, float z) {
		setScale(glm::vec3(x, y, z));
	}

	// return model matrix 
	glm::mat4 getTransform() {
		return transform;
	}



};

