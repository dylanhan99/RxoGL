#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text[2];
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text[0], TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}  