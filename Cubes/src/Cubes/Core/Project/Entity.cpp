#include "cbpch.h"
#include "Entity.h"

namespace Cubes {



    Entity::Entity(Scene* scene, entt::entity handle)
        : _scene(scene), _entityHandle(handle)
    {   }

}
