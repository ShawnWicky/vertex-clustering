#version 330 core

in vec3 v2fNormal;

out vec4 FragColor;



void main()
{
    vec3 normal = normalize(v2fNormal);
    
    FragColor = vec4(normal, 1.0f);
}
