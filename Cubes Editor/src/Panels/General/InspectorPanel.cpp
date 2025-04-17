#include "InspectorPanel.h"
#include "../../Utility/ImGuiTemplates.h"
#include <Cubes/Core/Project/Components.h>

#include <imgui.h>

namespace Cubes {

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
        if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight })) {
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

	InspectorPanel::InspectorPanel()
		: Panel("Inspector")
	{
	}

	void InspectorPanel::OnImGuiRender()
	{
		DrawComponents();
	}

    void InspectorPanel::DrawComponents()
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

            ImGuiTemplates::DrawVec3Control("Position", component.Position);
            glm::vec3 rotation = glm::degrees(component.Rotation);
            ImGuiTemplates::DrawVec3Control("Rotation", rotation);
            ImGuiTemplates::DrawVec3Control("Scale", component.Scale, 1.0f);
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

    void InspectorPanel::DrawAddComponentButton()
    {
        ImGui::PushItemWidth(-1);

        if (_selectedEntity) {
            if (ImGui::Button("Add Component"))
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

