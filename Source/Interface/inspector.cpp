#include <Interface/inspector.hpp>


namespace MSc
{
    Inspector::Inspector(CellSet* iGrid): _grid(iGrid)
    {

    }
    
    void Inspector::ShowGuiWindow(bool* outIsOpen)
    {
        if(ImGui::Begin("Controller"), outIsOpen)
        {
            ImGui::Text("Dimension: ");
            ImGui::SameLine();
            ImGui::InputInt("##dimension", &_grid->in_dimension);
            
            ImGui::Separator();
            
            
            ImGui::End();
        }
    }
}
