#shader vertex
#version 330 core

layout (location = 0) in vec4 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
  
out vec4 fragColor;
out vec2 texCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * aPosition;
    fragColor = aColor;
	texCoord = aTexCoord;
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