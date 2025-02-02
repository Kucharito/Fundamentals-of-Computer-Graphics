#version 330 core

in vec3 worldNormal;
in vec3 worldPosition;

uniform vec3 lightDirection;  
uniform vec3 lightColor;     
uniform vec3 viewPosition;  

out vec4 fragColor;

void main() {
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

    vec3 normal = normalize(worldNormal);
    vec3 lightDir = normalize(-lightDirection);
    vec3 viewDir = normalize(viewPosition - worldPosition);
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0); 
    vec3 specular = spec * lightColor;

    vec3 result = (diffuse + specular) * objectColor.rgb;
    fragColor = vec4(result, 1.0);
}
