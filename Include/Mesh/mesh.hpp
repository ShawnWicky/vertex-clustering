#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

namespace MSc
{
    class Mesh
    {
        struct MeshInfo
        {
            std::string meshName;
            
            std::size_t vertexStartIndex;
	        std::size_t numberOfVertices;
        };


        struct Model
        {
            Model() noexcept;

	        Model( Model const& ) = delete;
	        Model& operator= (Model const&) = delete;

	        Model( Model&& ) noexcept;
	        Model& operator= (Model&&) noexcept;


	        std::string modelName;
	        std::string modelSourcePath;

	        std::vector<MeshInfo> meshes;

	        std::vector<glm::vec3> vertexPositions;
	        std::vector<glm::vec3> vertexNormals;
	        std::vector<glm::vec2> vertexTextureCoords;
        };

        Model loadobj(std::string fileName);
    };
}