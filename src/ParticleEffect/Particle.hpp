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
        int i;
        int total;
        glm::vec3 origin;

        /* Constructors */
        Particle(int type, int i, int total, glm::vec3 origin);

        void Particle::update(float tData);
        void Particle::die();
        void Particle::updateMovement(float tData);
        glm::vec3 Particle::sphereMove(float tData);
        glm::vec3 Particle::sphereExplode(float tData);
};

#endif // !_PARTICLE_HPP_