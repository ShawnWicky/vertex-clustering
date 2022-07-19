#pragma once

#include <Render/scene.hpp>
#include <Interface/inspector.hpp>

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
