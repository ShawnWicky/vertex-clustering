#pragma once

#include <tiny_obj_loader.h>
#include <glm/glm.hpp>

namespace MSc
{
    class Mesh
    {
        struct meshInfo
        {
            std::string meshName;

            std::vector<glm::vec3> vertexPositions;
	        std::vector<glm::vec3> vertexNormals;
	        std::vector<glm::vec2> vertexTextureCoords;
        };
    };
}