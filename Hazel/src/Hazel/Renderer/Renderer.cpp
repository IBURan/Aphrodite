//
// Created by npchitman on 6/1/21.
//

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "hzpch.h"

namespace Hazel {
    Renderer::SceneData *Renderer::s_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera &camera) {
        s_SceneData->ViewProjectionMatrix = camera.GetProjectionMatrix();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform) {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
                "u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(
                "u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}// namespace Hazel