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

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        _viewportWidth = width;
        _viewportHeight = height;

        auto view = _registry.view<CameraComponent>();
        for (auto entity : view) 
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            cameraComponent.Camera.SetViewportSize(width, height);
            
        }
    }

    void Scene::Update(TimeStep deltaTime)
    {   
        //Update scripts
        {
            _registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc) 
            {
                //TODO: Move to Scene::OnScenePlay()
                if (!nsc.Instance) {
                    nsc.Instance = nsc.InstantiateScript();
                    nsc.Instance->_entity = { this, entity };

                    nsc.Instance->OnCreate();
                }

                nsc.Instance->OnUpdate(deltaTime);

                //TODO: Call Delete funciton on play mode exit
            });
        }

        Entity cameraEntity;
        auto view = _registry.view<TransformComponent, CameraComponent>();
        for (auto [entity, transform, camera] : view.each()) {
            if (camera.Primary) {
                cameraEntity = { this, entity};
                break;
            }
        }
        auto& cameraTransform = cameraEntity.GetComponent<TransformComponent>().Transform;
        

        //TODO: SceneRenderer
        Renderer::BeginScene(Renderer::RenderCamera{ cameraEntity.GetComponent<CameraComponent>().Camera.GetProjection(), cameraTransform });
        RenderScene(); 
        Renderer::EndScene();
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
