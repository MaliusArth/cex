#pragma once
#include "components/render_component.hpp"
#include "components/physics_component.hpp"
#include "components/ai_component.hpp"

namespace ma
{
    // this might be turned to a single hash id (representing the indices to the components)
    class GameEntity
    {
        AIComponent* m_aiComponents;
        PhysicsComponent* m_physicsComponents;
        RenderComponent* m_renderComponents;
    };
}
