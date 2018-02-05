#include "ParticleEffect.hpp"
#include <GLFW/glfw3.h>

ParticleEffect::ParticleEffect(int type, int total, float duration, Entity *pe) :
    type(type),
    total(total),
    duration(duration),
    pe(pe),
    life(0),
    toDie(false),
    particles(generateParticles()),
    tData(0.f),
    t(glfwGetTime())
{
    /* 
    type = type;
    total = total;
    position = position;
    particles = generateParticles();
    // NEED TO ADD TO RENDER LIST
    duration = duration;
    life = 0;
    toDie = false;
    t = glfwGetTime();
    */
}

std::vector<Particle> ParticleEffect::generateParticles() {
    std::vector<Particle> vp = std::vector<Particle>();
    for (int i = 0; i < total; i++) {
        //Particle p = Particle(type, i, total, position, duration);
        vp.emplace_back(type, i, total, pe->position);
        
    }
    return vp;
}

void ParticleEffect::update() {
    double dt = glfwGetTime() - t;
    t += dt;
    life += dt;
    tData = life / duration;
    if (life < duration && !toDie) {
        for (int i = 0; i < total; i++) {
            particles[i].update(tData);
        }
    }
    else {
        toDie = true;
    }
}

void ParticleEffect::die() {
    // Just die
    for (int i = 0; i < total; i++) {
        particles[i].die();
    }
}
