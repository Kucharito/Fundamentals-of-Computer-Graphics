#version 330 core

#define MAX_LIGHTS 4

in vec3 fragPosition;
in vec3 normal;

out vec4 frag_colour;

uniform vec3 viewPosition;

struct Light {
    int typeLight;
    vec3 lightPosition;
    vec3 lightColor;
    vec3 lightAttenuation;
    float lightCutOff;
    vec3 lightDirection;
};

uniform int numberOfLights;
uniform Light lights[MAX_LIGHTS];
uniform float ra, rd, rs;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 resultColor = vec3(0.0);

    vec3 ambient = vec3(0.3);

    for (int i = 0; i < numberOfLights; i++) {
        vec3 lightDir;
        float attenuation = 1.0;

        if (lights[i].typeLight == 1) {
            lightDir = normalize(lights[i].lightPosition - fragPosition);
        }
        else if (lights[i].typeLight == 2) {
            lightDir = normalize(lights[i].lightPosition - fragPosition);
            float spot = dot(normalize(lights[i].lightDirection), -lightDir);
            if (spot < lights[i].lightCutOff) continue;
        }
        else if (lights[i].typeLight == 3) {
            lightDir = normalize(-lights[i].lightDirection);
        }

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = rd * diff * lights[i].lightColor;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        vec3 specular = rs * spec * lights[i].lightColor;

        resultColor += diffuse + specular;
    }

    frag_colour = vec4(ambient + resultColor, 1.0);
}
