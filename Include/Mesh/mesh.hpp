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
        Mesh(std::string const &fileName);
        
        unsigned int VAO;
        
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        
        void LoadScene(const aiScene* scene);
        void SetUpMesh();
        void Loadobj(std::string const &fileName);
        void loadMesh(const aiMesh* meshes);
        void Render(Shader &shader);
        
    private:
        unsigned int VBO, EBO;
        
        void BindMesh();
 
    };
}
