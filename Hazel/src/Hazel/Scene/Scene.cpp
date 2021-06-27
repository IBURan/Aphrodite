//
// Created by npchitman on 6/26/21.
//

#include "Scene.h"

#include <glm/glm.hpp>

#include "Components.h"
#include "Entity.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "hzpch.h"

namespace Hazel {

    static void DoMath(const glm::mat4& transform) {
    }

    static void OnTransformConstruct(entt::registry& registry, entt::entity entity) {
    }

    Scene::Scene() {// NOLINT(modernize-use-equals-default)
#if ENTT_EXAMPLE_CODE
        auto entity = m_Registry.create();
        m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
        m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

        if (m_Registry.has<TransformComponent>(entity))
            TransformComponent& transform = m_Registry.get<TransformComponent>(entity);

        auto view = m_Registry.view<TransformComponent>();

        for (auto e : view) {
            auto& transform = view.get<TransformComponent>(entity);
        }

        auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
        for (auto e : group) {
            auto& [transform, mesh] = group.get<TranformComponent, MeshComponent>(entity);
        }
#endif
    }

    Scene::~Scene() = default;

    Entity Scene::CreateEntity(const std::string& name) {
        Entity entity = {m_Registry.create(), this};
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Entity" : name;
        return entity;
    }

    void Scene::OnUpdate(Timestep ts) {
        Camera* mainCamera = nullptr;
        glm::mat4* cameraTransform = nullptr;
        {
            auto group = m_Registry.view<TransformComponent, CameraComponent>();
            for (auto entity : group) {
                const auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);

                if (camera.Primary) {
                    mainCamera = &camera.Camera;
                    cameraTransform = &transform.Transform;
                    break;
                }
            }
        }

        if (mainCamera) {
            Renderer2D::BeginScene(static_cast<const Camera>(mainCamera->GetProjection()), *cameraTransform);

            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group) {
                const auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

                Renderer2D::DrawQuad(static_cast<const glm::mat4>(transform), sprite.Color);
            }
            Renderer2D::EndScene();
        }
    }
}// namespace Hazel