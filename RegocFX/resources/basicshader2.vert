#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm;

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

void main()
{
    gl_Position = proj * view * model * vec4(pos, 1.0);
    vCol = vec4(clamp(vec3(pos.x, pos.y, pos.z), 0.0f, 1.0f), 1.0);
    
    TexCoord = tex;
    
    Normal = mat3(transpose(inverse(model))) * norm;
    
    FragPos = (model * vec4(pos, 1.0)).xyz;
}


