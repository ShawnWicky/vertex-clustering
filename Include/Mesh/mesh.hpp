#pragma once

#include <glm/glm.hpp>
#include <Render/shader.hpp>

#include <string>
#include <vector>
#include <map>
#include <tuple>

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
    
    struct Vertex_Render
    {
        //position info
        glm::vec3 position;
        //normal info
        glm::vec3 normal;
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
        
        //the pointer of the start vertex and end vertex of the edge
        Vertex* start_ver;
        Vertex* end_ver;
        ///--------------------------------------
        /// functions
        ///--------------------------------------
    };

    class Face
    {
    public:
        Face();
        // one of the half edge in the face
        HalfEdge* half_edge_face;
        // vertice in the face
        std::vector<unsigned int> vertices_id;

        std::vector<unsigned int> normals_id;
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
        unsigned int in_dimension;
        
        // the boundary of the grid in xyz dimensions
        float x_max, x_min;
        float y_max, y_min;
        float z_max, z_min;
        
        void ConstructAxises(std::vector<Vertex> &iVertices, int dimension);
        
        void ConstructGrid(int in_dimension, std::vector<Cell> &iCells);
        
    };

    //used for easily represent weight
    typedef std::map<unsigned int, float> weight_table;

    //used for easily represent the data structure of C table (vertices in each cell)
    typedef std::map<unsigned int, std::vector<unsigned int>> cell_table;
    
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
        
        // map key = vertex id, map value = weight of the vertex
        // W table
        std::map<unsigned int, float> weight_of_vertex;
        
        // map key = cell id, map value = vertex id
        // the cell that each vertex falls in
        // R table
        std::map<unsigned int, unsigned int> representative_vertex_of_cell;
        
        // map key = cell id, map value = vertices id
        // vertices that falls in each cell
        // C table
        std::map<unsigned int, std::vector<unsigned int>> vertices_in_cell;
        
        // SV table
        std::vector<Vertex> simplified_vertices;
        
        // ST table
        std::vector<Face> simplified_triangles;
        
        
        //----------------------------------
        // Functions
        //----------------------------------

        // build vertices table without halfedge(v table)
        void BuildVertices(std::vector<glm::vec3> &positions, std::vector<glm::vec3> &normals, std::vector<Face>& iFaces);
        
        // create half edges for the mesh
        std::vector<HalfEdge> BuildHalfEdge(std::vector<Face> &iFaces, std::vector<Edge> &iEdges, std::vector<Vertex> &iVertices);
        
        // create edges for the mesh
        std::vector<Edge> BuildEdge(std::vector<Face> &iFaces, std::vector<Vertex> &iVertices);
        
        void AddHalfEdgeToFace(std::vector<HalfEdge> &iHalfEdges);
        
        void AddHalfEdgeToVertex(std::vector<HalfEdge> &iHalfEdges);
        
        // calculate the weight of each vertex;
        // fill the w table
        std::map<unsigned int, float> CalculateWeight(std::vector<Vertex> &iVertices, std::vector<Edge> &iEdges);
        
        // calculate the simplified vertices(SV) table
        std::vector<Vertex> CalculateSimplifiedVertices(cell_table &Ctable, weight_table &Wtable, std::vector<Vertex> &iVertices);
        
        // fill the r table
        std::map<unsigned int, unsigned int> CalculateRepresentativeVertices(CellSet &iGrid, std::vector<Vertex> &iVertices);
        
        // fill the c table
        std::map<unsigned int, std::vector<unsigned int>> CalculateVerticesInCell(std::vector<Vertex> &iVertices, CellSet &iGrid);
        
        // elimination
        std::vector<Face> Elimination(std::vector<Face> &iFaces,
            std::map<unsigned int, unsigned int>& iRtable,
            CellSet& iGrid,
            std::vector<Vertex>& iVertices,
            std::vector<Vertex>& iVertices_original);

        // calculate the new vertex normal for all vertices from ST table
        void CalculateVertexNormal(std::vector<Face> iFace, std::vector<Vertex>& iVertices);
        
        void Initialize(CellSet &iGrid, int dimension);

        void Terminate(Mesh &iMesh);

        bool GetBool()
        {
            return curvature_area;
        }
        
        void SetBool(bool input)
        {
            curvature_area = input;
        }
    private:
        
        bool curvature_area = false;
        
        // calculate the simplified faces' normal
        std::map<unsigned int, glm::vec3> CalculateFaceNormal(std::vector<Face> iFace, std::vector<Vertex>& iVertices);

        // helper function for r and c to reduce the code redundancy
        unsigned int GetCellid(Vertex& iVertex, CellSet& cell);

        ///------------------------------------------------------------
        ///OpenGL Section
        ///------------------------------------------------------------
    public:
        //opengl stuff
        std::vector<Vertex_Render> vertices_render;

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

        //set up the opengl rendering items
        void SetUp();
        
        void Render(Shader &shader);
    };
}
