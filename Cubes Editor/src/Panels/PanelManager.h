#pragma once
#include "Panel.h"

#include <vector>

namespace Cubes {

    class PanelManager {
    public:
        PanelManager();
        ~PanelManager();

        void OpenPanel(Panel* panel);
        void ClosePanel(Panel* panel);

        std::vector<Panel*>::iterator begin() { return _panels.begin(); }
        std::vector<Panel*>::iterator end() { return _panels.end(); }

    private:
        std::vector<Panel*> _panels;
    };

}
