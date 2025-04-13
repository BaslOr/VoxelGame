#pragma once
#include "Scene.h"
#include "../Core.h"

#include <entt.hpp>
#include <optional>

namespace Cubes {

    class Entity {
    public:
        Entity() = default;
        Entity(Scene* scene, entt::entity handle);

        template<typename T, typename ...Args>
        inline T& AddComponent(Args && ...args)
        {
            CB_CORE_ASSERT_FALSE(HasComponent<T>(), "Tried to add an allready existing component");

            return _scene->_registry.emplace<T>(_entityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        void RemoveComponent() 
        {
            if (HasComponent<T>()) {
                CB_CORE_LOG_WARN("Tried to remove not existing component");
                return;
            }

            return _scene->_registry.remove<T>(_entityHandle);
        }

        template<typename T>
        T& GetComponent()
        {
            CB_CORE_ASSERT_FALSE(!HasComponent<T>(), "Tried to access a non-exsiting component");

            return _scene->_registry.get<T>(_entityHandle);
        }

        template<typename T>
        bool HasComponent()
        {
            return _scene->_registry.all_of<T>(_entityHandle);
        }

        bool operator ==(Entity other) {
            return (_scene == other._scene) && (_entityHandle == other._entityHandle) ? true : false;
        }

        operator entt::entity() {
            return _entityHandle;
        }

        operator uint32_t() {
            return static_cast<uint32_t>(_entityHandle);
        }

        operator bool() {
            return _scene != nullptr && _entityHandle != entt::null;
        }

    private:
        Scene* _scene = nullptr; //TODO: Should be std::weak_ptr or sth
        entt::entity _entityHandle = entt::null;
    };



}
