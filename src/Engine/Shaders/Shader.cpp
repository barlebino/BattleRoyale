#include "Shader.hpp"
#include "GLSL.hpp"

#include <fstream>
#include <iostream>

bool Shader::init() {
    GLint rc;

    std::ifstream v(vShaderName.c_str());
    std::ifstream f(fShaderName.c_str());
    if (!v.good() || !f.good()) {
        std::cerr << "Shader(s) don't exist" << std::endl;
        std::cerr << "\t" << vShaderName << std::endl;
        std::cerr << "\t" << fShaderName << std::endl;
        return false;
    }


    vShaderId = GLSL::createShader(vShaderName, GL_VERTEX_SHADER);
    if (vShaderId < 0) {
        return false;
    }

    fShaderId = GLSL::createShader(fShaderName, GL_FRAGMENT_SHADER);
    if (fShaderId < 0) {
        return false;
    }

    pid = glCreateProgram();
    glAttachShader(pid, vShaderId);
    glAttachShader(pid, fShaderId);
    glLinkProgram(pid);
    glGetProgramiv(pid, GL_LINK_STATUS, &rc);
    if (!rc) {
        GLSL::printProgramInfoLog(pid);
        std::cerr << "Error linking shaders" << std::endl;
        return false;
    }

    GLSL::checkError(GET_FILE_LINE);
    return true;
}
void Shader::bind() {
    glUseProgram(pid);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::addAttribute(const std::string &name) {
    GLint r = glGetAttribLocation(pid, name.c_str());
    if (r < 0) {
        std::cerr << "WARN: " << name << " cannot be bound (it either doesn't exist or has been optimized away). safe_glAttrib calls will silently ignore it\n" << std::endl;
    }
    attributes[name] = r;
}

void Shader::addUniform(const std::string &name) {
    GLint r = glGetUniformLocation(pid, name.c_str());
    if (r < 0) {
        std::cerr << "WARN: " << name << " cannot be bound (it either doesn't exist or has been optimized away). safe_glAttrib calls will silently ignore it\n" << std::endl;
    }  
    uniforms[name] = r;
}

GLint Shader::getAttribute(const std::string &name) { 
    std::map<std::string, GLint>::const_iterator attribute = attributes.find(name.c_str());
    if (attribute == attributes.end()) {
        std::cerr << name << " is not an attribute variable" << std::endl;
        return -1;
    }
    return attribute->second;
}

GLint Shader::getUniform(const std::string &name) { 
    std::map<std::string, GLint>::const_iterator uniform = uniforms.find(name.c_str());
    if (uniform == uniforms.end()) {
        std::cerr << name << " is not an uniform variable" << std::endl;
        return -1;
    }
    return uniform->second;
}

void Shader::cleanUp() {
    unbind();
    glDetachShader(pid, vShaderId);
    glDetachShader(pid, fShaderId);
    glDeleteShader(vShaderId);
    glDeleteShader(fShaderId);
    glDeleteProgram(pid);
}

void Shader::unloadMesh() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Shader::unloadTexture(int texId) {
    glActiveTexture(GL_TEXTURE0 + texId);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Shader::loadBool(const int location, const bool b) const {
    glUniform1i(location, b);
}

void Shader::loadInt(const int location, const int i) const {
    glUniform1i(location, i);
}

void Shader::loadFloat(const int location, const float f) const { 
    glUniform1f(location, f);
}

void Shader::loadVec2(const int location, const glm::vec2 v) const { 
    glUniform2f(location, v.x, v.y);
}

void Shader::loadVec3(const int location, const glm::vec3 v) const { 
    glUniform3f(location, v.x, v.y, v.z);
}

void Shader::loadMat4(const int location, const glm::mat4 *m) const { 
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(*m));
}