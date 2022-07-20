#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <queue>
#include <algorithm>
#include <stdlib.h>

#include <Mesh/mesh.hpp>

#include <glad/glad.h>
#include <glm/gtx/string_cast.hpp>

namespace MSc
{
    ///-------------------------------------------------
    /// Vertex Section
    ///-------------------------------------------------
    Vertex::Vertex()
    {
        
    }

    ///-------------------------------------------------
    /// HalfEdge Section
    ///-------------------------------------------------
    HalfEdge::HalfEdge()
    {

    }

    bool HalfEdge::MakeAdjacent(HalfEdge* in, HalfEdge* out)
    {
        // already adjacent
        if(in->next == out)
        {
            return true;
        }
        
        return true;
    }

    
    ///-------------------------------------------------
    /// Edge Section
    ///-------------------------------------------------
    Edge::Edge()
    {
        this->half_edge_edge = nullptr;
    }

    ///-------------------------------------------------
    /// Face Section
    ///-------------------------------------------------
    Face::Face()
    {
        
    }

    ///-------------------------------------------------
    /// Cell Section
    ///-------------------------------------------------
    Cell::Cell()
    {
        this->left_bottom_near_point = glm::vec3(0.f,0.f,0.f);
        this->cell_id = -1;
        this->number_of_vertices = 0;
    }

    ///-------------------------------------------------
    /// CellSet Section
    ///-------------------------------------------------
    CellSet::CellSet()
    {

    }

    void CellSet::ConstructAxises(std::vector<Vertex> &iVertices, int dimension)
    {
        // 1. Loop through the 'vertices' vector, find the minX, minY, minZ, maxX, maxY, maxZ.
        // 2. Set (0,0,0) to be the origin of the grid
        // 3. Set the length X to (maxX - minX + 0.1), length Y to (maxY - minY + 0.1), length Z to (maxZ - minZ + 0.1).
        std::vector<float> x_pos;
        std::vector<float> y_pos;
        std::vector<float> z_pos;
        
        for(unsigned int i = 0; i < iVertices.size(); i++)
        {
            x_pos.emplace_back(iVertices[i].position.x);
            y_pos.emplace_back(iVertices[i].position.y);
            z_pos.emplace_back(iVertices[i].position.z);
        }
        
        //get the max and min in x dimension
        x_min = *std::min_element(x_pos.begin(), x_pos.end());
        x_max = *std::max_element(x_pos.begin(), x_pos.end());
        
        //get the max and min in y dimension
        y_min = *std::min_element(y_pos.begin(), y_pos.end());
        y_max = *std::max_element(y_pos.begin(), y_pos.end());
        
        //get the max and min in z dimension
        z_min = *std::min_element(z_pos.begin(), z_pos.end());
        z_max = *std::max_element(z_pos.begin(), z_pos.end());
        
        length_x = (x_max - x_min) / dimension;
        length_y = (y_max - y_min) / dimension;
        length_z = (z_max - z_min) / dimension;
        
        //clear the vector
        x_pos.clear();
        y_pos.clear();
        z_pos.clear();
    }

    void CellSet::ConstructGrid(int in_dimension, std::vector<Cell> &iCells)
    {
        // 1. divide the lenght of x, y, z axies by thier dimensions to get the length of each cell in thier dimension
        //  save the length to the parameters length_x, length_y, length_z
        // 2. set the boundary to the minX->maxX, minY->maxY, minZ->maxZ
        // 3. loop through the cells to add cells to the grid
         Cell cell;
         for(unsigned int i = 0; i < in_dimension; i++ ) //(z dimension)
             for(unsigned int j = 0; j < in_dimension; j++ ) //(y dimension)
                 for(unsigned int m = 0; m < in_dimension; m++ ) //(x dimension)
                 {
                     
                     cell.left_bottom_near_point = glm::vec3( m * length_x + x_min, j * length_y + y_min, i * length_z + z_min);
                     cell.cell_id = m + in_dimension * j + std::powf((float)in_dimension, 2.f) * i;
                     iCells.emplace_back(cell);
                     cell_count++;
                 }
    }


    ///-------------------------------------------------
    /// Mesh Section
    ///-------------------------------------------------

    // the section for Rendering
    
    Mesh::Mesh(std::string fileName)
    {
        LoadObj(fileName);
        SetUp();
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
        
        //each line of the file
        std::string line, token;
        //input file
        std::ifstream objFile(fileName);
        
        //read file
        while(!objFile.eof())
        {
            Face face;
            std::getline(objFile, line);
            
           // std::cout << line << std::endl;
            
            token = line.substr(0, line.find_first_of (" "));
            
            if(token == "v")
            {
                std::vector<std::string> pos = Split(line, ' ');
          
                glm::vec3 position = glm::vec3(std::stof(pos[1]), std::stof(pos[2]), std::stof(pos[3]));
                
                positions.emplace_back(position);
            }
            
            if(token == "vn")
            {
                std::vector<std::string> norm = Split(line, ' ');
                
                glm::vec3 normal = glm::vec3(std::stof(norm[1]), std::stof(norm[2]), std::stof(norm[3]));
                
                normals.emplace_back(normal);
            }
            
            if(token == "f")
            {
                //get the token of each line of face
                std::vector<std::string> face_index = Split(line, ' ');
                face.face_id = face_id;
                for(int i = 0; i < face_index.size(); i++)
                {
                    if(face_index[i] != "f" )
                    {
                        std::vector<std::string> sub_token = Split(face_index[i], '/');
                        
                        face.vertices_id.emplace_back(std::stoi(sub_token[0])-1);
                    }
   
                }
                face.half_edge_face = nullptr;
                
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
        
        //set up the vertices table
        BuildVertices(positions, normals);
    }

    void Mesh::ExportObj(std::string fileName)
    {
        std::ofstream writeFile(fileName);
        writeFile << "o " << fileName << "\n";
        
        if( writeFile.fail() )
        {
            std::cerr << "!Error opening " << fileName << std::endl;
            return;
        }
        
        if(writeFile.is_open())
        {
            for(unsigned int i = 0; i < positions.size(); i++)
            {
                writeFile << "v " << Mesh::positions[i].x << " " << Mesh::positions[i].y << " " << Mesh::positions[i].z << "\n";
            }
        
            for(unsigned int i = 0; i < normals.size(); i++)
            {
                writeFile << "vn " << Mesh::normals[i].x << " " << Mesh::normals[i].y << " " << Mesh::normals[i].z << "\n";
            }
        
            for(const auto& face: faces)
            {
                writeFile << "f ";
                for(std::uint8_t j = 0; j < face.vertices_id.size(); j++)
                {
                    if(j == 2)
                        writeFile << face.vertices_id[j]+1 << "//" << face.vertices_id[j]+1 << "\n";
                    else
                        writeFile << face.vertices_id[j]+1 << "//" << face.vertices_id[j]+1 << " ";
                }
            }
            writeFile.close();
        }
        
    }

    void Mesh::BuildVertices(std::vector<glm::vec3> &iPositions, std::vector<glm::vec3> &iNormals)
    {
        for(unsigned int i = 0; i < iPositions.size(); i++)
        {
            Vertex vertex;
            
            vertex.position = iPositions[i];
            vertex.normal = iNormals[i];
            vertex.vertex_id = i;
            vertex.half_edge_vertex = nullptr;
            
            vertices.emplace_back(vertex);
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

    void Mesh::Render(Shader &shader)
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }




    // The section for Simplification

    std::vector<HalfEdge> Mesh::BuildHalfEdge(std::vector<Face> &iFaces, std::vector<Edge> &iEdges, std::vector<Vertex> &iVertices)
    {
        std::vector<HalfEdge> temp;
        
        Edge edge;
        HalfEdge half_edge;
        // 1. Loop the faces
        for ( int i = 0; i < iFaces.size(); i++)
        {
            unsigned int counter = 0;
            // 2. For each face add half edges to the temp vector
            for( int j = 0; j < 3; j++ )
            {
                if( j + 1 > 2)
                {
                    half_edge.end_vertex = &iVertices[iFaces[i].vertices_id[j-2]];
                    half_edge.face = &iFaces[i];
                    half_edge.half_edge_id = 3 * iFaces[i].face_id + counter;
                }
                else
                {
                    half_edge.end_vertex = &iVertices[iFaces[i].vertices_id[j+1]];
                    half_edge.face = &iFaces[i];
                    half_edge.half_edge_id = 3 * iFaces[i].face_id + counter;
                }
                temp.emplace_back(half_edge);
            }
        }
        
        // 3.
        
        return temp;
    }

    std::vector<Edge> Mesh::BuildEdge(std::vector<Face> &iFaces, std::vector<Vertex> &iVertices)
    {
        //the temporary vector of edges that need to be returned
        std::vector<Edge> temp(3 * iFaces.size());
        
        Edge edge0;
        Edge edge1;
        Edge edge2;
        // 1. loop through the faces
        // 2. for each face construct the edge
        for(int i = 0; i < iFaces.size(); i++)
        {
            edge0.start_vertex = iFaces[i].vertices_id[0];
            edge0.end_vertex = iFaces[i].vertices_id[1];
            
            edge1.start_vertex = iFaces[i].vertices_id[1];
            edge1.end_vertex = iFaces[i].vertices_id[2];
            
            edge2.start_vertex = iFaces[i].vertices_id[2];
            edge2.end_vertex = iFaces[i].vertices_id[0];
            
            temp[3*i] = edge0;
            temp[3*i+1] = edge1;
            temp[3*i+2] = edge2;
        }

        // remove duplicates
        for(unsigned int i = 0; i < temp.size(); i++)
        {
            for(unsigned int j = 0; j < temp.size(); j++)
            {
                if(temp[i].start_vertex == temp[j].end_vertex && temp[i].end_vertex == temp[j].start_vertex)
                {
                    temp.erase(temp.begin()+j);
                }
            }
        }

        // calculate length
        for(unsigned int i = 0; i < temp.size(); i++)
        {
            glm::vec3 e0 = iVertices[temp[i].start_vertex].position;
            glm::vec3 e1 = iVertices[temp[i].end_vertex].position;
            
            temp[i].length = glm::distance(e0, e1);
        }
        

        return temp;
    }


    //cell_table -> std::map<int, std::vector<unsigned int>>
    //weight_table -> std::map<int, float>
    void Mesh::CalculateSVtable(cell_table &Ctable, weight_table &Wtable, std::vector<Vertex> &iVertices)
    {
        
        unsigned int new_vertex_id = 0;
        // 1. loop through the cells
        for(auto const& cell: Ctable)
        {
            Vertex vertex;
            // when there is no vertex in the cell
            if(cell.second.size() == 0)
            {
                //do nothing
            }
            // when there is only one vertex in the cell
            else if(cell.second.size() < 2 && cell.second.size() > 0)
            {
                vertex.position = iVertices[cell.second[0]].position;
                vertex.vertex_id = new_vertex_id;
                vertex.half_edge_vertex = nullptr;
                
                simplified_vertices.emplace_back(vertex);
                
                new_vertex_id++;
            }
            // when there are more than one vertex in the cell
            else
            {
                // use for temporary saving the represetative vertex position
                glm::vec3 temp_pos = glm::vec3(0.f, 0.f, 0.f);
            
                float cell_total_weight = 0.f;
                
                // 2. loop through the vertices in cell
                for(auto id: cell.second)
                    cell_total_weight = Wtable[id] + cell_total_weight;
            
                for(auto id: cell.second)
                    // representative vertex = (vertex.position * ( vertex_weight / total_vertices_weight_cell)) * all_vertices
                temp_pos = temp_pos + iVertices[id].position * Wtable[id] / cell_total_weight;
                
                vertex.position = temp_pos;
                vertex.vertex_id = new_vertex_id;
                vertex.half_edge_vertex = nullptr;
                
                simplified_vertices.emplace_back(vertex);
                
                new_vertex_id++;
            }
        }
        
    }

    // C table
    std::map<unsigned int, std::vector<unsigned int>> Mesh::CalculateVerticesInCell(std::vector<Vertex> &iVertices, CellSet &iGrid)
    {
        //the output c table
        std::map<unsigned int, std::vector<unsigned int>> c_table;
        
        //the vector of vertices in the cell
        std::vector<unsigned int> vertices_in_cell;

        //loop through the grid
        for(unsigned int i = 0; i < iGrid.cells.size(); i++)
        {
            //loop through the vertices
            for(unsigned int j = 0; j < iVertices.size(); j++)
            {
                // shift the vertex to the positive half of the axis
                glm::vec3 shifted_vertex = iVertices[j].position - glm::vec3(iGrid.x_min, iGrid.y_min, iGrid.z_min);
                
                // get he floor number of the (shifted vertex position / the length of a cell in each dimension)
                unsigned int x_dimension = static_cast<unsigned int>(std::floor(shifted_vertex.x / iGrid.length_x));
                unsigned int y_dimension =  static_cast<unsigned int>(std::floor(shifted_vertex.y / iGrid.length_y));
                unsigned int z_dimension =  static_cast<unsigned int>(std::floor(shifted_vertex.z / iGrid.length_z));
                
                // if the vertex is fall on the top / right / far plane of the whole cluster
                if(x_dimension == iGrid.in_dimension)
                    x_dimension = x_dimension - 1;
                else if (y_dimension == iGrid.in_dimension)
                    y_dimension = y_dimension - 1;
                else if (z_dimension == iGrid.in_dimension)
                    z_dimension = z_dimension - 1;
                
                // convert the x,y,z dimension of the cell to cell id
                if(iGrid.cells[i].cell_id == (x_dimension + (y_dimension * iGrid.in_dimension) + (z_dimension * std::powf((float)iGrid.in_dimension,2.f))))
                {
                    vertices_in_cell.emplace_back(vertices[j].vertex_id);
                }
            }
            
            c_table.insert(std::make_pair(iGrid.cells[i].cell_id, vertices_in_cell));
            
            vertices_in_cell.clear();
        }
        return c_table;
    }
 
    // W table
    std::map<int, float> Mesh::CalculateWeight(std::vector<Vertex> &iVertices, std::vector<Edge> &iEdges)
    {
        // 1. loop through the vertices
        // 2. find all edges attached on the vertex
        // 3. compare the length of each edge attached on vertex (use priority queue to auto order the length in descending order)
        // 4. attach the longest length to the weight of vertex
        
        
        // get the length of edges
        
        std::map<int, float> temp;
        
        for(unsigned int i = 0; i < iVertices.size(); i++)
        {
            std::priority_queue<float> length_queue;
            
            for(unsigned int j = 0; j < iEdges.size(); j++)
            {
                if(iEdges[j].start_vertex == iVertices[i].vertex_id || iEdges[j].end_vertex == iVertices[i].vertex_id)
                {
                    length_queue.push(iEdges[j].length);
                }
            }
            
            temp.insert(std::pair<unsigned int, float>(iVertices[i].vertex_id, length_queue.top()));
        }
        
        weight_of_vertex = temp;
        
        return weight_of_vertex;
    }

    // R table
    std::map<int, int> Mesh::CalculateRepresentativeVertices(CellSet &iGrid, std::vector<Vertex> &iVertices)
    {
        std::map<int, int> temp;

        
        return temp;
    }

    std::tuple<std::vector<Vertex>, std::vector<Edge>, std::vector<Face>> Mesh::Elimination(std::vector<Face> iFaces, std::map<int, int> iRtable)
    {
        std::vector<Face> faces;
        std::vector<Edge> edges;
        std::vector<Vertex> points;
        
        return {points, edges, faces};
    }

    void Mesh::Initialize(CellSet &iGrid, int dimension)
    {
        edges = BuildEdge(faces, vertices);
        half_edges = BuildHalfEdge(faces, edges, vertices);
        
        iGrid.ConstructAxises(vertices, dimension);
        iGrid.ConstructGrid(dimension, iGrid.cells);
        
        representative_vertex_of_cell = CalculateRepresentativeVertices(iGrid, vertices);
        
        vertices_in_cell = CalculateVerticesInCell(vertices, iGrid);
        
        weight_of_vertex = CalculateWeight(vertices, edges);
        
    }

    void Mesh::Terminate(Mesh &iMesh)
    {
        //Simplification parameters
        iMesh.vertices.clear();
        iMesh.edges.clear();
        iMesh.half_edges.clear();
        iMesh.faces.clear();
        iMesh.weight_of_vertex.clear();
        iMesh.representative_vertex_of_cell.clear();
        iMesh.vertices_in_cell.clear();
        iMesh.simplified_vertices.clear();
        iMesh.simplified_points.clear();
        iMesh.simplified_edges.clear();
        iMesh.simplified_triangles.clear();

        //OpenGL parmeters
        iMesh.positions.clear();
        iMesh.normals.clear();
        iMesh.indices.clear();
    }
}
