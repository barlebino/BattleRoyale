#include "MasterRenderer.hpp"
#include "Renderer/GLSL.hpp"

#include "World/World.hpp"

#include "Entity/EntityShader/EntityShader.hpp"

/* Addition */
//#include "ParticleEffect/ParticleShader/ParticleShader.hpp"
#include "ParticleEffect/ParticleEffect.hpp"

#include <iostream>

/* Master render function */
void MasterRenderer::render(const World *world) {
    /* Reset rendering display */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    /* Loop through active subrenderers */
    for (auto &shader : shaders) {
        /* Bind subrenderer's shader */
        shader->bind();
        /* Load world-shader uniforms */
        bindWorldUniforms(world, shader);
        /* Subrenderer render */
        shader->render();
        /* Unbind subrenderer's shader */
        shader->unbind();
    }
}

void MasterRenderer::bindWorldUniforms(const World *world, Shader *shader) {
    auto uniforms = world->uniforms.find(shader->type);
    if (shader->type == ERROR || uniforms == world->uniforms.end()) {
        return;
    }
    for (auto uniformData : world->uniforms.at(shader->type)) {
        int pos = shader->getUniform(uniformData->location);
        if (!uniformData->dataptr || pos < 0) {
            continue;
        }
        switch (uniformData->type) {
            case(UniformType::Bool):
                shader->loadBool(pos, *(bool *) uniformData->dataptr);
                break;
            case(UniformType::SignedInt8):
                // TODO 
                break;
            case(UniformType::SignedInt16):
                // TODO
                break;
            case(UniformType::SignedInt32):
                // TODO 
                break;
            case(UniformType::UnsignedInt8):
                // TODO
                break;
            case(UniformType::UnsignedInt16):
                // TODO
                break;
            case(UniformType::UnsignedInt32):
                // TODO
                break;
            case(UniformType::Float):
                shader->loadFloat(pos, *(float *) uniformData->dataptr);
                break;
            case(UniformType::Vec2):
                shader->loadVec2(pos, *(glm::vec2 *)uniformData->dataptr);
                break;
            case(UniformType::Vec3):
                shader->loadVec3(pos, *(glm::vec3 *)uniformData->dataptr);
                break;
            case(UniformType::Vec4):
                // TODO
                break;
            case(UniformType::Mat3):
                // TODO
                break;
            case(UniformType::Mat4):
                shader->loadMat4(pos, (glm::mat4 *)uniformData->dataptr);
                break;
            default:
                break;
        }
    }
}

void MasterRenderer::init(const Context &ctx) {
    this->verbose = ctx.verbose;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MasterRenderer::activateEntityShader(std::vector<Entity *> *entities) {
    EntityShader *eShader = new EntityShader;
    if (eShader->init(entities)) {
        shaders.push_back(eShader);
        if (verbose) {
            std::cout << "Entity Shader activated" << std::endl;
        }
    }
    else {
        delete eShader;
        if (verbose) {
            std::cout << "Entity Shader failed to activate" << std::endl;
        }
    }
}

/*void MasterRenderer::activateParticleShader(std::vector<ParticleEffect *> *particleEffects) {
    ParticleShader *pShader = new ParticleShader;
    if (pShader->init(particleEffects)) {
        shaders.push_back(pShader);
        if (verbose) {
            std::cout << "Particle Shader activated" << std::endl;
        }
    }
    else {
        delete pShader;
        if (verbose) {
            std::cout << "Particle Shader failed to activate" << std::endl;
        }
    }
}*/

void MasterRenderer::cleanUp() {
    /* Clean up all active subrenderers */
    for (auto &shader : shaders) {
        shader->cleanUp();
    }
}

void MasterRenderer::toggleWireFrameMode() {
    wireFrame = !wireFrame;
    glPolygonMode(GL_FRONT_AND_BACK, wireFrame ? GL_LINE : GL_FILL);
}
