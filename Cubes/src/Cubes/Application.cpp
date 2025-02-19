#include "cbpch.h"
#include "Application.h"
#include "Renderer/Renderer.h"


namespace Cubes {

    Application* Application::_instance = nullptr;


    Application::Application()
    {
        if (_instance != nullptr)
            CB_CORE_ERROR("Application already exists");
        _instance = this;

        Cubes::Log::init();
        _window = std::unique_ptr<Window>(Window::Create());
        _window->SetEventCallback(CB_BIND_EVENT_FUNC(Application::OnEvent));
        _camera = PerspectiveCamera(_cameraPosition, (float)_window->GetWidth() / (float)_window->GetHeight(), 45.f);
        std::cout << _window->GetWidth() << " " << _window->GetHeight() << std::endl;

        //Temporary: ---------------------------------------------------------------------
        float vertices[3 * 4] = {
            -0.5f,  0.5f, 0.f, //up, left   
             0.5f,  0.5f, 0.f, //up, right
             0.5f, -0.5f, 0.f, //down, right
            -0.5f, -0.5f, 0.f  //down, left
        };

        uint16_t indices[3 * 2] = {
            0, 1, 2, 2, 3, 0
        };

        std::string vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "\n"
            "uniform mat4 u_ViewProjection;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   gl_Position = u_ViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        std::string fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

        _vertexArray.reset(VertexArray::Create());

        _vertexBuffer.reset(VertexBuffer::Create(&vertices, sizeof(vertices)));

        {
            BufferLayout layout = {
               { ShaderDataType::Float3, "aPos"}
            };

            _vertexBuffer->SetLayout(layout);
        }

        _indexBuffer.reset(IndexBuffer::Create(indices, 6));

        _vertexArray->AddVertexBuffer(_vertexBuffer);
        _vertexArray->SetIndexBuffer(_indexBuffer);

        _shader.reset(Shader::Create(vertexShaderSource, fragmentShaderSource));
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(CB_BIND_EVENT_FUNC(Application::OnWindowClose));

        for (auto it = _layerStack.end(); it != _layerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.IsHandled())
                break;
        }

        _camera.OnEvent(event);
    }

    void Application::PushLayer(Layer* layer)
    {
        _layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        _layerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }


    void Application::run()
    {
        float rotation = 0;
        while (_isRunning) {
            //Update
            _window->OnUpdate();

            for (Layer* layer : _layerStack)
                layer->OnUpdate();

            if (Input::IsKeyDown(CB_KEY_W))
                _cameraPosition.z -= .1f;
            else if (Input::IsKeyDown(CB_KEY_S))
                _cameraPosition.z += .1f;
            if (Input::IsKeyDown(CB_KEY_D))
                _cameraPosition.x += .1f;
            else if (Input::IsKeyDown(CB_KEY_A))
                _cameraPosition.x -= .1f;

            if (Input::IsKeyDown(CB_KEY_SPACE))
                _cameraPosition.y += .1f;
            else if (Input::IsKeyDown(CB_KEY_LEFT_SHIFT))
                _cameraPosition.y -= .1f;
            //Render

            RendererCommand::SetClearColor(glm::vec4(.23f, .3f, .5f, 1.f));
            RendererCommand::Clear();

            _camera.SetPosition(_cameraPosition);

            Renderer::BeginScene(_camera);
            _shader->Bind();
            Renderer::Submit(_shader, _vertexArray);
            Renderer::EndScene();
        }
    }


    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        _isRunning = false;
        return true;
    }

}
