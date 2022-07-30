#include <Interface/inspector.hpp>
#include <iostream>

namespace MSc
{
    Inspector::Inspector(CellSet& iGrid, Mesh& iMesh): _grid(iGrid), _mesh(iMesh)
    {

    }
    
    void Inspector::ShowGuiWindow(bool* outIsOpen)
    {
        static char loadBuf[64] = "";
        static char exportBuf[64] = "";
 
        if(ImGui::Begin("Controller"), outIsOpen)
        {
            // This Part is load file
            ImGui::InputText("##load", loadBuf, 64);
            ImGui::SameLine();
            if (ImGui::Button("Load File"))
            {

#ifdef __APPLE__
                _mesh.LoadObj("../../assets/" + std::string(loadBuf));
#else
                _mesh.LoadObj("./assets/" + std::string(loadBuf));
#endif  
                _mesh.SetUp();
            }

            ImGui::Separator();

            // This part is change the weighting method (the way to compute W table)
            if(ImGui::Button(_mesh.GetBool() ? "Curvature###curvature model" : "Area###area model"))
            {
                _mesh.SetBool(!_mesh.GetBool());
               // std::cout << _mesh.GetBool() << std::endl;
            }
            
            ImGui::Separator();

            ImGui::InputScalar("##dimension", ImGuiDataType_U32, &_grid.in_dimension, nullptr, nullptr, "%u");
            ImGui::SameLine();
            
            if(ImGui::Button("Initialize"))
            {
                _mesh.Initialize(_grid, _grid.in_dimension);
            }

            ImGui::Separator();
            
            ImGui::InputText("##export", exportBuf, 64);
            ImGui::SameLine();
            
            if(ImGui::Button("Export File"))
            {
#ifdef __APPLE__
                _mesh.ExportObj("../../assets/" + std::string(exportBuf));
#else
                _mesh.ExportObj("./assets/" + std::string(exportBuf));
#endif
            }

            ImGui::Separator();
            
            if(ImGui::Button("Terminate"))
            {
                Terminate(_mesh, _grid);
            }
               
            ImGui::End();
        }
    }

    void Inspector::Terminate(Mesh &iMesh, CellSet &iGrid)
    {  
        //Simplification parameters
        iMesh.vertices.clear();
        iMesh.edges.clear();
        iMesh.faces.clear();
        iMesh.weight_of_vertex.clear();
        iMesh.representative_vertex_of_cell.clear();
        iMesh.vertices_in_cell.clear();
        iMesh.simplified_vertices.clear();
        iMesh.simplified_triangles.clear();

        //OpenGL parmeters
        iMesh.positions.clear();
        iMesh.normals.clear();
        iMesh.indices.clear();
        iMesh.vertices_render.clear();
        
        iGrid.cells.clear();
    }
}