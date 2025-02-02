#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPosition;  
uniform vec3 lightColor;      
uniform vec3 objectColor;     

out vec4 FragColor;

void main() {
    vec3 ambient = 0.1 * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(-FragPos);  
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);  
    vec3 specular = 0.5 * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
