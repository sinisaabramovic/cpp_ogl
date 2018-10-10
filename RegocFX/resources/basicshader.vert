#version 330
layout (location = 0) in vec3 pos;
out vec4 vCol;
uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;
void main()
{
    gl_Position = proj * view * model * vec4(pos, 1.0);
    vCol = vec4(clamp(vec3(pos.x, pos.y, pos.z), 0.0f, 1.0f), 1.0);
}

