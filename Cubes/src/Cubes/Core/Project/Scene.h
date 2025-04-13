#pragma once
#include <entt.hpp>
#include <glm/glm.hpp>

#include "../Time/TimeStep.h"


namespace Cubes {    

    class Entity;
    class SceneHierarchyPanel;

    class Scene {
    public:
        Scene();
        ~Scene();

        void Update(TimeStep deltaTime);

        Entity CreateEmptyEntity(const std::string& name = "");
        void RemoveEntity(Entity entity);

        void OnViewportResize(uint32_t width, uint32_t height);

    private:
        void RenderScene();

    private:
        entt::registry _registry;
        uint32_t _viewportWidth = 0, _viewportHeight = 0;

        friend class Entity;
        friend class SceneHierarchyPanel;
    };

}
