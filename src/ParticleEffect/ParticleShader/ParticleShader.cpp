#include "ParticleShader.hpp"

#include "glm/gtc/matrix_transform.hpp" 

bool ParticleShader::init(std::vector<ParticleEffect*> *particleEffects) {
    /* Parent init */
    if (!particleEffects || !Shader::init()) {
        return false;
    }
    
    /* Set render target */
    this->particleEffectsPointer = particleEffects;

    /* Set enum type */
    this->type = MasterRenderer::ShaderTypes::PARTICLE_SHADER;

    addAllLocations();
        
    return true;
}

void ParticleShader::addAllLocations() {
    /* Add attributes */
    addAttribute("vertexPos");
    addAttribute("vertexNormal");
    addAttribute("vertexTexture");

    /* Add matrix transforms */
    addUniform("P");
    addUniform("M");
    addUniform("V");
    addUniform("cameraPos");

    /* Add texture info */
    addUniform("usesTexture");
    addUniform("textureImage");

    /* Add material properties */
    addUniform("matAmbient");
    addUniform("matDiffuse");
    addUniform("matSpecular");
    addUniform("shine");

    /* Add light */
    addUniform("lightPos");
    addUniform("lightCol");
    addUniform("lightAtt");
}

void ParticleShader::render() {
    /* Loop through every entity */
    // TODO : batched render
    glm::mat4 M;
    for (auto &p : *particleEffectsPointer) {
        /* If entity mesh doesn't contain geometry, skip it */
        if (!p->pe->mesh || !p->pe->mesh->vertBuf.size()) {
            continue;
        }

        /* Create and load model matrix */
        M = glm::translate(glm::mat4(1.f), p->pe->position);
        M *= glm::rotate(glm::mat4(1.f), glm::radians(p->pe->rotation.x), glm::vec3(1, 0, 0));
        M *= glm::rotate(glm::mat4(1.f), glm::radians(p->pe->rotation.y), glm::vec3(0, 1, 0));
        M *= glm::rotate(glm::mat4(1.f), glm::radians(p->pe->rotation.z), glm::vec3(0, 0, 1));
        M *= glm::scale(glm::mat4(1.f), p->pe->scale);
        loadM(&M);

        /* Load texture/material */
        loadTexture(p->pe->modelTexture);

        /* Load mesh */
        loadMesh(p->pe->mesh);

        /* Draw */
        glDrawElements(GL_TRIANGLES, (int)p->pe->mesh->eleBuf.size(), GL_UNSIGNED_INT, nullptr);

        /* EDITS */
        //int nParticles = 100;
        //glDrawElementsInstanced(GL_TRIANGLES, (int)e->mesh->eleBuf.size(), GL_UNSIGNED_INT, nullptr, nParticles);

        /* Unload mesh */
        unloadMesh(p->pe->mesh);

        /* Unload texture/material */
        unloadTexture(p->pe->modelTexture);
    }
}

/* Bind mesh attributes to VAO/VBOs 
 * All Meshes are assumed to have valid vertices and element indices 
 * Other attributes can be exlcluded */
void ParticleShader::loadMesh(const Mesh *mesh) {
    /* Bind mesh VAO */
    glBindVertexArray(mesh->vaoId);
    
    /* Bind vertex buffer VBO */
    int pos = getAttribute("vertexPos");
    glEnableVertexAttribArray(pos);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufId);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);

    /* Bind normal buffer VBO */
    pos = getAttribute("vertexNormal");
    if (pos != -1 && mesh->norBufId != 0) {
        glEnableVertexAttribArray(pos);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->norBufId);
        glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
    }

    /* Bind texture coordinate buffer VBO */
    pos = getAttribute("vertexTexture");
    if (pos != -1 && mesh->texBufId != 0) {
        glEnableVertexAttribArray(pos);
        glBindBuffer(GL_ARRAY_BUFFER, mesh->texBufId);
        glVertexAttribPointer(pos, 2, GL_FLOAT, GL_FALSE, 0, (const void *)0);
    }

    /* Bind indices buffer VBO */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->eleBufId);
}

/* Bind material properties and  texture if provided */
void ParticleShader::loadTexture(const ModelTexture &modelTexture) {
    /* Bind texture if it exists */
    if(modelTexture.texture && modelTexture.texture->textureId != 0) {
        loadUsesTexture(true);
        loadTexture(modelTexture.texture);
        glActiveTexture(GL_TEXTURE0 + modelTexture.texture->textureId);
        glBindTexture(GL_TEXTURE_2D, modelTexture.texture->textureId);
    }
    else {
        loadUsesTexture(false);
    }

    /* Bind materials */
    loadMaterial(modelTexture.ambientColor, 
                          modelTexture.diffuseColor, 
                          modelTexture.specularColor);
    loadShine(modelTexture.shineDamper);
}

/* Unbind mesh */
void ParticleShader::unloadMesh(const Mesh *mesh) {
    glDisableVertexAttribArray(getAttribute("vertexPos"));

    int pos = getAttribute("vertexNormal");
    if (pos != -1) {
        glDisableVertexAttribArray(pos);
    }

    pos = getAttribute("vertexTexture");
    if (pos != -1) {
        glDisableVertexAttribArray(pos);
    }

    Shader::unloadMesh();
}

/* Unbind model/texture*/
void ParticleShader::unloadTexture(const ModelTexture &modelTexture) {
    if (modelTexture.texture) {
        Shader::unloadTexture(modelTexture.texture->textureId);
    }
}

void ParticleShader::cleanUp() {
    Shader::cleanUp();
}

void ParticleShader::loadM(const glm::mat4 *m) {
    this->loadMat4(getUniform("M"), m);
}

void ParticleShader::loadMaterial(const float ambient, const glm::vec3 diffuse, const glm::vec3 specular) {
    this->loadFloat(getUniform("matAmbient"), ambient);
    this->loadVec3(getUniform("matDiffuse"), diffuse);
    this->loadVec3(getUniform("matSpecular"), specular);
}

void ParticleShader::loadShine(const float s) {
    this->loadFloat(getUniform("shine"), s);
}

void ParticleShader::loadUsesTexture(const bool b) {
    this->loadBool(getUniform("usesTexture"), b);
}

void ParticleShader::loadTexture(const Texture *texture) {
    this->loadInt(getUniform("textureImage"), texture->textureId);
}
