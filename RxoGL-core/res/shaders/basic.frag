#version 330 core

out vec4 color;
//out vec3 color;

//in vec2 v_TexCoord;
in vec4 fragmentColor;

uniform sampler2D u_Texture;

void main()
{
    //color = texture(u_Texture, v_TexCoord);
    color = fragmentColor;
}