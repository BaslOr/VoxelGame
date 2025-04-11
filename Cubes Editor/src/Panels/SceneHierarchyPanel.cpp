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
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags = (_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0;
        flags |= ImGuiTreeNodeFlags_OpenOnArrow;

        if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str())) {
            _selectedEntity = entity;

            ImGui::Text("%s", tag.c_str());

            ImGui::TreePop();
        }
    }

}
