#include "cbpch.h"
#include <imgui.h>
#include "ImGUILayer.h"
#include "../Application.h"

//Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cubes {

    ImGUILayer::ImGUILayer()
        : Layer("ImGUILayer")
    {
    }

    ImGUILayer::~ImGUILayer()
    {
    }

    void ImGUILayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.FontGlobalScale = 1.5f;

        // TEMPORARY: should eventually use CUBES key codes
        io.KeyMap[ImGuiKey_Tab] = CB_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = CB_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = CB_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = CB_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = CB_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = CB_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = CB_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = CB_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = CB_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = CB_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = CB_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = CB_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = CB_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = CB_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = CB_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = CB_KEY_A;
        io.KeyMap[ImGuiKey_C] = CB_KEY_C;
        io.KeyMap[ImGuiKey_V] = CB_KEY_V;
        io.KeyMap[ImGuiKey_X] = CB_KEY_X;
        io.KeyMap[ImGuiKey_Y] = CB_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = CB_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 440");
    }

    void ImGUILayer::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseButtonPressedEvent>(CB_BIND_EVENT_FUNC(ImGUILayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(CB_BIND_EVENT_FUNC(ImGUILayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(CB_BIND_EVENT_FUNC(ImGUILayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(CB_BIND_EVENT_FUNC(ImGUILayer::OnMouseScrollEvent));
        dispatcher.Dispatch<WindowResizeEvent>(CB_BIND_EVENT_FUNC(ImGUILayer::OnWindowResizeEvent));
        //dispatcher.Dispatch<KeyTypedEvent>(CB_BIND_EVENT_FUNC(ImGUILayer::OnKeyTypedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(CB_BIND_EVENT_FUNC(ImGUILayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyPressedEvent>(CB_BIND_EVENT_FUNC(ImGUILayer::OnKeyPressedEvent));
    }

    void ImGUILayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        float time = (float)glfwGetTime();
        io.DeltaTime = _time > 0.0 ? (time - _time) : (1.f / 60.f);
        _time = time;

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    bool ImGUILayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool ImGUILayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGUILayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool ImGUILayer::OnMouseScrollEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();

        return false;
    }

    bool ImGUILayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());

        return false;
    }

    bool ImGUILayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();
        if (keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter(static_cast<unsigned short>(keycode));

        return false;
    }

    bool ImGUILayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true; //TODO: Use Cubes Key Code

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGUILayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;

        return false;
    }

}
