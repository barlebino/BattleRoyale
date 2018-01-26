#pragma once
#ifndef _PARTICLEEFFECT_HPP_
#define _PARTICLEEFFECT_HPP_

#include "glm/glm.hpp"
#include "Entity/Entity.hpp"
#include "Particle.h"
#include <vector>

class ParticleEffect {
    public:
        /* Attributes*/
        int type;
        int total;
        glm::vec3 position;
        float duration;
        float life;
        double t;
        bool toDie;
        std::vector<Particle *> particles;

        /* Constructors */
        ParticleEffect(int type, int n, glm::vec3 position, float duration);

        std::vector<Particle *> ParticleEffect::generateParticles();

        void ParticleEffect::die();
        void ParticleEffect::update();
};

#endif // !_PARTICLEEFFECT_HPP_
