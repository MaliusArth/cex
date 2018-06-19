#pragma once

#include "common/Exports.hpp"
#include "common/Config.hpp"
#include "templates/Singleton.hpp"
#include "components/AIComponent.hpp"
#include "components/PhysicsComponent.hpp"
#include "components/RenderComponent.hpp"


namespace ma
{
    class  MA_API Engine : public Singleton<Engine>
    {
        friend class Singleton<Engine>;

    public:
        bool Init(int argc, char **argv);
        bool SetBackend();
        void run(void);

    private:
        // in-memory data / settings
        static const unsigned int MAX_ENTITIES = 25;

        bool gameOver;
        unsigned int numEntities;   // number of instanced game entities

        AIComponent* m_aiComponents = new AIComponent[MAX_ENTITIES];
        PhysicsComponent* m_physicsComponents = new PhysicsComponent[MAX_ENTITIES];
        RenderComponent* m_renderComponents = new RenderComponent[MAX_ENTITIES];
    };
}

namespace ma
{
    inline void Engine::Run(void)
    {
        while (!gameOver)
        {
            // Process AI.
            for (int i = 0; i < numEntities; i++)
            {
                m_aiComponents[i].update();
            }

            // Update physics.
            for (int i = 0; i < numEntities; i++)
            {
                m_physicsComponents[i].update();
            }

            // Draw to screen.
            for (int i = 0; i < numEntities; i++)
            {
                m_renderComponents[i].render();
            }

            // Other game loop machinery for timing...
        }
    }
}
