#pragma once
#include "Entity.h"

namespace Cubes {

    class ScriptableEntity
    {
    public:
        ScriptableEntity() { }

        template<typename T>
        T& GetComponent()
        {
            return _entity.GetComponent<T>();
        }

    protected:
        virtual void OnCreate() { }
        virtual void OnDestroy() { }
        virtual void OnUpdate(TimeStep deltaTime) { }

    private:
        Entity _entity;
        friend class Scene;
    };

}