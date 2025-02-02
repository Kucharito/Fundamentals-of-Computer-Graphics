#version 450
layout(location = 0) in vec3 vp;


uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 fragmentLocalPosition;


void main () {
	 mat4 viewNoTranslation = mat4(mat3(viewMatrix)); 
	gl_Position = projectionMatrix * viewNoTranslation * vec4(vp, 1.0);
    fragmentLocalPosition = vp;
}
