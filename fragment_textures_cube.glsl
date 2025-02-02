#version 450


in vec3 fragmentLocalPosition;


uniform samplerCube textureUnitID;
uniform vec3 viewPosition;

out vec4 frag_colour;



void main () {
	 
    frag_colour = texture(textureUnitID, fragmentLocalPosition);
}