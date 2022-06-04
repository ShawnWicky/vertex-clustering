#include <Interface.hpp>

namespace MSc
{
    Interface::Interface(Scene* scene, Inspector* Inspector): _scene(scene), _inspector(Inspector)
    {

    }

    void Interface::ShowGUI()
    {
        if(_showSceneWindow) ShowSceneWindow(&_showSceneWindow);
        if(_showInspectorWindow) ShowInspectorWindow(&_showInspectorWindow);
    }

    void Interface::ShowInspectorWindow(bool* outIsOpen)
    {
        _inspector->ShowGuiWindow(outIsOpen);
    }

    void Interface::ShowSceneWindow(bool* outIsOpen)
    {
        _scene->ShowGuiWindow(outIsOpen);
    }
}