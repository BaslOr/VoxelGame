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

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = (_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0;
        flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;


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
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, columbWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float fontScale = io.FontGlobalScale;
        float lineHeight = GImGui->Font->FontSize * fontScale + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight};
        
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("X", buttonSize))
            values.x = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Y", buttonSize))
            values.y = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushFont(boldFont);
        if (ImGui::Button("Z", buttonSize))
            values.z = resetValue;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }

    template<typename ComponentType, typename UIFunction>
    static void DrawComponent(const std::string& name, Entity entity, UIFunction uiFunction) 
    {
        if (!entity.HasComponent<ComponentType>())
            return;

        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_DefaultOpen |
            ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth
            | ImGuiTreeNodeFlags_FramePadding;
        auto& component = entity.GetComponent<ComponentType>(); 
        ImGuiIO& io = ImGui::GetIO();
        ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();


        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
        float lineHeight = GImGui->Font->FontSize * io.FontGlobalScale + GImGui->Style.FramePadding.y * 2.0f;
        ImGui::Separator();
        bool opened = ImGui::TreeNodeEx((void*)typeid(ComponentType).hash_code(), treeNodeFlags, name.c_str());
        ImGui::PopStyleVar();
        ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
        if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight})) {
            ImGui::OpenPopup("ComponentSettings");
        }

        bool removeComponent = false;
        if (ImGui::BeginPopup("ComponentSettings")) {
            if (ImGui::MenuItem("Remove Component"))
                removeComponent = true;

            ImGui::EndPopup();
        }

        if (opened) {
            uiFunction(component);
            ImGui::TreePop();
        }

        if (removeComponent)
            entity.RemoveComponent<ComponentType>();
    }


    void SceneHierarchyPanel::DrawComponents()
    {
        if (!_selectedEntity)
            return;

        if (_selectedEntity.HasComponent<TagComponent>()) {
            auto& entityTag = _selectedEntity.GetComponent<TagComponent>().Tag;
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), entityTag.c_str());


            if (ImGui::InputText("##Name", buffer, sizeof(buffer))) {
                entityTag = std::string(buffer);
            }
        }

        ImGui::SameLine();
        DrawAddComponentButton();



        DrawComponent<TransformComponent>("Transform", _selectedEntity, [](auto& component) {

            DrawVec3Control("Position", component.Position);
            glm::vec3 rotation = glm::degrees(component.Rotation);
            DrawVec3Control("Rotation", rotation);
            DrawVec3Control("Scale", component.Scale, 1.0f);
        });
        DrawComponent<CameraComponent>("Camera", _selectedEntity, [](auto& component) {

            auto& camera = component.Camera;

            ImGui::Checkbox("Primary", &component.Primary);

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

            }
            else if (camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic) {
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
        });
        DrawComponent<SpriteRendererComponent>("Sprite Renderer", _selectedEntity, [](auto& component)
        {
            //TODO: Add query for sprite
            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
        });
        DrawComponent<MeshRendererComponent>("Mesh Renderer", _selectedEntity, [](auto& component) {
            //TODO: Add query for mesh
            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
        });
    }

    void SceneHierarchyPanel::DrawAddComponentButton()
    {
        ImGui::PushItemWidth(-1);

        if (_selectedEntity) {
            if (ImGui::ButtonEx("Add Component"))
                ImGui::OpenPopup("AddComponent");

            if (ImGui::BeginPopup("AddComponent")) {
                if (ImGui::MenuItem("Camera Component ")) {
                    _selectedEntity.AddComponent<CameraComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("Sprite Renderer Component")) {
                    _selectedEntity.AddComponent<SpriteRendererComponent>();
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::MenuItem("Mesh Renderer Component")) {
                    _selectedEntity.AddComponent<MeshRendererComponent>();
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }
    }

}
