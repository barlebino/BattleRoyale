#include "Particle.h"
#include <GLFW/glfw3.h>

Particle::Particle(int type, int n, int total, glm::vec3 origin, float duration) {
    type = type;
    n = n;
    total = total;
    origin = origin;
    life = 0;
    particle = Entity(origin, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));

}

~Particle();

void Particle::update(float dt) {
    life += dt;
    updateMovement(dt);
}

void Particle::die() {
    // Just Die
}

void Particle::updateMovement(float dt) {
    if (type == 0) {
        sphereMove();
    }
}

glm::vec3 Particle::sphereMove() {
    int planeCount = int(sqrt(total));
    float default_speed = 2;
    double pi = 3.1415926535897;
    float theta = (2 * pi / planeCount) * (n / planeCount);
    float phi = ((pi / (total / planeCount)) * (n % (total / planeCount))) - pi / 2;
    
    return origin + (default_speed * life) * glm::vec3(sin(phi) * cos(theta), sin(theta) * sin(theta), cos(phi));
}