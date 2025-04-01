#pragma once
#include <entt.hpp>
#include <glm/glm.hpp>


namespace Cubes {    

    class Entity;

    class Scene {
    public:
        Scene();
        ~Scene();

        void OnUpdate();

        Entity CreateEntity(const std::string& name = "");

    private:
        friend class Entity;

        entt::registry _registry;
    };

}
