#pragma once

#include <glm/glm.hpp>
#include <Render/shader.hpp>

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace MSc
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
    };

    class Mesh
    {
    public:
        //consturctor
        Mesh(std::vector<Vertex> iVertices, std::vector<unsigned int> iIndices);
        ~Mesh();
        
        unsigned int VAO;
        
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        
        void LoadScene();
        void Loadobj(std::string const &fileName);
        Mesh loadMesh(aiMesh *mesh, aiScene *scene);
        void Render(Shader &shader);
        void Clear();
    private:
        unsigned int VBO, EBO;
        
        void BindMesh();
 
    };
}
