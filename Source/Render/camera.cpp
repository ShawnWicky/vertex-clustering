#include <Render/camera.hpp>
#include <glad/glad.h>

namespace MSc
{
Camera::Camera(glm::vec3 iPosition, glm::vec3 iTarget, glm::vec3 iWorldUp)
    {
        position = iPosition;
        worldUp = iWorldUp;

    }

    Camera::Camera(glm::vec3 iPosition, float iPitch, float iYaw, glm::vec3 iWorldUp)
    {
        position = iPosition;
        worldUp = iWorldUp;
        pitch = iPitch;
        yaw = iYaw;
        forward.x = glm::cos(pitch) * glm::sin(yaw);
        forward.y = glm::sin(pitch);
        forward.z = glm::cos(pitch) * glm::cos(yaw);
        right = glm::normalize(glm::cross(forward, worldUp));
        up = glm::normalize(glm::cross(right, forward));
    }

    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(position, position + forward, worldUp);
    }

    void Camera::updateCameraAngle()
    {
        // calculate the new Front vector
        forward.x = glm::cos(pitch) * glm::sin(yaw);
        forward.y = glm::sin(pitch);
        forward.z = glm::cos(pitch) * glm::cos(yaw);
        right = glm::normalize(glm::cross(forward, worldUp));
        up = glm::normalize(glm::cross(right, forward));
    }

    void Camera::updateCameraPosition(float deltaTime)
    {
        position += (forward * speedZ * speedScalar + right * speedX * speedScalar + up * speedY * speedScalar) * deltaTime;
    }

    void Camera::processMouseMovement(float xoffset, float yoffset, float deltaTime)
    {
        yaw -= xoffset * deltaTime;
        pitch -= yoffset * deltaTime;

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraAngle();
    }
}
