#version 330 core

layout(location = 0) in vec4 vertexPos;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexTexture;
layout(location = 3) in vec4 particleOffset;

uniform mat4 P;
uniform mat4 M;
uniform mat4 V;
uniform vec3 cameraPos;
uniform float timeData;
uniform int total;
uniform vec3 origin;

out vec4 worldPos;
out vec3 fragNormal;
out vec3 viewDir;
out vec2 textureCoords;

vec4 sphereMove(int i, int n, float t){
	float phi = 1.6180339887f;
	float pi = 3.14159265359f;
	float z = 1 - (float(2 * i) / float(n - 1));
	float radius = sqrt(1 - z * z);
	float theta = 2 * pi * (2 - phi) * i;
	float default_speed = 10.f;
	vec3 position = origin + (default_speed * t) * vec3(radius * cos(theta), radius * sin(theta), z);

	return vec4(position, 1);
}

void main() {
	//vec4 offset = sphereMove(gl_InstanceID, total, timeData);

    worldPos = M * vertexPos + particleOffset;
    gl_Position = P * V * worldPos; //+ vec4(gl_InstanceID, 0 , 0, 1);

    viewDir = cameraPos - worldPos.xyz;
    fragNormal = vec3(M * vec4(vertexNormal, 0.0));
    textureCoords = vertexTexture;
}
