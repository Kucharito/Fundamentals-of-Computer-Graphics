#version 330 core

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vc;
layout(location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec2 uvc;

void main() {
    gl_Position = projectionMatrix* viewMatrix* modelMatrix * vec4(vp, 1.0);
    uvc = uv;
}