#include "TutorialWorld.hpp"
#include "glm/gtc/matrix_transform.hpp"

void TutorialWorld::init(Context &ctx, Loader &loader) {
    /* Set up light */
    this->light = new Light(glm::vec3(-1000, 1000, 1000), glm::vec3(1.f), glm::vec3(1.f, 0.0f, 0.0f));

    /* Set up camera */
    this->camera = new Camera;

    /* Entities */
    Mesh *mesh = loader.loadObjMesh("bunny.obj");
    ModelTexture modelTexture(0.3f,
                    glm::vec3(0.f, 0.f, 1.f),
                    glm::vec3(1.f));
    //NEW CODE
    int type = 0;
    int n = 500;
    int duration = 10.f;
    glm::vec3 position = glm::vec3(50.f, -5.f, -5.f);
    glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 scale = glm::vec3(1.f);
    Entity *pe = new Entity(mesh, modelTexture, position, rotation, scale);
    ParticleEffect *explosion = spawnParticleEffect(type, n, duration, pe);

    particleEffects.push_back(explosion);
    //entities.push_back(new Entity(mesh, modelTexture, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f), glm::vec3(3.f)));

    /* World-specific members */
    this->P = ctx.display.projectionMatrix;
    this->V = glm::lookAt(camera->position, camera->lookAt, glm::vec3(0, 1, 0));
}


ParticleEffect* TutorialWorld::spawnParticleEffect(int type, int n, float duration, Entity *pe) {
    
    ParticleEffect *test = new ParticleEffect(type, n, duration, pe);
    particleEffects.push_back(test);
    for (int i = 0; i < n; i++) {
        Entity *e = &test->particles[i].particle;

        entities.push_back(e);
    }

    return test;
}

void TutorialWorld::prepareRenderer(MasterRenderer *mr) {
    //mr->activateEntityShader(&entities);
    mr->activateParticleShader(&particleEffects);
}

void TutorialWorld::prepareUniforms() {
    UniformData *PData = new UniformData{ UniformType::Mat4, "P", (void *)&P };
    UniformData *VData = new UniformData{ UniformType::Mat4, "V", (void *)&V };
    UniformData *cameraPos = new UniformData{ UniformType::Vec3, "cameraPos", (void *)&camera->position };
    UniformData *lightPos = new UniformData{ UniformType::Vec3, "lightPos", (void *)&light->position };
    UniformData *lightCol = new UniformData{ UniformType::Vec3, "lightCol", (void *)&light->color };
    UniformData *lightAtt = new UniformData{ UniformType::Vec3, "lightAtt", (void *)&light->attenuation };
    UniformData *timeData = new UniformData{ UniformType::Float, "timeData", (void *)&particleEffects[0]->tData };
    UniformData *total = new UniformData{ UniformType::SignedInt32, "total", (void *)&particleEffects[0]->total };
    UniformData *origin = new UniformData{ UniformType::Vec3, "origin", (void *)&particleEffects[0]->pe->position };


    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(PData);
    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(VData);
    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(cameraPos);
    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(lightPos);
    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(lightCol);
    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(lightAtt);
    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(timeData);
    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(total);
    uniforms[MasterRenderer::ShaderTypes::PARTICLE_SHADER].push_back(origin);


    uniforms[MasterRenderer::ShaderTypes::ENTITY_SHADER].push_back(PData);
    uniforms[MasterRenderer::ShaderTypes::ENTITY_SHADER].push_back(VData);
    uniforms[MasterRenderer::ShaderTypes::ENTITY_SHADER].push_back(cameraPos);
    uniforms[MasterRenderer::ShaderTypes::ENTITY_SHADER].push_back(lightPos);
    uniforms[MasterRenderer::ShaderTypes::ENTITY_SHADER].push_back(lightCol);
    uniforms[MasterRenderer::ShaderTypes::ENTITY_SHADER].push_back(lightAtt);
}

void TutorialWorld::update(Context &ctx) {
    this->P = ctx.display.projectionMatrix;
    this->V = glm::lookAt(camera->position, camera->lookAt, glm::vec3(0, 1, 0));
    takeInput(ctx.mouse, ctx.keyboard);
    camera->update();
  
    /* update Particles*/
    for (auto pe : particleEffects) {
        pe->update();
    }

    /* Update entities */
    for (auto e : entities) {
        //e->update();
        //e->rotation.y += 15.f * ctx.timeStep;
    }

    
}

void TutorialWorld::takeInput(Mouse &mouse, Keyboard &keyboard) {
    if (keyboard.isKeyPressed(' ')) {
        isPaused = !isPaused;
    }

    if (mouse.isButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        camera->takeMouseInput(mouse.dx, mouse.dy);
    }
    else {
        camera->takeMouseInput(0.f, 0.f);
    }
    if (keyboard.isKeyPressed('w')) {
        camera->moveForward();
    }
    if (keyboard.isKeyPressed('a')) {
        camera->moveLeft();
    }
    if (keyboard.isKeyPressed('s')) {
        camera->moveBackward();
    }
    if (keyboard.isKeyPressed('d')) {
        camera->moveRight();
    }
    if (keyboard.isKeyPressed('e')) {
        camera->moveDown();
    }
    if (keyboard.isKeyPressed('r')) {
        camera->moveUp();
    }
}

void TutorialWorld::cleanUp() {
    
}

