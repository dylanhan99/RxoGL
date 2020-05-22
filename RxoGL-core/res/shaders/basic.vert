#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

//layout(location = 1) in vec3 vertexColor;
//out vec3 fragmentColor;
out vec2 v_TexCoord;

// Values that stay constant for the whole mesh.
uniform mat4 u_MVP;
  
void main(){
    // Output position of the vertex, in clip space : MVP * position
    gl_Position = u_MVP * position;

  
    // The color of each vertex will be interpolated
    // to produce the color of each fragment
    //fragmentColor = vertexColor;
    v_TexCoord = texCoord;

}