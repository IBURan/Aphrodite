//
// Created by npchitman on 6/21/21.
//

#ifndef Aphrodite_ENGINE_TEXTURE_H
#define Aphrodite_ENGINE_TEXTURE_H

#include <string>

#include "Aphrodite/Core/Base.h"

namespace Aph {
    class Texture {
    public:
        virtual ~Texture() = default;
        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual intptr_t GetRendererID() const = 0;
        virtual std::string GetName() const = 0;

        virtual void SetData(void* data, uint32_t size) = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;

        virtual bool operator==(const Texture& other) const = 0;
    };

    class Texture2D : public Texture {
    public:
        static Ref<Texture2D> Create(uint32_t width, uint32_t height);
        static Ref<Texture2D> Create(const std::string& path);
    };

    class TextureCube : public Texture
    {
    public:
        static Ref<TextureCube> Create(const std::string& path);

        virtual uint32_t GetHDRRendererID() = 0;
        virtual uint32_t GetIrradianceRendererID() = 0;
    };
}// namespace Aph-Runtime


#endif//Aphrodite_ENGINE_TEXTURE_H
