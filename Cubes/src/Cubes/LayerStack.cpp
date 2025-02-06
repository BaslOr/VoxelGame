#include "cbpch.h"
#include "LayerStack.h"

namespace Cubes {

    LayerStack::LayerStack()
    {
        _layerInsert = _layerStack.begin();
    }



    LayerStack::~LayerStack()
    {
        for (auto* layer : _layerStack) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        _layerStack.emplace(_layerInsert, layer);
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        _layerStack.emplace_back(overlay);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(_layerStack.begin(), _layerStack.end(), layer);
        if (it != _layerStack.end()) {
            _layerStack.erase(it);
            _layerInsert--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(_layerStack.begin(), _layerStack.end(), overlay);
        if (it != _layerStack.end()) 
            _layerStack.erase(it);
        
    }

}
