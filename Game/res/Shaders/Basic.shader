#shader vertex
#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;
  
out vec4 fragColor;

void main()
{
    gl_Position = aPosition;
    fragColor = aColor;
}   

#shader fragment
#version 330 core

in vec4 fragColor;
out vec4 outColor;
  
void main()
{
    outColor = fragColor;
} 