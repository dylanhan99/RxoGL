#version 330 core

out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    //vec4 texColor = texture(u_Texture, v_TexCoord);

	// Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    //color = fragmentColor;
    color = texture(u_Texture, v_TexCoord);
    //color = vec4(1.0);
}