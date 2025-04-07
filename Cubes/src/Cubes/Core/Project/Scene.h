#pragma once
#include <entt.hpp>
#include <glm/glm.hpp>

#include "../Time/TimeStep.h"


namespace Cubes {    

    class Entity;

    class Scene {
    public:
        Scene();
        ~Scene();

        void Update(TimeStep deltaTime);

        Entity CreateEntity(const std::string& name = "");

        void OnViewportResize(uint32_t width, uint32_t height);

    private:
        void RenderScene();

    private:
        entt::registry _registry;
        uint32_t _viewportWidth = 0, _viewportHeight = 0;

        friend class Entity;
    };

}
