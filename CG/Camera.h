#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>

class Camera{
    // euler Angles
    float yaw;
    float pitch;


    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 WorldUp;


    glm::mat4 proj;
    glm::vec3 location; 

    void updateCameraVectors()
    {
        // calculate the new Front vector
        forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward.y = sin(glm::radians(pitch));
        forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward = glm::normalize(forward);
        // also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(forward, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up = glm::normalize(glm::cross(right, forward));
    }
public:

	Camera() {}
    Camera(float screenWidth, float screenHeight, float fov = 100.0f, float near = 0.1f, float far = 10'000.0f)
    {
        SetProjection(screenWidth, screenWidth, fov, near, far);
        location = glm::vec3(0.0f);

        WorldUp = glm::vec3(0, 1, 0);
        yaw = -90;
        pitch = 0;
        updateCameraVectors();
    }

    void Move(glm::vec3 deltaLocation) {
        location += deltaLocation.x * right;
        location += deltaLocation.y * up;
        location += deltaLocation.z * -forward;
    }
    void Rotate(glm::vec3 deltaRotation) {
        yaw += -deltaRotation.y;
        pitch += deltaRotation.x;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        
        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    void SetProjection(float screenWidth, float screenHeight, float fov,  float near = 0.1f, float far = 10'000.0f) {
        proj = glm::perspective(glm::degrees(10.0f), screenWidth / screenHeight, near, far);

    }

    glm::mat4 GetCameraMatrix() {        
        return proj * glm::lookAt(location, location + forward*100.0f, glm::vec3(0, 1, 0));
    }

};

