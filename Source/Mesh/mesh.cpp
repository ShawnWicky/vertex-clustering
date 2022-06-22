#include <iostream>

#include <Mesh/mesh.hpp>

#include <tiny_obj_loader.h>

namespace MSc
{
    // Model
    Mesh::Model::Model() noexcept = default;

    Mesh::Model::Model( Model&& aOther ) noexcept
	    : modelName( std::exchange( aOther.modelName, {} ) )
	    , modelSourcePath( std::exchange( aOther.modelSourcePath, {} ) )
	    , meshes( std::move( aOther.meshes ) )
	    , vertexPositions( std::move( aOther.vertexPositions ) )
	    , vertexNormals( std::move( aOther.vertexNormals ) )
	    , vertexTextureCoords( std::move( aOther.vertexTextureCoords ) )
    {}

    Mesh::Model& Mesh::Model::operator=( Model&& aOther ) noexcept
    {
	    std::swap( modelName, aOther.modelName );
	    std::swap( modelSourcePath, aOther.modelSourcePath );
	    std::swap( meshes, aOther.meshes );
	    std::swap( vertexPositions, aOther.vertexPositions );
	    std::swap( vertexNormals, aOther.vertexNormals );
	    std::swap( vertexTextureCoords, aOther.vertexTextureCoords );
	    return *this;
    }


    Mesh::Model Mesh::loadobj(std::string fileName)
    {
        Mesh::Model model;
        tinyobj::ObjReaderConfig read_config;
        read_config.mtl_search_path = "./assets/";

        tinyobj::ObjReader reader;

        if (!reader.ParseFromFile(fileName, read_config)) 
        {
            if (!reader.Error().empty()) 
            {
                 std::cerr << "TinyObjReader: " << reader.Error();
            }
            exit(1);
        }

        if (!reader.Warning().empty()) 
        {
            std::cout << "TinyObjReader: " << reader.Warning();
        }

        auto& attrib = reader.GetAttrib();
        auto& shapes = reader.GetShapes();
        auto& materials = reader.GetMaterials();

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++) 
                {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    model.vertexPositions.emplace_back(attrib.vertices[3*size_t(idx.vertex_index)+0]);
                    model.vertexPositions.emplace_back(attrib.vertices[3*size_t(idx.vertex_index)+1]);
                    model.vertexPositions.emplace_back(attrib.vertices[3*size_t(idx.vertex_index)+2]);

                    // Check if `normal_index` is zero or positive. negative = no normal data
                    if (idx.normal_index >= 0) 
                    {
                        model.vertexNormals.emplace_back(attrib.normals[3*size_t(idx.normal_index)+0]);
                        model.vertexNormals.emplace_back(attrib.normals[3*size_t(idx.normal_index)+1]);
                        model.vertexNormals.emplace_back(attrib.normals[3*size_t(idx.normal_index)+2]);
                    }

                    // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                    if (idx.texcoord_index >= 0) 
                    {
                        model.vertexTextureCoords.emplace_back(attrib.texcoords[2*size_t(idx.texcoord_index)+0]);
                        model.vertexTextureCoords.emplace_back(attrib.texcoords[2*size_t(idx.texcoord_index)+1]);
                    }

                    // Optional: vertex colors
                    // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                    // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                    // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
                }
                
                index_offset += fv;

                // per-face material
                shapes[s].mesh.material_ids[f];
            }
        }   
    
        return model;
    }
}