#include "cbpch.h"
#include "Renderer.h"

#include "Renderer2D.h"
#include "MeshFactory.h"

#include <glad/glad.h>

namespace Cubes {


    struct SceneData {
        glm::mat4 ViewProjectionMatrix;
    };

    struct RendererData {
        Ref<Framebuffer> Framebuffer;

        Ref<VertexArray> CubeVertexArray;
        Ref<VertexBuffer> CubeVertexBuffer;
        Ref<IndexBuffer> CubeIndexBuffer;

        Ref<Texture> DefaultTexture;
    };

    static SceneData sceneData;
    static RendererData rendererData;



    void Renderer::Init()
    {
        RenderCommand::Init();

        ShaderLibrary::Load("../Cubes/resources/shaders/DefaultShader.glsl");

        Renderer2D::Init();

        InitCubeData();
        rendererData.DefaultTexture = Texture::Create("../Cubes/resources/textures/DefaultTexture.png");
        FramebufferSpecification framebufferSpec{};
        framebufferSpec.Width = 1280;
        framebufferSpec.Height = 720;
        rendererData.Framebuffer = Framebuffer::Create(framebufferSpec);

    }

    void Renderer::ShutDown() 
    {
        Renderer2D::Shutdown();
    }

    void Renderer::OnWindowsResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    uint32_t Renderer::GetFramebufferColorAttachmentID()
    {
        return rendererData.Framebuffer->GetColorAttachmentID();
    }

    void Renderer::RecreateFramebuffer(const FramebufferSpecification& spec)
    {
        rendererData.Framebuffer->Invalidate(spec);
    }

    void Renderer::EnableWireframeMode(bool enable)
    {
        RenderCommand::EnableWireframeMode(enable);
    }

    void Renderer::BeginScene(PerspectiveCamera& camera)
    {
       rendererData.Framebuffer->Bind();

        Ref<Shader> defaultShader = ShaderLibrary::Get("DefaultShader");
        sceneData.ViewProjectionMatrix = camera.GetViewProjection();
        defaultShader->Bind();
        defaultShader->SetUniformMat4("u_ViewProjection", camera.GetViewProjection());

        Renderer2D::BeginScene();

        RenderCommand::SetClearColor(glm::vec4(.15f, .15f, .15f, 1.f));
        RenderCommand::Clear();
    }

    void Renderer::EndScene()
    {
        Renderer2D::EndScene();

        rendererData.Framebuffer->Unbind();
    }

    void Renderer::DrawModel(Ref<Model> model, const glm::mat4& transform, const glm::vec4 color)
    {
        Ref<VertexArray> VAO = VertexArray::Create();
        Ref<VertexBuffer> VBO = VertexBuffer::Create(model->Vertices.data(), sizeof(Vertex) * model->Vertices.size());
        Ref<IndexBuffer> IBO = IndexBuffer::Create(model->Indices.data(), model->Indices.size());
        {
            Cubes::BufferLayout layout = {
               { Cubes::ShaderDataType::Float3, "aPos"},
               { Cubes::ShaderDataType::Float2, "aTexCoord" }
            };

            VBO->SetLayout(layout);
        }

        VAO->AddVertexBuffer(VBO);
        VAO->SetIndexBuffer(IBO);

        //Bind
        model->Texture->Bind();
        auto shader = ShaderLibrary::Get("DefaultShader");
        shader->SetUniformFloat4("u_Color", color);
        shader->SetUniformMat4("u_Model", transform);
        shader->SetUniformInt("u_Sampler", 0);

        RenderCommand::DrawIndexed(VAO);
    }

    void Cubes::Renderer::DrawModel(Ref<Model> model, glm::vec3& position, glm::vec3& size, glm::vec4& color)
    {
        Ref<VertexArray> VAO = VertexArray::Create();
        Ref<VertexBuffer> VBO = VertexBuffer::Create(model->Vertices.data(), sizeof(Vertex) * model->Vertices.size());
        Ref<IndexBuffer> IBO = IndexBuffer::Create(model->Indices.data(), model->Indices.size());
        {
            Cubes::BufferLayout layout = {
               { Cubes::ShaderDataType::Float3, "aPos"},
               { Cubes::ShaderDataType::Float2, "aTexCoord" }
            };

            VBO->SetLayout(layout);
        }

        VAO->AddVertexBuffer(VBO);
        VAO->SetIndexBuffer(IBO);

        //Transform
        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.f), position);
        modelMatrix = glm::scale(modelMatrix, size);
        
        //Bind
        model->Texture->Bind();
        auto shader = ShaderLibrary::Get("DefaultShader");
        shader->SetUniformFloat4("u_Color", color); 
        shader->SetUniformMat4("u_Model", modelMatrix);
        shader->SetUniformInt("u_Sampler", 0);

        RenderCommand::DrawIndexed(VAO);
    }

    void Renderer::DrawCube(glm::vec3& position, glm::vec3& size, glm::vec4& color)
    {
        //Transform
        glm::mat4 model = glm::translate(glm::mat4(1.f), position);
        model = glm::scale(model, size);

        //Bind
        rendererData.DefaultTexture->Bind();
        auto shader = ShaderLibrary::Get("DefaultShader");
        shader->SetUniformFloat4("u_Color", color);

        Submit(shader, rendererData.CubeVertexArray, model);
    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& modelMatrix)
    {
        vertexArray->Bind();
        shader->SetUniformMat4("u_Model", modelMatrix);
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Cubes::Renderer::InitCubeData()
    {
        auto cubeVertices = MeshFactory::GetCubeVertices();
        auto cubeIndices = MeshFactory::GetCubeIndices();

        rendererData.CubeVertexArray = VertexArray::Create();
        rendererData.CubeVertexBuffer = VertexBuffer::Create(cubeVertices.data(), cubeVertices.size() * sizeof(Vertex));
        rendererData.CubeIndexBuffer = IndexBuffer::Create(cubeIndices.data(), cubeIndices.size());
        {
            Cubes::BufferLayout layout = {
               { Cubes::ShaderDataType::Float3, "aPos"},
               { Cubes::ShaderDataType::Float2, "aTexCoord" }
            };

            rendererData.CubeVertexBuffer->SetLayout(layout);
        }

        rendererData.CubeVertexArray->AddVertexBuffer(rendererData.CubeVertexBuffer);
        rendererData.CubeVertexArray->SetIndexBuffer(rendererData.CubeIndexBuffer);
    }

    
}