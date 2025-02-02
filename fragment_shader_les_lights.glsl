#version 330 core
#define MAX_LIGHTS 4

struct Light {
    vec4 position;
    vec4 diffuse;
    vec4 specular;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;
in vec3 fragPosition;
in vec3 normal;
out vec4 frag_colour;

void main() {
    vec3 norm = normalize(normal);
    vec3 result = vec3(0.0); 

    for (int i = 0; i < numberOfLights; i++) {
        vec3 lightDir = normalize(vec3(lights[i].position) - fragPosition);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(lights[i].diffuse);

        vec3 viewDir = normalize(-fragPosition);  
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
        vec3 specular = spec * vec3(lights[i].specular);

        result += diffuse + specular;
    }

    vec3 ambient = vec3(0.1, 0.1, 0.1);
    result = ambient + result;

    frag_colour = vec4(result, 1.0);  
}
