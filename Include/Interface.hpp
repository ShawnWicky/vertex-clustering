#pragma once

#include <imgui.h>
#include <Render/scene.hpp>
#include <Algorithm/inspector.hpp>

namespace MSc
{
    class Interface
    {
    private:
        bool _showSceneWindow = true;
        bool _showInspectorWindow = true;

        Scene *_scene;
        Inspector *_inspector;
    public:
    //constructor
        Interface(Scene *scene, Inspector *Inspector);
    //Window
        void ShowGUI();
        void ShowSceneWindow(bool* outIsOpen);
        void ShowInspectorWindow(bool* outIsOpen);
    };
}