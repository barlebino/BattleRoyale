/* Entity Shader class derives Shader
 * Contains reference to a list of entities and entire rendering strategy */
#pragma once
#ifndef _PARTICLE_SHADER_HPP_
#define _PARTICLE_SHADER_HPP_

#include "Entity/Entity.hpp"
#include "Entity/EntityShader/EntityShader.hpp"
#include "ParticleEffect/ParticleEffect.hpp"
#include "Renderer/Shader.hpp"
#include "Light/Light.hpp"
#include "Model/Texture.hpp"

#include <vector>

class ParticleShader : public Shader {
    public:
        /* Define GLSL shader locations */
        ParticleShader() : Shader("../src/Entity/ParticleShader/particle_vertex_shader.glsl",
                                "../src/Entity/ParticleShader/particle_fragment_shader.glsl") { }
        
        /* Reference to render target */
        std::vector<ParticleEffect *> *particleEffectsPointer;
        
        /* Init render target and local shaders */
        bool init(std::vector<ParticleEffect *> *);

        /* Render */
        void render();

        /* Wrap up and shut down */
        void cleanUp();

    private:
        /* Mesh */
        void loadMesh(const Mesh *);
        void unloadMesh(const Mesh *);
        
        /* Texture */
        void loadTexture(const ModelTexture &);
        void unloadTexture(const ModelTexture &);

        /* GLSL Load functions */
        void addAllLocations();
        void loadM(const glm::mat4 *);
        void loadMaterial(const float, const glm::vec3, const glm::vec3);
        void loadShine(const float);
        void loadUsesTexture(const bool);
        void loadTexture(const Texture *);
};

#endif
