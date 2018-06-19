#pragma once
#include <cassert>

// INCOMPLETE
// TODO: http://gameprogrammingpatterns.com/data-locality.html#packed-data

class Particle
{
public:
    void update() { /* Gravity, etc. ... */ }
    // Position, velocity, etc. ...
};

class ParticleSystem
{
public:
    ParticleSystem()
        : m_numParticles(0)
    {}

    void update(void);
    void activateParticle(int index);
    void deactivateParticle(int index);
private:
    static const int MAX_PARTICLES = 10000; // set for each ParticleSystem instance?

    unsigned int m_numParticles;
    unsigned int m_numActive;
    Particle m_particles[MAX_PARTICLES];    // sorted by active state
};

void ParticleSystem::update(void)
{
    for (int i = 0; i < m_numActive; i++)
    {
        m_particles[i].update();
    }
}

void ParticleSystem::activateParticle(int index)
{
    // Shouldn't already be active!
    assert(index >= m_numActive);

    // Swap it with the first inactive particle
    // right after the active ones.
    Particle temp = m_particles[m_numActive];
    m_particles[m_numActive] = m_particles[index];
    m_particles[index] = temp;

    // Now there's one more.
    m_numActive++;
}

void ParticleSystem::deactivateParticle(int index)
{
    // Shouldn't already be inactive!
    assert(index < m_numActive);

    // There's one fewer.
    m_numActive--;

    // Swap it with the last active particle
    // right before the inactive ones.
    Particle temp = m_particles[m_numActive];
    m_particles[m_numActive] = m_particles[index];
    m_particles[index] = temp;
}
