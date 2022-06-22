#pragma once

#include <imgui.h>
#include <Render/scene.hpp>
#include <Algorithm/inspector.hpp>

namespace MSc
{
    class Interface
    {
    private:
        bool _showInspectorWindow = true;

        Inspector *_inspector;
    public:
    //constructor
        Interface(Inspector *Inspector);
    //Window
        void ShowGUI();
        void ShowInspectorWindow(bool* outIsOpen);
    };
}