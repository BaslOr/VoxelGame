#include "cbpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

#include "../Renderer/Renderer.h"
#include "../Renderer/Renderer2D.h"
#include "entt.hpp"

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

    void Scene::Update(TimeStep deltaTime)
    {
        RenderScene();
    }

    void Scene::RenderScene()
    {
        //Indirect Filtering between 2D and 3D rendering calls
        {
            auto view = _registry.view<TransformComponent, SpriteRendererComponent>();
            for (auto [entity, transform, sprite] : view.each())
            {
                auto& [transform, sprite] = view.get<TransformComponent, SpriteRendererComponent>(entity);
                Renderer2D::DrawTexture(sprite.Sprite, transform.Transform, sprite.Color);
            }
        }
        
        
        {
            auto view = _registry.view<TransformComponent, MeshRendererComponent>();

            for (auto [entity, transform, mesh] : view.each()) {
                auto& [transform, mesh] = view.get<TransformComponent, MeshRendererComponent>(entity);

                Renderer::DrawModel(mesh.Mesh, transform.Transform, mesh.Color);
            }
        }
    }

}
