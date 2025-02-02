#version 330 core
in vec3 fragPosition;
in vec3 transformedNormal;

out vec4 frag_colour;

uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;

void main()
{
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec3 norm = normalize(transformedNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 diffuse = diff * lightColor;

    float specularStrength = 4.0;
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor.rgb;
    frag_colour = vec4(result, 1.0);
}
