#version 330

in vec3 FragPos; 
in vec3 Normal;  

uniform vec3 lightPosition;  
uniform vec3 lightColor;     
uniform vec3 objectColor; 

out vec4 FragColor;

void main() {
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    
    vec3 ambient = 0.1 * lightColor; 
     
    float diff = max(dot(norm, lightDir), 0.0); 
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor.rgb;
    FragColor = vec4(result, 1.0);
}
