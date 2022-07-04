#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace MSc
{
    enum class Movement 
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class Camera
    {
    public:
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw;
        float pitch;

        float speed;
        float sensitive;
        float zoom;

        // constructor with vectors
        Camera(glm::vec3 iPosition, glm::vec3 iUp, float iYaw, float iPitch);
        // constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float iYaw, float iPitch);

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix();

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(Movement direction, float deltaTime);

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xoffset, float yoffset);


    private:
        float _yaw          = -90.0f;
        float _pitch        =  0.0f;
        float _speed        =  2.5f;
        float _sensitive    =  0.1f;
        float _zoom         =  45.0f;

        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors();

    };
}
