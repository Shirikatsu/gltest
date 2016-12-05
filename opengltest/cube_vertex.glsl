#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 newColor;

uniform mat4 transform;
uniform float phase;
uniform float time_value;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0f);
	newColor = vec3((sin(time_value + (color.x * phase)) / 2.0) + 0.3, (sin(time_value + (color.y * phase)) / 2.0) + 0.3, (sin(time_value + (color.z * phase)) / 2.0) + 0.3);
}