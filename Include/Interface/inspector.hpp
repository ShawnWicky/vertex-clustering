#pragma once

#include <imgui.h>

#include <Mesh/mesh.hpp>
namespace MSc
{
    class Inspector
    {
    public:
        Inspector(CellSet &iGrid, Mesh &iMesh);
        
        void ShowGuiWindow(bool* outIsOpen);
        
    private:
        Mesh &_mesh;
        CellSet &_grid;
    };
}
