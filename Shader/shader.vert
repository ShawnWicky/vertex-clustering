#version 330 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v2fPosition;
out vec3 v2fNormal;

void main()
{
    v2fPosition = vec3(model * vec4(iPos, 1.0));
    v2fNormal = mat3(transpose(inverse(model))) * iNormal;
    
    gl_Position = projection * view * model * vec4(iPos, 1.0f);
}
