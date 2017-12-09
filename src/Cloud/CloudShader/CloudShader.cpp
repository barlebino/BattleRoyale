#include "CloudShader.hpp"

bool CloudShader::init() {
    if (!Shader::init()) {
        return false;
    }

    /* Attributes */
    addAttribute("vertexPos");

    /* Projection and view */
    addUniform("P");
    addUniform("V");
    addUniform("M");
    addUniform("cameraPosition");

    /* Cloud things */
    addUniform("center");
    addUniform("size");

    /* Texture */
    addUniform("textureImage");

    return true;
}

void CloudShader::loadP(const glm::mat4 *p) {
    this->loadMat4(getUniform("P"), p);
}

void CloudShader::loadV(const glm::mat4 *v) {
    this->loadMat4(getUniform("V"), v);
}

void CloudShader::loadCameraPosition(const glm::vec3 c) {
    this->loadVec3(getUniform("cameraPosition"), c);
}

void CloudShader::loadM(const glm::mat4 *m) {
    this->loadMat4(getUniform("M"), m);
}

void CloudShader::loadCenter(const glm::vec3 c) {
    this->loadVec3(getUniform("center"), c);
}

void CloudShader::loadSize(const glm::vec2 s) {
    this->loadVec2(getUniform("size"), s);
}

void CloudShader::loadTexture(const Texture *texture) {
    this->loadInt(getUniform("textureImage"), texture->textureId);
}