#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColour;
// Output data ; will be interpolated for each fragment.
out vec4 v2fPos;
out vec3 v2fColour;

// Values that stay constant for the whole mesh.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	
	gl_Position =  model * view * projection * vec4(inPos, 1.f);
	v2fPos = model * vec4(inPos, 1.f);
	v2fColour = inColour;
}