#include "ParticleEffect.h"
#include <GLFW/glfw3.h>

ParticleEffect::ParticleEffect(int type, int total, glm::vec3 position, float duration) {
    type = type;
    total = total;
    position = position;
    particles = generateParticles();
    // NEED TO ADD TO RENDER LIST
    duration = duration;
    life = 0;
    toDie = false;
    t = glfwGetTime();
}

std::vector<Particle *> ParticleEffect::generateParticles() {
    std::vector<Particle *> vp = std::vector<Particle *>();
    for (int i = 0; i < total; i++) {
        Particle p = Particle(type, i, total, position, duration);
        vp.push_back(&p);
        
    }
    return vp;
}

void ParticleEffect::update() {
    double dt = glfwGetTime() - t;
    t += dt;
    life += dt;
    if (life < duration) {
        for (int i = 0; i < total; i++) {
            particles.at(i)->update(dt);
        }
    }
    else {
        toDie = true;
    }
}

void ParticleEffect::die() {
    // Just die
    for (int i = 0; i < total; i++) {
        particles.at(i)->die();
    }
}
