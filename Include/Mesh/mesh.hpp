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
    /*
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
    */

    //forward declartion
    class Vertex;
    class HalfEdge;
    class Face;
    class Edge;

    class Vertex
    {
    public:
        //position info
        glm::vec3 position;
        //normal info
        glm::vec3 normal;
        //the pointer of the half edge that start from the current vertex
        HalfEdge* half_edge_vertex;
    };
    
    class HalfEdge
    {
    public:
        
        // the vertex at the end of the half edge ( the vertex that half edge point to)
        Vertex* end_vertex;
        // the id of the half edge
        unsigned int half_edge_id;
        // id of the other pair(opposite) of the half edge
        unsigned int pair_id;
        // the face that current half edge belong to
        Face* face;
        // the next half edge of current half edge
        HalfEdge* next;
        // the previous half edge of current half edge
        HalfEdge* prev;
    };

    class Edge
    {
        // one of the half edge of the whole edge;
        HalfEdge* half_edge_edge;
        // the length of edge
        float length;
        // id of edge
        unsigned int edge_id;
    };

    class Face
    {
    public:
        // one of the half edge in the face
        HalfEdge* half_edge_face;
        // vertice in the face
        std::vector<unsigned int> vertices_id;
        // id of face
        unsigned int face_id;
    };

    class Weight
    {
    public:
        float weight;
        
        void CalculateWeight();
    };


    class Mesh
    {
    public:
        Mesh();
        
        std::vector<glm::vec3> vertices_positions;
        std::vector<glm::vec3> vertices_normals;
        std::vector<unsigned int> indices;
        
        //Load obj file
        void LoadObj(const char* fileName);
        
        //Write obj file
        void ExportObj(const char* fileName);
        
        //load indices array for rendering
        void LoadIndices();
    };
}
