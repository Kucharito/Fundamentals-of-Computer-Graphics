#version 450

in vec3 fragmentLocalPosition;

uniform samplerCube textureUnitID;
uniform vec3 viewPosition;

out vec4 frag_colour;

void main() {
    vec4 color = texture(textureUnitID, fragmentLocalPosition);
    float brightnessFactor = 0.35; 
    frag_colour = color * brightnessFactor; 
}
