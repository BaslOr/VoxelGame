#include "SceneHierarchyPanel.h"
#include <Cubes/Core/Project/Components.h>

#include <imgui.h>
#include <imgui_internal.h>
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

        if (_selectedEntity) {
            if (ImGui::Button("Add Component"))
                ImGui::OpenPopup("AddComponent");

            if (ImGui::BeginPopup("AddComponent")) {
                if (ImGui::MenuItem("Camera")) {
                    _selectedEntity.AddComponent<CameraComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("SpriteRenderer")) {
                    _selectedEntity.AddComponent<SpriteRendererComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("MeshRenderer")) {
                    _selectedEntity.AddComponent<MeshRendererComponent>();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }

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
    
    static void DrawVec3Control(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columbWidth = 100.0f) 
    {
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columbWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float lineHeight = GImGui->Font->Scale * GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight + 3.0f};
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    void SceneHierarchyPanel::DrawComponents()
    {
        if (!_selectedEntity)
            return;

        const ImGuiTreeNodeFlags treenNodeFlags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;

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
                auto& transformComponent = _selectedEntity.GetComponent<TransformComponent>();
                DrawVec3Control("Position", transformComponent.Position);
                glm::vec3 rotation = glm::degrees(transformComponent.Rotation);
                DrawVec3Control("Rotation", rotation);
                DrawVec3Control("Scale", transformComponent.Scale, 1.0f);

                ImGui::TreePop();
            }
        }

        if (_selectedEntity.HasComponent<CameraComponent>()) {
            bool opened = ImGui::TreeNodeEx("Camera", treenNodeFlags);

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
            bool opened = ImGui::TreeNodeEx("Sprite Renderer", treenNodeFlags);

            ImGui::SameLine();
            if (ImGui::Button("+")) {
                ImGui::OpenPopup("ComponentSettings");
            }

            bool removeComponent = false;
            if (ImGui::BeginPopup("ComponentSettings")) {
                if (ImGui::MenuItem("Remove Component"))
                    removeComponent = true;

                ImGui::EndPopup();
            }

            if (opened) {
                //TODO: Add query for material
                auto& spriteRendererComponent = _selectedEntity.GetComponent<SpriteRendererComponent>();
                ImGui::ColorEdit4("Color", glm::value_ptr(spriteRendererComponent.Color));
                
                ImGui::TreePop();
            }

            if (removeComponent)
                _selectedEntity.RemoveComponent<TransformComponent>();
        }

        if (_selectedEntity.HasComponent<MeshRendererComponent>()) {
            bool opened = ImGui::TreeNodeEx("Mesh Renderer", treenNodeFlags);

            if (opened) {
                //TODO: Add query for material
                auto& meshRendererComponent = _selectedEntity.GetComponent<MeshRendererComponent>();
                ImGui::ColorEdit4("Color", glm::value_ptr(meshRendererComponent.Color));

                ImGui::TreePop();
            }
        }
    }

}
