#include <vector>
#include <iostream>
#include <queue>

#include <glm/glm.hpp>


class Vertex
{
public:
    // vertex position
    glm::vec3 position;
    // vertex normal
    glm::vec3 vertex_normal;
    //all neighbor vertex id
    std::vector<std::uint32_t> neighbor_vertex_id;
    //error matrix
    glm::mat4 error;
    //vertex id
    std::uint32_t vertex_id;

    Vertex();
    ~vertex(); 
};

class Pair
{
public:
    std::uint32_t v0;
    std::uint32_t v1;
    //the cost of deleting the pair
    float deletion_cost;
};

class Face
{
public:
    //id of face
    std::uint32_t face_id;

    //face normal
    glm::vec3 face_normal;

    //pointers of vertices that are included in the face
    std::vector<Vertex*> vertices_of_face;

    //pointers of faces are adjacent to the current face
    std::vector<Face*> neighbors_of_face;
};

class Edge
{
public:
    Vertex v0;
    Vertex v1;
};

class Heap
{
    
}