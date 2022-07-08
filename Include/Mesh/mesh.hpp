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
        // weight of the edge (could be the w table)
        float weight;
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

    class Mesh
    {
    public:
        Mesh();
        
        //vertex info
        std::vector<Vertex> vertices;

        //edge info
        std::vector<Edge> edges;
        //face info
        std::vector<Face> faces;
        std::vector<unsigned int> indices;
        
        //split the string
        std::vector<std::string> Split(std::string str, char del);
        
        //opengl stuff
        unsigned int VAO, VBO, EBO;
        
        //Load obj file
        void LoadObj(std::string fileName);
        
        //Write obj file
        void ExportObj(std::string fileName);
        
        //load indices array for rendering
        void LoadIndices();
        
        //set up the opengl rendering items
        void SetUp();
        
        void Bind();
        
        void Render();
    };

    class Cell
    {
    public:
        //the id of vertices in the cell
        std::vector<unsigned int> points_in_cell;
        
        //the id of edges in the cell
        std::vector<unsigned int> edges_in_cell;
        
        //the id of Cell
        unsigned int cell_id;
        
    };

    class CellSet
    {
    public:
        //the id of cells in the grid
        std::vector<unsigned int> cells;
        
        //the total number of cells
        std::uint32_t cell_count;
        
        //the boundary of the grid in xyz dimensions
        float x_max, x_min;
        float y_max, y_min;
        float z_max, z_min;
    };
}
