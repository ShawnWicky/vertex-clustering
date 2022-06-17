#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <Render/shader.hpp>

namespace MSc
{
    class Scene
    {
    private:
        bool _setupOpenGL = false;

        unsigned int VBO, VAO;
         ;
        Shader _shader;
    public:
        Scene(Shader shader);
        
        void ShowGuiWindow(bool* outIsOpen);

        void SetupOpenGL();
    };
}