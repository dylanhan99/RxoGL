#version 330 core

out vec4 o_Col;

in vec4 v_Col;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[2];

void main()
{
    int index = int(v_TexIndex);
    o_Col = texture(u_Textures[index], v_TexCoord);
    //o_Col = v_Col;
    //o_Col = vec4(v_TexIndex, v_TexIndex, v_TexIndex, 1.0);
}