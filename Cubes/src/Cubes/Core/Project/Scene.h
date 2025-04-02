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

    private:
        void RenderScene();

    private:
        friend class Entity;

        entt::registry _registry;
    };

}
