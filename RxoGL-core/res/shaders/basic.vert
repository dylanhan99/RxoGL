#version 330 core

layout(location = 0) in vec4 position;

//layout(location = 1) in vec2 texCoord;
layout(location = 1) in vec4 vertexColor;

//out vec2 v_TexCoord;
out vec4 fragmentColor;

uniform mat4 u_MVP;
  
void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position = u_MVP * position;

    //v_TexCoord = texCoord;
    fragmentColor = vertexColor;

}