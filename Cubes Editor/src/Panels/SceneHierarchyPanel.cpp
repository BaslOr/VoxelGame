#include "SceneHierarchyPanel.h"
#include <Cubes/Core/Project/Components.h>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Cubes {

    SceneHierarchyPanel::SceneHierarchyPanel(Scene* context)
        : _context(context) {

    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");
        _context->_registry.view<TagComponent>().each([&](entt::entity nativeEntity, TagComponent tc) {
            Entity entity(_context, nativeEntity);

            DrawEntityNode(entity);
        });

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            _selectedEntity = {};

        ImGuiPopupFlags flags = ImGuiPopupFlags_NoOpenOverItems | 1;
        if (ImGui::BeginPopupContextWindow(0, flags)) {
            if (ImGui::MenuItem("Create Empty Entity"))
                _context->CreateEmptyEntity("Empty Entity");

            ImGui::EndPopup();
        }

        ImGui::End();

        ImGui::Begin("Inspector");

        DrawComponents();

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = (_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0;
        flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow;


        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
            
        if (ImGui::IsItemClicked(0)) {
            _selectedEntity = entity;
        }

        bool entityDeleted = false;
        if (ImGui::BeginPopupContextItem(0, 1)) {
            if (ImGui::MenuItem("Delete Entity"))
                entityDeleted = true;

            ImGui::EndPopup();
        }

        if (opened) {
            ImGui::Text("%s", tag.c_str());
            ImGui::TreePop();
        }

        if (entityDeleted) {
            _context->RemoveEntity(entity);
            if (_selectedEntity == entity) {
                _selectedEntity = {};
            }
        }
    }

    void SceneHierarchyPanel::DrawComponents()
    {
        if (!_selectedEntity)
            return;


        if (_selectedEntity.HasComponent<TagComponent>()) {
            auto& entityTag = _selectedEntity.GetComponent<TagComponent>().Tag;
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, entityTag.c_str());


            if (ImGui::InputText("Name", buffer, sizeof(buffer))) {
                entityTag = std::string(buffer);
            }
        }

        if (_selectedEntity.HasComponent<TransformComponent>()) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx("Transform", flags);

            if (opened) {
                glm::mat4& transform = _selectedEntity.GetComponent<TransformComponent>().Transform;
                ImGui::DragFloat3("Position: ", glm::value_ptr(transform[3]), 0.1f);

                ImGui::TreePop();
            }
        }

        if (_selectedEntity.HasComponent<CameraComponent>()) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx("Camera", flags);

            if (opened) {
                auto& cameraComponent = _selectedEntity.GetComponent<CameraComponent>();
                auto& camera = cameraComponent.Camera;

                const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
                const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];

                if (ImGui::BeginCombo("Projection Type", currentProjectionTypeString)) {

                    for (int i = 0; i < 2; i++) {
                        bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                        if (ImGui::Selectable(projectionTypeStrings[i], isSelected)) {
                            currentProjectionTypeString = projectionTypeStrings[i];
                            camera.SetProjectionType((SceneCamera::ProjectionType)i);
                        }

                        if (isSelected)
                            ImGui::SetItemDefaultFocus();
                    }

                    ImGui::EndCombo();
                }

                if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective) {
                    float fov = camera.GetPerspectiveFov();
                    if (ImGui::DragFloat("FOV", &fov, 0.5f)) {
                        camera.SetPerspectiveFov(fov);
                    }

                    float farClip = camera.GetPerspectiveFar();
                    if (ImGui::DragFloat("Far Clip", &farClip, 1.f)) {
                        camera.SetPerspectiveFar(farClip);
                    }

                    float nearClip = camera.GetPerspectiveNear();
                    if (ImGui::DragFloat("Near Clip", &nearClip, 1.f)) {
                        camera.SetPerspectiveFar(nearClip);
                    }

                } else if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {
                    float size = camera.GetOrthographicSize();
                    if (ImGui::DragFloat("Size", &size, 0.5f)) {
                        camera.SetOrthographicSize(size);
                    }

                    float farClip = camera.GetOrthographicFar();
                    if (ImGui::DragFloat("Far Clip", &farClip, 1.f)) {
                        camera.SetOrthographicFar(farClip);
                    }

                    float nearClip = camera.GetOrthographicNear();
                    if (ImGui::DragFloat("Near Clip", &nearClip, 1.f)) {
                        camera.SetOrthographicFar(nearClip);
                    }
                }

                ImGui::TreePop();
            }
        }

        if (_selectedEntity.HasComponent<SpriteRendererComponent>()) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx("Sprite Renderer", flags);

            if (opened) {
                //TODO: Add query for material
                auto& spriteRendererComponent = _selectedEntity.GetComponent<SpriteRendererComponent>();
                ImGui::ColorEdit4("Color", glm::value_ptr(spriteRendererComponent.Color));

                ImGui::TreePop();
            }
        }

        if (_selectedEntity.HasComponent<MeshRendererComponent>()) {
            ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
            bool opened = ImGui::TreeNodeEx("Mesh Renderer", flags);

            if (opened) {
                //TODO: Add query for material
                auto& meshRendererComponent = _selectedEntity.GetComponent<MeshRendererComponent>();
                ImGui::ColorEdit4("Color", glm::value_ptr(meshRendererComponent.Color));

                ImGui::TreePop();
            }
        }
    }

}
