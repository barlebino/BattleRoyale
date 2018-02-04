#include "Particle.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>

Particle::Particle(int type, int i, int total, glm::vec3 origin, Mesh *mesh, ModelTexture texture) :
    particle(mesh, texture, origin, glm::vec3(0.f), glm::vec3(1.f)),
    type(type),
    i(i),
    total(total),
    origin(origin)
{
    int a = 1;
}

void Particle::update(float tData) {
 
    updateMovement(tData);
}

void Particle::die() {
    // Just Die
}

void Particle::updateMovement(float tData) {
    if (type == 0) {
        particle.position = sphereMove(tData);
    }
}

glm::vec3 Particle::sphereMove(float tData) {
    double phi = glm::golden_ratio<float>();
    //float z = (1 - 1 / float(total)) * (1 - 2 * float(i) / float(total - 1));
    float z = 1 - (2 * float(i) / float(total - 1));
    float radius = sqrt(1 - z * z);
    float theta = 2 * 3.14f * (2 - phi) * float(i);
    //int planeCount = int(sqrt(total));
    float default_speed = 10.f;
    //double pi = 3.1415926535897;
    //float theta = ((2 * pi) / planeCount) * (n / planeCount);
    //float phi = ((pi / (planeCount)) * (n % planeCount));
    //printf("n: %d\nTheta: %f\nPhi: %f\n", i, theta, phi);
    return origin + (default_speed * tData) * glm::vec3(radius * cos(theta), radius * sin(theta), z);
}

