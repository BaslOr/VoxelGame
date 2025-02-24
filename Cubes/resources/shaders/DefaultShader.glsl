#type vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
    
uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
    
out vec2 TexCoord;
    
void main()
{
    gl_Position = u_ViewProjection * u_Model * vec4(aPos.xyz, 1.0);
    TexCoord = aTexCoord;
}

#type fragment
#version 330 core
out vec4 FragColor;
    
in vec2 TexCoord;
    
uniform vec4 u_Color;
uniform sampler2D u_Sampler;
    
void main()
{
    FragColor = texture(u_Sampler, TexCoord) * u_Color;
}