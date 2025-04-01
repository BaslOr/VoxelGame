#include "cbpch.h"
#include "Scene.h"

#include "Entity.h"
#include "Components.h"

namespace Cubes {

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { this, _registry.create() };
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;

        return entity;
    }

    void Scene::OnUpdate()
    {
    }

}
