
#version 330 core

#define MAX_LIGHTS 4

in vec3 fragPosition;
in vec3 transformedNormal; 

out vec4 frag_colour;

uniform vec3 viewPosition;
uniform int numberOfLights;

struct Light {
    vec4 position;   
    vec4 diffuse;    
    vec4 specular;  
};

uniform Light lights[MAX_LIGHTS];

void main()
{
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0); 
    vec3 norm = normalize(transformedNormal); 
    vec3 viewDir = normalize(viewPosition - fragPosition);  
    vec3 resultColor = vec3(0.0);                     

    for (int i = 0; i < numberOfLights; i++) {
        vec3 lightPos = vec3(lights[i].position);
        vec3 lightDir = normalize(lightPos - fragPosition); 
        float distance = length(lightPos - fragPosition);   

        const float constant = 1.0;
        const float linear = 0.09;
        const float quadratic = 0.032;

        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(lights[i].diffuse) * attenuation;

        vec3 reflectDir = reflect(-lightDir, norm); 
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16); 
        vec3 specular = vec3(lights[i].specular) * spec * attenuation;

        resultColor += (diffuse + specular) * objectColor.rgb;
    }

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    frag_colour = vec4(resultColor + ambient, objectColor.a);
}
