#include "VoxelGame.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


namespace GameNamespace {

	VoxelGame::VoxelGame()
		: _camera(glm::vec3(0.f, 0.f, 3.f), 45.f)
	{
		PushOverlay(new Cubes::ImGUILayer());

        //Temporary: ---------------------------------------------------------------------
        float vertices[5 * 4] = {
            //Positions           TexCoords
            -0.5f,  0.5f, 0.f,    0.f, 1.f, //up, left   
             0.5f,  0.5f, 0.f,    1.f, 1.f, //up, right
             0.5f, -0.5f, 0.f,    1.f, 0.f, //down, right
            -0.5f, -0.5f, 0.f,    0.f, 0.f  //down, left
        };

        uint16_t indices[3 * 2] = {
            0, 1, 2, 2, 3, 0
        };

        std::string vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "layout (location = 1) in vec2 aTexCoord;\n"
            "\n"
            "uniform mat4 u_ViewProjection;\n"
            "uniform mat4 u_Model;\n"
            "\n"
            "out vec2 TexCoord;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   gl_Position = u_ViewProjection * u_Model * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "   TexCoord = aTexCoord;\n"
            "}\0";
        std::string fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "\n"
            "uniform sampler2D u_Texture;\n"
            "\n"
            "in vec2 TexCoord;\n"
            "\n"
            "void main()\n"
            "{\n"
            "   FragColor = texture(u_Texture, TexCoord);\n"
            "}\n\0";



        _vertexArray = Cubes::VertexArray::Create();
        _vertexBuffer = Cubes::VertexBuffer::Create(&vertices, sizeof(vertices));
        {
            Cubes::BufferLayout layout = {
               { Cubes::ShaderDataType::Float3, "aPos"},
               { Cubes::ShaderDataType::Float2, "aTexCoord" }
            };

            _vertexBuffer->SetLayout(layout);
        }

        _indexBuffer = Cubes::IndexBuffer::Create(indices, 6);

        _vertexArray->AddVertexBuffer(_vertexBuffer);
        _vertexArray->SetIndexBuffer(_indexBuffer);

        _shader = Cubes::Shader::Create(vertexShaderSource, fragmentShaderSource);
        _shader->SetUnifromInt("u_Texture", 0);
        _texture = Cubes::Texture::Create("../VoxelGame/Assets/Textures/TestIcon.png");
        _text = Cubes::Texture::Create("../VoxelGame/Assets/Textures/OgerText.png");
	}

	void VoxelGame::OnUpdate(Cubes::TimeStep deltaTime)
	{
        //Update
        _camera.OnUpdate(deltaTime);

        //Render
        Cubes::RendererCommand::SetClearColor(glm::vec4(.23f, .3f, .5f, 1.f));
        Cubes::RendererCommand::Clear();

        Cubes::Renderer::BeginScene(_camera);
        _shader->Bind();
         _texture->Bind();
        Cubes::Renderer::Submit(_shader, _vertexArray);
        _text->Bind();
        Cubes::Renderer::Submit(_shader, _vertexArray);
        Cubes::Renderer::EndScene();
	}

}
