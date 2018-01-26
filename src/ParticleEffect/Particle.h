#pragma once
#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_

#include "glm/glm.hpp"
#include "Entity/Entity.hpp"
class Particle {
    public:
        /* Attributes*/
        Entity particle;
        int type;
        int n;
        int total;
        float life;
        glm::vec3 origin;

        /* Constructors */
        Particle(int type, int n, int total, glm::vec3 origin, float duration);
        
        
        ~Particle();

        void Particle::update(float dt);
        void Particle::die();
        void Particle::updateMovement(float dt);
        glm::vec3 Particle::sphereMove();
};

#endif // !_PARTICLE_HPP_