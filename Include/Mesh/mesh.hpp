#pragma once

#include <glm/glm.hpp>
#include <Render/shader.hpp>

#include <string>
#include <vector>
#include <map>

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
        
        //id of vertices that consturct the edge
        unsigned int v0, v1;
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
        CellSet(unsigned int in_x_dimension, unsigned int in_y_dimension, unsigned int in_z_dimension);
        
        //the id of cells in the grid
        std::vector<unsigned int> cells;
    
        //the total number of cells
        std::uint32_t cell_count;
    
        //xyz dimensions
        unsigned int x_dimension, y_dimension, z_dimension;
        
        //the boundary of the grid in xyz dimensions
        float x_max, x_min;
        float y_max, y_min;
        float z_max, z_min;
        
        void ConstructGrid(unsigned int x_dimension, unsigned int y_dimension, unsigned int z_dimension);
    };


    class Mesh
    {
    public:
        Mesh();
        
        ///------------------------------------------------------------
        ///Vertex Clustering Section
        ///------------------------------------------------------------
        
        //----------------------------------
        // Parameter
        //----------------------------------
        
        //vertex info
        std::vector<Vertex> vertices;
        //edge info
        std::vector<Edge> edges;
        //half edge info
        std::vector<HalfEdge> half_edges;
        //face info
        std::vector<Face> faces;
        
        
        // map key = edge id, map value = edge weight
        // contains weights of each edge
        // w table
        std::map<int, float> w_table;
        
        // map key = vertex id, map value = cell id
        // the cell that each vertex falls in
        // r table
        std::map<int, int> r_table;
        
        // map key = cell id, map value = vertices id
        // vertices that falls in each cell
        // c table
        std::map<int, std::vector<int>> c_table;
        
        //----------------------------------
        // Functions
        //----------------------------------
        
        //split the string
        std::vector<std::string> Split(std::string str, char del);
        
        //build vertices table without halfedge(v table)
        void BuildVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals);
        
        //create half edges for the mesh
        void BuildHalfEdge(std::vector<Face> &faces);
        
        //calculate the weight of each edge
        std::map<int, float> CalculateWeight(std::vector<Edge> iEdges);
        
        //fill the r table
        std::map<int, int> CalculateRtable(CellSet grid, std::vector<Vertex> vertices);
        
        ///------------------------------------------------------------
        ///OpenGL Section
        ///------------------------------------------------------------
        //opengl stuff
        std::vector<glm::vec3> positions;
        
        std::vector<glm::vec3> normals;
        
        std::vector<unsigned int> indices;
        
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

}
