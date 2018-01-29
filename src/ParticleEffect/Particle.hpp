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
        float life;
        glm::vec3 origin;

        /* Constructors */
        Particle(int type, int i, int total, glm::vec3 origin, float duration, Mesh *mesh, ModelTexture texture);

        void Particle::update(float dt);
        void Particle::die();
        void Particle::updateMovement();
        glm::vec3 Particle::sphereMove();
};

#endif // !_PARTICLE_HPP_