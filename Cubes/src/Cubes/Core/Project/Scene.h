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

        template<typename T>
        void OnComponentAdded(Entity entity, T& component);

    private:
        entt::registry _registry;
        uint32_t _viewportWidth = 100, _viewportHeight = 100;

        friend class Entity;
        friend class SceneHierarchyPanel;
    };

}
