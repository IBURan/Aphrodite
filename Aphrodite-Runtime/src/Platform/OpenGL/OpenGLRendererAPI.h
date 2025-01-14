//
// Created by npchitman on 6/1/21.
//

#ifndef APHRODITE_ENGINE_OPENGLRENDERERAPI_H
#define APHRODITE_ENGINE_OPENGLRENDERERAPI_H

#include "Aphrodite/Renderer/RendererAPI.h"

namespace Aph {
    class OpenGLRendererAPI : public RendererAPI {
    public:
        void Init() override;
        void Clear() override;

        void DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0) override;
        void DrawArray(uint32_t first, uint32_t count) override;

        void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void SetClearColor(const glm::vec4 &color) override;
        void SetDepthMask(bool flag) override;
        void SetDepthTest(bool flag) override;
    };
}// namespace Aph-Runtime

#endif// APHRODITE_ENGINE_OPENGLRENDERERAPI_H
