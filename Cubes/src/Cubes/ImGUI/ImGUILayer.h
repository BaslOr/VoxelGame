#pragma once
#include "../Core/Layer.h"
#include "../Core/Events/ApplicationEvent.h"
#include "../Core/Events/MouseEvent.h"
#include "../Core/Events/KeyEvent.h"
#include <imgui.h>

namespace Cubes {

    class CB_API ImGUILayer : public Layer
    {
    public:
        ImGUILayer();
        ~ImGUILayer();
        
        void OnAttach() override;
        void OnDetach() override;
        void OnImGuiRender() override;

        void Begin();
        void End();

        inline void SetImGuiFontScale(float scale);
        inline float GetImGuiFontScale() const { return _fontScale; }

        void SetDarkThemeColors(bool drawColorPicker = false);

    private:	
        void StartDockspace();
        void EndDockspace();

    private:
        float _time = 0.f;

        float _fontScale = 1.5;

        ImVec4 _headerColor = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
        ImVec4 _headerHoveredColor = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        ImVec4 _headerActiveColor = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);

        ImVec4 _buttonColor = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        ImVec4 _buttonHoveredColor = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
        ImVec4 _activeColor = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

        ImVec4 _frameBackgroundColor = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
        ImVec4 _frameBackgroundHovered = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

        ImVec4 _tagColor = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
        ImVec4 _tabHoveredColor = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
        ImVec4 _tabActiveColor = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
        ImVec4 _tabUnfocusedColor = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
        ImVec4 _tabUnfocusedActiveColor = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

        ImVec4 _titleBackground = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
        ImVec4 _titleBackgroundActive = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
        ImVec4 _titleBackgroundCollapsed = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    };

}
