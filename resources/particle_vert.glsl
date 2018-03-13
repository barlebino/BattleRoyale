#version 330 core

const int randCount = 10;
layout(location = 0) in vec3 vertPos;
layout(location = 1) in vec3 vertNor;
layout(location = 2) in vec2 vertTex;
layout(location = 3) in vec3 particleOffset;

uniform mat4 P;
uniform mat4 M;
uniform mat4 randomMs[randCount];
uniform mat4 V;
uniform mat3 N;
uniform vec3 cameraPos;

out vec3 worldPos;
out vec3 fragNor;
out vec2 texCoords;

void main() {
    worldPos = vec3(randomMs[gl_InstanceID % randCount] * vec4(vertPos, 1.0f)) + particleOffset;
	fragNor = N * vertNor;
	texCoords = vertTex;

    gl_Position = P * V * vec4(worldPos, 1.0f);    
}
