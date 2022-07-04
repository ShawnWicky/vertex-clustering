#include <Render/camera.hpp>
#include <glad/glad.h>

namespace MSc
{
    Camera::Camera(glm::vec3 iPosition, glm::vec3 iUp, float iYaw, float iPitch) : forward(glm::vec3(0.0f, 0.0f, -1.0f)), speed(_speed), sensitive(_sensitive), zoom(_zoom)
    {
        position = iPosition;
        worldUp = iUp;
        yaw = iYaw;
        pitch = iPitch;
        updateCameraVectors();
    }

    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float iYaw, float iPitch) : forward(glm::vec3(0.0f, 0.0f, -1.0f)), speed(_speed), sensitive(_sensitive), zoom(_zoom)
    {
        position = glm::vec3(posX, posY, posZ);
        worldUp = glm::vec3(upX, upY, upZ);
        yaw = iYaw;
        pitch = iPitch;
        updateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix()
    {
        return glm::lookAt(position, position + forward, up);
    }

    void Camera::ProcessKeyboard(MSc::Movement direction, float deltaTime)
    {
        float velocity = speed * deltaTime;
        if (direction == MSc::Movement::FORWARD)
            position += forward * velocity;
        if (direction == MSc::Movement::BACKWARD)
            position -= forward * velocity;
        if (direction == MSc::Movement::LEFT)
            position -= right * velocity;
        if (direction == MSc::Movement::RIGHT)
            position += right * velocity;
    }

    void Camera::ProcessMouseMovement(float xoffset, float yoffset)
    {
        xoffset *= sensitive;
        yoffset *= sensitive;

        yaw   += xoffset;
        pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    void Camera::updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        forward = glm::normalize(forward);
        // also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(forward, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up    = glm::normalize(glm::cross(right, forward));
    }
}
