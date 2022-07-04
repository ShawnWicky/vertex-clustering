#include <iostream>
#include <queue>

#include <Mesh/mesh.hpp>

#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>
#include <assimp/importer.hpp>

namespace MSc
{
    Mesh::Mesh(std::string const &fileName)
    {
        Loadobj(fileName);
        BindMesh();
    }

    void Mesh::Render(Shader &shader)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Mesh::BindMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        
        //vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        
    }

    void Mesh::Loadobj(std::string const &fileName)
    {
        Assimp::Importer importer;
        
        const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
        
        if(scene)
        {
            LoadScene(scene);
        }
        else
        {
            std::cout << ("Error parsing '%s': '%s'", fileName.c_str(), importer.GetErrorString()) << std::endl;
        }

    }

    void Mesh::LoadScene(const aiScene *scene)
    {
        for(unsigned int i = 0; i < scene->mNumMeshes; i++)
        {
            const aiMesh* meshes = scene->mMeshes[i];
            loadMesh(meshes);
        }
    }

    void Mesh::loadMesh(const aiMesh* meshes)
    {
        for(unsigned int i = 0; i < meshes->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;
            // positions
            vector.x = meshes->mVertices[i].x;
            vector.y = meshes->mVertices[i].y;
            vector.z = meshes->mVertices[i].z;
            vertex.position = vector;
            // normals
            if (meshes->HasNormals())
            {
                vector.x = meshes->mNormals[i].x;
                vector.y = meshes->mNormals[i].y;
                vector.z = meshes->mNormals[i].z;
                vertex.normal = vector;
            }
            vertices.emplace_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < meshes->mNumFaces; i++)
        {
            const aiFace& face = meshes->mFaces[i];
            //check if the obj file is triangle files
            assert(face.mNumIndices == 3);
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.emplace_back(face.mIndices[j]);
        }
        
        for(unsigned int i = 0; i < vertices.size(); i++)
        {
            std::cout << "v: " << glm::to_string(vertices[i].position) << std::endl;
        }
        
        for(unsigned int i = 0; i < vertices.size(); i++)
        {
            std::cout << "vn: " << glm::to_string(vertices[i].normal) << std::endl;
        }
    }
    
}
