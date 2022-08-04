#version 330 core

in vec3 v2fNormal;
in vec3 v2fPosition;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColour;
uniform vec3 meshColour;

void main()
{
    // vec3 normal = normalize(v2fNormal);
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColour;
        
    // diffuse
    vec3 norm = normalize(v2fNormal);
    vec3 lightDir = normalize(lightPos - v2fPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - v2fPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColour;
        
    vec3 result = (ambient + diffuse + specular) * meshColour;
    FragColor = vec4(result, 1.0);
    // FragColor = vec4(0.8274f, 0.8274f, 0.8274f, 1.0f);
}
