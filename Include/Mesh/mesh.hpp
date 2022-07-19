#pragma once

#include <glm/glm.hpp>
#include <Render/shader.hpp>

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace MSc
{
    //forward declartion
    class Vertex;
    class HalfEdge;
    class Edge;
    class Face;

    class Vertex
    {
    public:
        Vertex();
    
        //position info
        glm::vec3 position;
        //normal info
        glm::vec3 normal;
        //the pointer of the half edge that start from the current vertex
        HalfEdge* half_edge_vertex;
        //vertex id
        unsigned int vertex_id;
    };
    
    class HalfEdge
    {
    public:
        HalfEdge();
        // the vertex at the end of the half edge ( the vertex that half edge point to)
        Vertex* end_vertex;
        // the id of the half edge
        unsigned int half_edge_id;
        // id of the other pair(opposite) of the half edge
        HalfEdge* pair;
        // the face that current half edge belong to
        Face* face;
        // the next half edge of current half edge
        HalfEdge* next;
        // the previous half edge of current half edge
        HalfEdge* prev;
        
        bool MakeAdjacent(HalfEdge* in, HalfEdge* out);
    };

    class Edge
    {
    public:
        
        //Constructor
        Edge();
        
        // one of the half edge of the whole edge;
        HalfEdge* half_edge_edge;
        
        //length of edge
        float length = -1.f;
        
        //the id of the start vertex and end vertex of the edge
        unsigned int start_vertex;
        unsigned int end_vertex;
        
        ///--------------------------------------
        /// functions
        ///--------------------------------------
        
        static std::vector<Edge> BuildEdge(std::vector<Face> faces, std::vector<Vertex> vertices);
        
        bool isBoundary();
    private:
        // Compare function for std::sort
        static bool Compare(Edge e0, Edge e1);
    };

    class Face
    {
    public:
        Face();
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
        Cell();
        
        //this is the point on the left bottom corner of the cell whose
        //coordinate is based on the new grid coordinate
        glm::vec3 left_bottom_near_point;
    
        //the id of Cell
        unsigned int cell_id;
        
        //vertex count
        unsigned int number_of_vertices;
        
    };

    class CellSet
    {
    public:
        CellSet();
        
        // the id of cells in the grid
        std::vector<Cell> cells;
        
        // the total number of cells
        std::uint32_t cell_count;
    
        //the length of the cell in each axis
        float length_x, length_y, length_z;
        
        // xyz dimensions (user input)
        // the dimensions are the number of segments in the axis
        // In this period you can only form a cube(3D) or square(2D) grid
        int in_dimension;
        
        // the boundary of the grid in xyz dimensions
        float x_max, x_min;
        float y_max, y_min;
        float z_max, z_min;
        
        void ConstructAxises(std::vector<Vertex> &iVertices);
        
        void ConstructGrid(unsigned int in_dimension);
        
    };

    //used for easily represent weight
    typedef std::map<int, float> weight_table;

    //used for easily represent the data structure of C table (vertices in each cell)
    typedef std::map<unsigned int, std::vector<unsigned int>> cell_table;
    
    class Mesh
    {
    public:
        Mesh(std::string fileName);
        
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
        
        CellSet grid;

        // map key = vertex id, map value = weight of the vertex
        // W table
        std::map<int, float> weight_of_vertex;
        
        // map key = vertex id, map value = cell id
        // the cell that each vertex falls in
        // R table
        std::map<int, int> representative_vertex_of_cell;
        
        // map key = cell id, map value = vertices id
        // vertices that falls in each cell
        // C table
        std::map<int, std::vector<int>> vertices_in_cell;
        
        // SV table
        std::vector<Vertex> simplified_vertices;
        
        // ST table
        std::vector<Face> simplified_triangles;
        
        // SE table
        std::vector<Edge> simplified_edges;
        
        // SP tab le
        std::vector<Vertex> simplified_points;
        
        
        //----------------------------------
        // Functions
        //----------------------------------
        
        // build vertices table without halfedge(v table)
        void BuildVertices(std::vector<glm::vec3> positions, std::vector<glm::vec3> normals);
        
        // create half edges for the mesh
        void BuildHalfEdge(std::vector<Edge> iEdges, std::vector<Vertex> iVertices);

        // calculate the weight of each vertex
        std::map<int, float> CalculateWeight(std::vector<Vertex> iVertices, std::vector<Edge> iEdges);
        
        // fill the r table
        std::map<int, int> CalculateRepresentativeVertices(CellSet &iGrid, std::vector<Vertex> &iVertices);
        
        // calculate the simplified vertices(SV) table
        void CalculateSVtable(cell_table &Ctable, weight_table &Wtable, std::vector<Vertex> &iVertices);
        
        // fill the c table
        std::map<unsigned int, std::vector<unsigned int>> CalculateVerticesInCell(std::vector<Vertex> &iVertices, CellSet &iGrid);
        
        // elimination
        // complete the ST/SE/SP table
        std::tuple<std::vector<Vertex>, std::vector<Edge>, std::vector<Face>> Elimination(std::vector<Face> iFaces, std::map<int, int> iRtable);
        
        // reduce duplicates for simplifed mesh
        void ReduceDuplicates();
        
        // calculate the new vertex normal for all vertices from ST table
        void CalculateVertexNormal(std::vector<Face> iFace);
        
        void Initialize();
        ///------------------------------------------------------------
        ///OpenGL Section
        ///------------------------------------------------------------
        //opengl stuff
        std::vector<glm::vec3> positions;
        
        std::vector<glm::vec3> normals;
        
        std::vector<unsigned int> indices;
        
        unsigned int VAO, VBO, EBO;
        
        //split the string
        std::vector<std::string> Split(std::string str, char del);
        
        //Load obj file
        void LoadObj(std::string fileName);
        
        //Write obj file
        void ExportObj(std::string fileName);
        
        //load indices array for rendering
        void LoadIndices();
        
        //set up the opengl rendering items
        void SetUp();
        
        void Render(Shader &shader);
    };

}
