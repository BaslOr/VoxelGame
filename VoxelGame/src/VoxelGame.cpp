#include "VoxelGame.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


namespace GameNamespace {

	VoxelGame::VoxelGame()
		: _camera(glm::vec3(0.f, 0.f, 3.f), 45.f)
	{
		PushOverlay(new Cubes::ImGUILayer());

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
            "uniform mat4 u_Model;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   gl_Position = u_ViewProjection * u_Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        std::string fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\n\0";

        _vertexArray.reset(Cubes::VertexArray::Create());

        _vertexBuffer.reset(Cubes::VertexBuffer::Create(&vertices, sizeof(vertices)));

        {
            Cubes::BufferLayout layout = {
               { Cubes::ShaderDataType::Float3, "aPos"}
            };

            _vertexBuffer->SetLayout(layout);
        }

        _indexBuffer.reset(Cubes::IndexBuffer::Create(indices, 6));

        _vertexArray->AddVertexBuffer(_vertexBuffer);
        _vertexArray->SetIndexBuffer(_indexBuffer);

        _shader.reset(Cubes::Shader::Create(vertexShaderSource, fragmentShaderSource));
	}

	void VoxelGame::OnUpdate(Cubes::TimeStep deltaTime)
	{
        //Update
        _camera.OnUpdate(deltaTime);

        //Render
        Cubes::RendererCommand::SetClearColor(glm::vec4(.23f, .3f, .5f, 1.f));
        Cubes::RendererCommand::Clear();

        glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(2.f, 0.f, 0.f));

        Cubes::Renderer::BeginScene(_camera);
        _shader->Bind();
        Cubes::Renderer::Submit(_shader, _vertexArray, model);
        Cubes::Renderer::EndScene();
	}

}
