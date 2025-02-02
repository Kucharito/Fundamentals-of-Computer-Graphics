
#version 330 core

uniform vec3 lightDirection;  
uniform vec3 lightPosition;   
uniform vec3 lightColor;     
uniform vec3 attenuation;     

//uniform vec3 ambientLightColor; 
//uniform float ambientIntensity; 

uniform float cutOff;

uniform sampler2D textureUnitID;

in vec3 worldNormal;
in vec3 worldPosition;
in vec2 uvc;

out vec4 frag_colour;

void main() {
    vec3 normalizedNormal = normalize(worldNormal);

    float distance = length(lightPosition - worldPosition);

    float attenuationFactor = 1.0 / (attenuation.x + attenuation.y * distance + attenuation.z * (distance * distance));

    vec3 lightVector = normalize(lightPosition - worldPosition);
    vec3 viewVector = normalize(-worldPosition);

    float diff = max(dot(normalizedNormal, lightVector), 0.0);

    vec3 reflectVector = reflect(-lightVector, normalizedNormal);
    float spec = pow(max(dot(viewVector, reflectVector), 0.0), 32.0);

    float spot = dot(normalize(lightDirection), -lightVector);
    if (spot < cutOff) {
        spec = 0.0;
        diff = 0.0;
    }
    spot = (spot - cutOff) / (1.0 - cutOff);

    vec3 spotlightEffect = (diff + spec) * spot * lightColor * attenuationFactor;


    vec4 textureColor = texture(textureUnitID, uvc);

    vec3 finalColor = (spotlightEffect) * textureColor.rgb;
    frag_colour = vec4(finalColor, textureColor.a);
}
