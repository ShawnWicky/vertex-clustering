#include <Interface/interface.hpp>

namespace MSc
{
    Interface::Interface(Inspector* Inspector):  _inspector(Inspector)
    {

    }

    void Interface::ShowGUI()
    {
        if(_showInspectorWindow) ShowInspectorWindow(&_showInspectorWindow);
    }

    void Interface::ShowInspectorWindow(bool* outIsOpen)
    {
        _inspector->ShowGuiWindow(outIsOpen);
    }
}
