#pragma once
#include "Core.h"
#include "Utility/Log.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Input.h"
#include "Renderer/Shader.h"
#include "Time/Timestep.h"

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/PerspectiveCamera.h"

#include "../ImGUI/ImGUILayer.h"



namespace Cubes {


    class CB_API Application {
    public:
        Application();
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

        std::unique_ptr<Window> _window;
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