#include "cbpch.h"
#include "Application.h"
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGLShader.h"


namespace Cubes {

    Application* Application::_instance = nullptr;

    //TODO: Abstract the function out
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) { 
        switch (type)
        {
        case Cubes::ShaderDataType::Float:     return GL_FLOAT;
        case Cubes::ShaderDataType::Float2:    return GL_FLOAT;
        case Cubes::ShaderDataType::Float3:    return GL_FLOAT;
        case Cubes::ShaderDataType::Float4:    return GL_FLOAT;
        case Cubes::ShaderDataType::Mat3:      return GL_FLOAT;
        case Cubes::ShaderDataType::Mat4:      return GL_FLOAT;
        case Cubes::ShaderDataType::Int:       return GL_INT;
        case Cubes::ShaderDataType::Int2:      return GL_INT;
        case Cubes::ShaderDataType::Int3:      return GL_INT;
        case Cubes::ShaderDataType::Int4:      return GL_INT;
        case Cubes::ShaderDataType::Bool:      return GL_BOOL;
        }

        CB_CORE_ASSERT(false, "Unkown Shader Data type!");
        return 0;
    }

    Application::Application()
    {
        if (_instance != nullptr)
            CB_CORE_ERROR("Application already exists");
        _instance = this;

        Cubes::Log::init();
        _window = std::unique_ptr<Window>(Window::Create());
        _window->SetEventCallback(CB_BIND_EVENT_FUNC(Application::OnEvent));
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(CB_BIND_EVENT_FUNC(Application::OnWindowClose));

        for (auto it = _layerStack.end(); it != _layerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.IsHandled())
                break;
        }
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
        while (_isRunning) {
            //Update
            _window->OnUpdate();

            for (Layer* layer : _layerStack)
                layer->OnUpdate();

            //Render
            glClearColor(.23f, .3f, .5f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);

            //Temporary: ---------------------------------------------------------------------
            float vertices[3 * 3] = {
                0.f, 0.5f, 0.f,
                0.5f, -0.5f, 0.f,
                -0.5f, -0.5f, 0.f
            };

            uint16_t indices[3] = {
                0, 1, 2
            };

            std::string vertexShaderSource = "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;\n"
                "void main()\n"
                "{\n"
                "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                "}\0";
            std::string fragmentShaderSource = "#version 330 core\n"
                "out vec4 FragColor;\n"
                "void main()\n"
                "{\n"
                "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                "}\n\0";

            uint32_t VAO, VBO, IBO;
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            _vertexBuffer.reset(VertexBuffer::Create(&vertices, sizeof(vertices)));
 
            {
                BufferLayout layout = {
                   { ShaderDataType::Float3, "aPos"}
                };

                _vertexBuffer->SetLayout(layout);
            }

            uint32_t index = 0;
            const auto& layout = _vertexBuffer->GetLayout();
            for (const auto& element : layout) {
                glEnableVertexAttribArray(index);
                glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
                ++index;
            }

            _indexBuffer.reset(IndexBuffer::Create(indices, 3));
             
            _shader.reset(Shader::Create(vertexShaderSource, fragmentShaderSource));
            _shader->Bind();

            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }


    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        _isRunning = false;
        return true;
    }

}
