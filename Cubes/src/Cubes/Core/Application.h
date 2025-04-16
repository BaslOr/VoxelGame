#pragma once
#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Time/Timestep.h"
#include "Project/Scene.h"
#include "../ImGUI/ImGUILayer.h"
#include "Renderer/PerspectiveCamera.h"


namespace Cubes {


    class CB_API Application {
    public:
        Application(const std::string& name = "Cubes Program");
        virtual ~Application();
        
        void run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline static Application& Get() { return *_instance; }
        inline Window& GetWindow() { return *_window; }

        inline void Close() { _isRunning = false; }

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);

        void InitLogger();

    private:

        Scope<Window> _window;
        ImGUILayer* _ImGuiLayer;
        LayerStack _layerStack;

        glm::vec3 _cameraPosition = glm::vec3(0.f, 0.f, 3.f);
        PerspectiveCamera _camera;

        bool _isRunning = true;
        bool _minimized = false;
        float _lastFrameTime = 0.f;

    private:
        static Application* _instance;
    };

    //To be defined in Client
    Application* CreateApplication();

}