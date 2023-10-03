#shader vertex
#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;
  
out vec4 fragColor;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * aPosition;
    fragColor = aColor;
}   

#shader fragment
#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}