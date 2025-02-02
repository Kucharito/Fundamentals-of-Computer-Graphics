
#version 330 core

uniform vec3 lightDirection;   
uniform vec3 lightPosition;   
uniform vec3 lightColor;       
uniform vec3 attenuation;     

uniform float cutOff;

in vec3 worldNormal;
in vec3 worldPosition;


out vec4 frag_colour;

void main() {
    vec3 normalizedNormal = normalize(worldNormal);
    vec3 lightVector = normalize(lightPosition - worldPosition);

    float distance = length(lightPosition - worldPosition);

    float attenuationFactor = 1.0 / (attenuation.x + attenuation.y * distance + attenuation.z * (distance * distance));

    float diff = max(dot(normalizedNormal, lightVector), 0.0);

    vec3 viewVector = normalize(-worldPosition);
    vec3 reflectVector = reflect(-lightVector, normalizedNormal);
    float spec = pow(max(dot(viewVector, reflectVector), 0.0), 32.0);

    float spot = dot(normalize(lightDirection), -lightVector);
    if (spot < cutOff) {
        spec = 0.0;
        diff = 0.0;
    }
    spot = (spot - cutOff) / (1.0 - cutOff);

    vec3 spotlightEffect = (diff + spec) * spot * lightColor;


    vec3 baseColor = vec3(0.2, 0.8, 0.2); 

    vec3 finalColor = baseColor * (  spotlightEffect * attenuationFactor);

    frag_colour = vec4(finalColor, 1.0);
}