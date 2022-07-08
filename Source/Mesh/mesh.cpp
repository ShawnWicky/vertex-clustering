#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include <Mesh/mesh.hpp>

#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>
#include <assimp/importer.hpp>

namespace MSc
{
/*
    Mesh::Mesh(std::string const &fileName)
    {
        Loadobj(fileName);
        BindMesh();
    }

    void Mesh::Render(Shader &shader)
    {
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
        // now loop through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for(unsigned int i = 0; i < meshes->mNumFaces; i++)
        {
            const aiFace& face = meshes->mFaces[i];
            //check if the obj file is triangle files
            assert(face.mNumIndices == 3);
            // retrieve all indices of the face and store them in the indices vector
            for(unsigned int j = 0; j < face.mNumIndices; j++)
                indices.emplace_back(face.mIndices[j]);
        }
       
       for(unsigned int i = 0; i < indices.size(); i++)
       {
        std::cout << indices[i] << std::endl;
       }
    }
    */
    Mesh::Mesh()
    {
        
    };

    std::vector<std::string> Mesh::Split(std::string str, char del)
    {
        std::stringstream ss(str);
        std::string temp;
        std::vector<std::string> ret;
        while (getline(ss, temp, del))
        {
            ret.emplace_back(temp);
        }
        return ret;
    }

    void Mesh::LoadObj(std::string fileName)
    {
        
        unsigned int face_id = 0;
        unsigned int normal_count = 0;
        //each line of the file
        std::string line, token;
        //input file
        std::ifstream objFile(fileName);
        
        //read file
        while(!objFile.eof())
        {
            Vertex vertex;
            Face face;
            std::getline(objFile, line);
            
           // std::cout << line << std::endl;
            
            token = line.substr(0, line.find_first_of (" "));
            
            if(token == "v")
            {
                std::vector<std::string> pos = Split(line, ' ');
          
                vertex.position = glm::vec3(std::stof(pos[1]), std::stof(pos[2]), std::stof(pos[3]));
                
                vertices.emplace_back(vertex);
            }
            
            if(token == "vn")
            {
                std::vector<std::string> norm = Split(line, ' ');
                
                vertex.normal = glm::vec3(std::stof(norm[1]), std::stof(norm[2]), std::stof(norm[3]));
                
                vertices[normal_count].normal = vertex.normal;
                normal_count++;
            }
            
            if(token == "f")
            {
                //get the token of each line of face
                std::vector<std::string> face_index = Split(line, ' ');
                face.face_id = face_id;
                for(int i = 0; i < face_index.size(); i++)
                {
                    if(face_index[i] != "f")
                    {
                        std::vector<std::string> sub_token = Split(face_index[i], '/');
                        face.vertices_id.emplace_back(std::stoi(sub_token[0]));
                    }
   
                }
                faces.emplace_back(face);
                
                face_id++;
            }
        }
        //close file
        objFile.close();
        
        //set up the indices list
        for(int i = 0; i < faces.size(); i++)
        {
            for(int j = 0; j < faces[i].vertices_id.size(); j++)
                indices.emplace_back(faces[i].vertices_id[j]);
        }
        
        for(int i = 0; i < vertices.size(); i++)
        {
            std::cout << "v: " << glm::to_string(vertices[i].position) << std::endl;
            std::cout << "vn: " << glm::to_string(vertices[i].normal) << std::endl;
        }
    }

    void Mesh::SetUp()
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
}
