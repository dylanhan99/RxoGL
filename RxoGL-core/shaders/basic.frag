#version 330 core

//out vec4 color;
in vec3 fragmentColor;
out vec3 color;

void main()
{
	// Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    color = fragmentColor;
}