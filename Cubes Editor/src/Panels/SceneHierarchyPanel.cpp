#include "SceneHierarchyPanel.h"
#include <Cubes/Core/Project/Components.h>

#include <imgui.h>

namespace Cubes {

    SceneHierarchyPanel::SceneHierarchyPanel(Scene* context)
        : _context(context) {

    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
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

        if (entityDeleted)
            _context->DestroyEntity(entity);
    }

}
