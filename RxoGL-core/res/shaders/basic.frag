#version 330 core

out vec4 o_Col;

in vec4 v_Col;
in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[10];
uniform sampler2D u_Texture;

void main()
{
    o_Col = v_Col;
    if(v_TexIndex > 0.0)
    {
        int index = int(v_TexIndex);
        //o_Col = texture(u_Textures[index], v_TexCoord);
        o_Col = texture(u_Textures[index - 1], v_TexCoord);
    }
    //o_Col = vec4(v_TexIndex, v_TexIndex, v_TexIndex, 1.0);

}