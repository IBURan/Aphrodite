//
// Created by npchitman on 6/28/21.
//

#include "SceneSerializer.h"

#include <yaml-cpp/yaml.h>

#include <fstream>

#include "Components.h"
#include "Entity.h"
#include "pch.h"

namespace YAML {
    template<>
    struct convert<glm::vec2>
    {
        static Node encode(const glm::vec2& rhs)
        {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            return node;
        }

        static bool decode(const Node& node, glm::vec2& rhs)
        {
            if (!node.IsSequence() || node.size() != 2)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };

    template<>
    struct convert<glm::vec3> {
        static Node encode(const glm::vec3& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::vec3& rhs) {
            if (!node.IsSequence() || node.size() != 3)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            return true;
        }
    };

    template<>
    struct convert<glm::vec4> {
        static Node encode(const glm::vec4& rhs) {
            Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.push_back(rhs.z);
            node.push_back(rhs.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& node, glm::vec4& rhs) {
            if (!node.IsSequence() || node.size() != 4)
                return false;

            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            rhs.z = node[2].as<float>();
            rhs.w = node[3].as<float>();
            return true;
        }
    };
}// namespace YAML

namespace Aph {

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
        return out;
    }

    static void SerializeEntity(YAML::Emitter& out, Entity entity) {
        out << YAML::BeginMap;                                          // Entity
        out << YAML::Key << "Entity" << YAML::Value << "12837192831273";// TODO: Entity ID goes here

        if (entity.HasComponent<TagComponent>()) {
            out << YAML::Key << "TagComponent";
            out << YAML::BeginMap;// TagComponent

            auto& tag = entity.GetComponent<TagComponent>().Tag;
            out << YAML::Key << "Tag" << YAML::Value << tag;

            out << YAML::EndMap;// TagComponent
        }

        if (entity.HasComponent<TransformComponent>()) {
            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap;// TransformComponent

            auto& tc = entity.GetComponent<TransformComponent>();
            out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
            out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
            out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

            out << YAML::EndMap;// TransformComponent
        }

        if (entity.HasComponent<CameraComponent>()) {
            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap;// CameraComponent

            auto& cameraComponent = entity.GetComponent<CameraComponent>();
            auto& camera = cameraComponent.Camera;

            out << YAML::Key << "Camera" << YAML::Value;
            out << YAML::BeginMap;// Camera
            out << YAML::Key << "ProjectionType" << YAML::Value << (int) camera.GetProjectionType();
            out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
            out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
            out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
            out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
            out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
            out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
            out << YAML::EndMap;// Camera

            out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
            out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;

            out << YAML::EndMap;// CameraComponent
        }

        if (entity.HasComponent<SpriteRendererComponent>()) {
            out << YAML::Key << "SpriteRendererComponent";
            out << YAML::BeginMap;// SpriteRendererComponent

            auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();
            out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;
            out << YAML::Key << "TextureFilepath" << YAML::Value << spriteRendererComponent.TextureFilepath;
            out << YAML::Key << "TilingFactor" << YAML::Value << spriteRendererComponent.TilingFactor;

            out << YAML::EndMap;// SpriteRendererComponent
        }

        if (entity.HasComponent<Rigidbody2DComponent>())
        {
            out << YAML::Key << "Rigidbody2DComponent";
            out << YAML::BeginMap; // Rigidbody2DComponent

            auto& rigidbody2DComponent = entity.GetComponent<Rigidbody2DComponent>();
            out << YAML::Key << "Type" << YAML::Value << (int)rigidbody2DComponent.Specification.Type;
            out << YAML::Key << "LinearDamping" << YAML::Value << rigidbody2DComponent.Specification.LinearDamping;
            out << YAML::Key << "AngularDamping" << YAML::Value << rigidbody2DComponent.Specification.AngularDamping;
            out << YAML::Key << "GravityScale" << YAML::Value << rigidbody2DComponent.Specification.GravityScale;
            out << YAML::Key << "CollisionDetection" << YAML::Value << (int)rigidbody2DComponent.Specification.CollisionDetection;
            out << YAML::Key << "SleepingMode" << YAML::Value << (int)rigidbody2DComponent.Specification.SleepingMode;
            out << YAML::Key << "FreezeRotationZ" << YAML::Value << rigidbody2DComponent.Specification.FreezeRotationZ;

            out << YAML::EndMap; // Rigidbody2DComponent
        }

        if (entity.HasComponent<BoxCollider2DComponent>())
        {
            out << YAML::Key << "BoxCollider2DComponent";
            out << YAML::BeginMap; // BoxCollider2DComponent

            auto& boxCollider2DComponent = entity.GetComponent<BoxCollider2DComponent>();
            out << YAML::Key << "Size" << YAML::Value << boxCollider2DComponent.Size;
            out << YAML::Key << "Offset" << YAML::Value << boxCollider2DComponent.Offset;
            out << YAML::Key << "IsTrigger" << YAML::Value << boxCollider2DComponent.IsTrigger;

            out << YAML::EndMap; // BoxCollider2DComponent
        }

        out << YAML::EndMap;// Entity
    }

    SceneSerializer::SceneSerializer(const Ref<Scene>& scene) : m_Scene(scene) {
    }


    void SceneSerializer::Serialize(const std::string& filepath) {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << "Untitled";
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        m_Scene->m_Registry.each([&](auto entityID) {
            Entity entity = {entityID, m_Scene.get()};
            if (!entity)
                return;

            SerializeEntity(out, entity);
        });
        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fOut(filepath);
        fOut << out.c_str();
    }

    void SceneSerializer::SerializeRuntime(const std::string& filepath) {
        APH_CORE_ASSERT(false);
    }

    bool SceneSerializer::Deserialize(const std::string& filepath) {
        YAML::Node data = YAML::LoadFile(filepath);
        if (!data["Scene"])
            return false;

        auto sceneName = data["Scene"].as<std::string>();
        APH_CORE_TRACE("Deserializing scene '{0}'", sceneName);

        auto entities = data["Entities"];
        if (entities) {
            for (auto entity : entities) {
                auto uuid = entity["Entity"].as<uint64_t>();// TODO

                std::string name;
                auto tagComponent = entity["TagComponent"];
                if (tagComponent)
                    name = tagComponent["Tag"].as<std::string>();

                APH_CORE_TRACE("Deserialized entity with ID = {0}, name = {1}", uuid, name);

                Entity deserializedEntity = m_Scene->CreateEntity(name);

                auto transformComponent = entity["TransformComponent"];
                if (transformComponent) {
                    // Entities always have transforms
                    auto& tc = deserializedEntity.GetComponent<TransformComponent>();
                    tc.Translation = transformComponent["Translation"].as<glm::vec3>();
                    tc.Rotation = transformComponent["Rotation"].as<glm::vec3>();
                    tc.Scale = transformComponent["Scale"].as<glm::vec3>();
                }

                auto cameraComponent = entity["CameraComponent"];
                if (cameraComponent) {
                    auto& cc = deserializedEntity.AddComponent<CameraComponent>();

                    const auto& cameraProps = cameraComponent["Camera"];
                    cc.Camera.SetProjectionType((SceneCamera::ProjectionType) cameraProps["ProjectionType"].as<int>());

                    cc.Camera.SetPerspectiveVerticalFOV(cameraProps["PerspectiveFOV"].as<float>());
                    cc.Camera.SetPerspectiveNearClip(cameraProps["PerspectiveNear"].as<float>());
                    cc.Camera.SetPerspectiveFarClip(cameraProps["PerspectiveFar"].as<float>());

                    cc.Camera.SetOrthographicSize(cameraProps["OrthographicSize"].as<float>());
                    cc.Camera.SetOrthographicNearClip(cameraProps["OrthographicNear"].as<float>());
                    cc.Camera.SetOrthographicFarClip(cameraProps["OrthographicFar"].as<float>());

                    cc.Primary = cameraComponent["Primary"].as<bool>();
                    cc.FixedAspectRatio = cameraComponent["FixedAspectRatio"].as<bool>();
                }

                auto spriteRendererComponent = entity["SpriteRendererComponent"];
                if (spriteRendererComponent) {
                    auto& src = deserializedEntity.AddComponent<SpriteRendererComponent>();
                    src.Color = spriteRendererComponent["Color"].as<glm::vec4>();
                    auto textureFilepath = spriteRendererComponent["TextureFilepath"].as<std::string>();
                    if(!textureFilepath.empty())
                        src.SetTexture(textureFilepath);
                    src.TilingFactor = spriteRendererComponent["TilingFactor"].as<float>();
                }

                auto rigidbody2DComponent = entity["Rigidbody2DComponent"];
                if (rigidbody2DComponent)
                {
                    auto& src = deserializedEntity.AddComponent<Rigidbody2DComponent>();
                    src.Specification.Type = (Rigidbody2DType)rigidbody2DComponent["Type"].as<int>();
                    src.Specification.LinearDamping = rigidbody2DComponent["LinearDamping"].as<float>();
                    src.Specification.AngularDamping = rigidbody2DComponent["AngularDamping"].as<float>();
                    src.Specification.GravityScale = rigidbody2DComponent["GravityScale"].as<float>();
                    src.Specification.CollisionDetection = (Rigidbody2D::CollisionDetectionType)rigidbody2DComponent["CollisionDetection"].as<int>();
                    src.Specification.SleepingMode = (Rigidbody2D::SleepType)rigidbody2DComponent["SleepingMode"].as<int>();
                    src.Specification.FreezeRotationZ = rigidbody2DComponent["FreezeRotationZ"].as<bool>();
                }

                auto boxCollider2DComponent = entity["BoxCollider2DComponent"];
                if (boxCollider2DComponent)
                {
                    auto& src = deserializedEntity.AddComponent<BoxCollider2DComponent>();
                    src.Size = boxCollider2DComponent["Size"].as<glm::vec2>();
                    src.Offset = boxCollider2DComponent["Offset"].as<glm::vec2>();
                    src.IsTrigger = boxCollider2DComponent["IsTrigger"].as<bool>();
                }
            }
        }

        return true;
    }

    bool SceneSerializer::DeserializeRuntime(const std::string& filepath) {
        // Not implemented
        APH_CORE_ASSERT(false);
        return false;
    }
}// namespace Aph
