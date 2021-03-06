/* Renders scene's depth to an FBO from the POV of the light */
#pragma once
#ifndef _SHADOW_DEPTH_SHADER_HPP_
#define _SHADOW_DEPTH_SHADER_HPP_

#include "Shader.hpp"
#include "Model/Texture.hpp"

class Texture;

class ShadowDepthShader : public Shader {
    public:
        ShadowDepthShader(const String & vertName, const String & fragName);

        bool init();

        virtual void render(const CameraComponent * camera) override;
        
        Texture * getShadowMapTexture() { return s_shadowMap; }
        const glm::mat4 & getL() { return L; }
        int getMapSize() { return s_shadowMap->width; }
        void setMapSize(int);
    private:
        void initFBO();
        
        glm::mat4 L;
        GLuint s_fboHandle;
        Texture * s_shadowMap;

        GLuint s_particlesVAO;
        GLuint s_particlesVBO;
};

#endif