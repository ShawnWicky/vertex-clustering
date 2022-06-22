#include <Render/scene.hpp>


#include <imgui.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices[] = {
        // positions                        // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
};

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

namespace MSc
{
    Scene::Scene(Shader shader): _shader(shader)
    {
        
    }
    
    void Scene::ShowGuiWindow(bool* outIsOpen)
    {
        if(ImGui::Begin("Scene", outIsOpen))
        {
             if(!_setupOpenGL)
             {
                 SetupOpenGL();
                 _setupOpenGL = true;
             }
             // render
             // ------
             glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
             glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

             // activate shader
             _shader.use();

             // camera/view transformation
             glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
             float radius = 10.0f;
             float camX = static_cast<float>(sin(glfwGetTime()) * radius);
             float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
             view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
             _shader.setMat4("view", view);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            
        }  
        ImGui::End(); 
    }

    void Scene::SetupOpenGL()
    {
        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
        // -----------------------------------------------------------------------------------------------------------
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        _shader.setMat4("projection", projection); 
    }
}