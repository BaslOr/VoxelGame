#include "cbpch.h"
#include "Renderer2D.h"

#include "../Core.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"


namespace Cubes {

    struct Renderer2DData {
        glm::mat4 ViewProjectionMatrix;

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<IndexBuffer> QuadIndexBuffer;

        ShaderLibrary ShaderLib;
    };

    static Renderer2DData* renderer2DData = new Renderer2DData;


	void Renderer2D::Init()
	{
        float quadVertices[5 * 4] = {
            //Positions           TexCoords
            -1.0f,  1.0f, 0.f,    0.f, 1.f, //up, left   
             1.0f,  1.0f, 0.f,    1.f, 1.f, //up, right
             1.0f, -1.0f, 0.f,    1.f, 0.f, //down, right
            -1.0f, -1.0f, 0.f,    0.f, 0.f  //down, left
        };

        uint16_t quadIndices[3 * 2] = {
            0, 1, 2, 2, 3, 0
        };

        renderer2DData->QuadVertexArray = VertexArray::Create();
        renderer2DData->QuadVertexBuffer = VertexBuffer::Create(&quadVertices, sizeof(quadVertices));
        {
            Cubes::BufferLayout layout = {
               { Cubes::ShaderDataType::Float3, "aPos"},
               { Cubes::ShaderDataType::Float2, "aTexCoord" }
            };

            renderer2DData->QuadVertexBuffer->SetLayout(layout);
        }

        renderer2DData->QuadIndexBuffer = IndexBuffer::Create(quadIndices, 6);

        renderer2DData->QuadVertexArray->AddVertexBuffer(renderer2DData->QuadVertexBuffer);
        renderer2DData->QuadVertexArray->SetIndexBuffer(renderer2DData->QuadIndexBuffer);

        renderer2DData->ShaderLib.Load("../Cubes/resources/defaultShader.glsl");
	}

    void Renderer2D::DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color, float rotation)
    {
        //Transform
        glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(position, 0.f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::scale(model, glm::vec3(size, 0.f));

        const auto& shader = renderer2DData->ShaderLib.Get("defaultShader");
        renderer2DData->QuadVertexArray->Bind();
        shader->SetUniformMat4("u_ViewProjection", renderer2DData->ViewProjectionMatrix);
        shader->SetUniformMat4("u_Model", model);
        shader->SetUniformFloat4("u_Color", color);
        RenderCommand::DrawIndexed(renderer2DData->QuadVertexArray);
    }

    void Renderer2D::Shutdown()
    {
        delete renderer2DData;
    }

    void Renderer2D::BeginScene(PerspectiveCamera& camera)
    {
        renderer2DData->ViewProjectionMatrix = camera.GetViewProjection();
    }

    void Renderer2D::EndScene()
    {

    }

}
