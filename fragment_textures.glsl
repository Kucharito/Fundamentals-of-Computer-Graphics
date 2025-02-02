#version 330 core

out vec4 frag_colour;

uniform sampler2D textureUnitID;
uniform vec3 viewPosition;

in vec2 uvc;

void main() {
    frag_colour = texture(textureUnitID, uvc);
}
