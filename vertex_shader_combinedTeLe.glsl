#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 worldNormal;
out vec3 worldPosition;
out vec2 uvc;

void main() {
    worldNormal = transpose(inverse(mat3(modelMatrix))) * vn;

    vec4 position = modelMatrix * vec4(vp, 1.0);
    worldPosition = position.xyz / position.w;

    uvc = uv;

    gl_Position = projectionMatrix * viewMatrix * position;
}
