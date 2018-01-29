#pragma once
#ifndef _PARTICLEEFFECT_HPP_
#define _PARTICLEEFFECT_HPP_

#include "glm/glm.hpp"
#include "Entity/Entity.hpp"
#include "Particle.hpp"
#include "Model/Mesh.hpp"
#include "Model/ModelTexture.hpp"
#include <vector>

class ParticleEffect {
    public:

        /* Enum for particle effect */
        enum ParticleEffectTypes {
            SPHERE_LINEAR
        };
        
        /* Attributes*/
        int type;
        int total;
        float duration;
        Entity *pe;
        float life;
        bool toDie;
        std::vector<Particle> particles;

        double t;

        /* Constructors */
        ParticleEffect(int type, int n, float duration, Entity *pe);

        std::vector<Particle> ParticleEffect::generateParticles();

        void ParticleEffect::die();
        void ParticleEffect::update();
};

#endif // !_PARTICLEEFFECT_HPP_
