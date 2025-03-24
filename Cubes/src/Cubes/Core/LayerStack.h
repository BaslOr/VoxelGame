#pragma once
#include "Core.h"
#include "Layer.h"

namespace Cubes {

    class CB_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return _layerStack.begin(); }
        std::vector<Layer*>::iterator end() { return _layerStack.end(); }

    private:
        std::vector<Layer*> _layerStack;
        uint32_t _layerInsertIndex = 0;
    };

}

