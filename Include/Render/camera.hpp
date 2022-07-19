#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace MSc
{
    class Camera
    {
    public:
        //Ruglar
        Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);

        Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);

        glm::vec3 position; //camera pos
        glm::vec3 forward; //camera forward direction
        glm::vec3 right; // camera right
        glm::vec3 up; // camera up
        glm::vec3 worldUp; //world up

        float yaw;
        float pitch;
        float speedX;
        float speedY;
        float speedZ;
        float speedScalar = 0.5f;

        glm::mat4 getViewMatrix();

        void updateCameraPosition(float deltaTime);

        void updateCameraAngle();

        void processMouseMovement(float deltaX, float deltaY, float deltaTime);
};
}
