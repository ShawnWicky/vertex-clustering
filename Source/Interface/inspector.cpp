#include <Interface/inspector.hpp>


namespace MSc
{
    Inspector::Inspector(CellSet& iGrid, Mesh& iMesh): _grid(iGrid), _mesh(iMesh)
    {

    }
    
    void Inspector::ShowGuiWindow(bool* outIsOpen)
    {

        static char exportBuf[64] = "";
 
        if(ImGui::Begin("Controller"), outIsOpen)
        {
            ImGui::InputInt("##dimension", &_grid.in_dimension);
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

            ImGui::End();
        }
    }
}
