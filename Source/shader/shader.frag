#version 330 core

// Interpolated values from the vertex shaders
in vec4 v2fPos;
in vec3 v2fColour;
// Ouput data
out vec4 oColour;

void main(){

	// Output color = color of the texture at the specified UV
	oColour = vec4(v2fColour,1.f);
}