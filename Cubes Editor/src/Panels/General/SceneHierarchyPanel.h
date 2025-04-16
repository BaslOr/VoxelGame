#pragma once
#include <Cubes/Core/Project/Scene.h>
#include <Cubes/Core/Project/Entity.h>
#include "../Panel.h"
#include "InspectorPanel.h"

namespace Cubes {

    class SceneHierarchyPanel : public Panel {
    public:
        SceneHierarchyPanel(Scene* context, InspectorPanel* inspector = nullptr);

        inline void SetContext(Scene* context) { _context = context; }

        void OnImGuiRender() override;

    private:
        void DrawEntityNode(Entity entity);

    private:
        Scene* _context = nullptr; //TODO: Should be a Cubes::weak_ptr or sth 
        InspectorPanel* _inspector;
    };

}
