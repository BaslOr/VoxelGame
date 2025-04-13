#pragma once
#include <Cubes/Core/Project/Scene.h>
#include <Cubes/Core/Project/Entity.h>

namespace Cubes {

    class SceneHierarchyPanel {
    public:
        SceneHierarchyPanel(Scene* context);

        inline void SetContext(Scene* context) { _context = context; }

        void OnImGuiRender();

    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents();

    private:
        Scene* _context = nullptr; //TODO: Should be a Cubes::weak_ptr or sth 
        Entity _selectedEntity;
    };

}
