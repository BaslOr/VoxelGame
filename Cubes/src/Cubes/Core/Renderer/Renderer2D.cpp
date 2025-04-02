#include "cbpch.h"
#include "Renderer2D.h"

#include "../Core.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "MeshFactory.h"


namespace Cubes {

    struct Renderer2DData {
        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<IndexBuffer> QuadIndexBuffer;

        Ref<Texture> DefaultTexture;
    };

    static Renderer2DData renderer2DData;


    void Renderer2D::Init()
    {
        InitQuadData();

        renderer2DData.DefaultTexture = Texture::Create("../Cubes/resources/textures/DefaultTexture.png");
    }

    void Renderer2D::Shutdown()
    {

    }

    void Renderer2D::BeginScene()
    {

    }

    void Renderer2D::EndScene()
    {

    }




    void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        Ref<Shader> shader = ShaderLibrary::Get("DefaultShader");
        shader->Bind();
        shader->SetUniformMat4("u_Model", transform);
        shader->SetUniformFloat4("u_Color", color);
        shader->SetUniformInt("u_Sampler", 0);

        renderer2DData.QuadVertexArray->Bind();
        renderer2DData.DefaultTexture->Bind();
        RenderCommand::DrawIndexed(renderer2DData.QuadVertexArray);
    }

    void Renderer2D::DrawQuad(glm::vec3& position, glm::vec2& size, glm::vec4& color, float rotation)
    {
        glm::mat4 transform = ApplyTransformations(position, size, rotation);

        DrawQuad(transform, color);
    }

    void Renderer2D::DrawTexture(Ref<Texture> texture, const glm::mat4& transform, const glm::vec4& color)
    {
        //Bind
        renderer2DData.QuadVertexArray->Bind();
        texture->Bind();

        //Set Uniforms
        Ref<Shader> shader = ShaderLibrary::Get("DefaultShader");
        shader->Bind();
        shader->SetUniformMat4("u_Model", transform);
        shader->SetUniformFloat4("u_Color", color);
        shader->SetUniformInt("u_Sampler", 0);

        RenderCommand::DrawIndexed(renderer2DData.QuadVertexArray);
    }

    void Renderer2D::DrawTexture(Ref<Texture> texture, glm::vec3& position, glm::vec2& size, glm::vec4& color, float rotation)
    {
        glm::mat4 model = ApplyTransformations(position, size, rotation);

        Ref<Shader> shader = ShaderLibrary::Get("DefaultShader");
        shader->Bind();
        shader->SetUniformMat4("u_Model", model);
        shader->SetUniformFloat4("u_Color", color);
        shader->SetUniformInt("u_Sampler", 0);

        renderer2DData.QuadVertexArray->Bind();
        texture->Bind();
        RenderCommand::DrawIndexed(renderer2DData.QuadVertexArray);
    }



    void Cubes::Renderer2D::InitQuadData()
    {
        auto quadVertices = MeshFactory::GetQuadVertices();
        auto quadIndices = MeshFactory::GetQuadIndices();

        renderer2DData.QuadVertexArray = VertexArray::Create();
        renderer2DData.QuadVertexBuffer = VertexBuffer::Create(quadVertices.data(), quadVertices.size() * sizeof(Vertex));
        {
            Cubes::BufferLayout layout = {
               { Cubes::ShaderDataType::Float3, "aPos"},
               { Cubes::ShaderDataType::Float2, "aTexCoord" }
            };

            renderer2DData.QuadVertexBuffer->SetLayout(layout);
        }
        renderer2DData.QuadIndexBuffer = IndexBuffer::Create(quadIndices.data(), quadIndices.size());

        renderer2DData.QuadVertexArray->AddVertexBuffer(renderer2DData.QuadVertexBuffer);
        renderer2DData.QuadVertexArray->SetIndexBuffer(renderer2DData.QuadIndexBuffer);
    }

    glm::mat4 Renderer2D::ApplyTransformations(const glm::vec3 position, const glm::vec2 size, float rotation)
    {
        return glm::translate(glm::mat4(1.f), position) *
            glm::rotate(glm::mat4(1.f), glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f)) *
            glm::scale(glm::mat4(1.f), glm::vec3(size, 0.f));
    }

}