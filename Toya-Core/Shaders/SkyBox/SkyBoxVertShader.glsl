#version 330 core
layout (location = 0) in vec3 vertexPosition_ModelSpace;
out vec3 TextureDirection;

uniform mat4 projection = mat4(1.0f);
uniform mat4 view = mat4(1.0f);


void main()
{
	vec4 pos = projection * view* vec4(vertexPosition_ModelSpace, 1.0);
    gl_Position = pos.xyww;
    TextureDirection = vertexPosition_ModelSpace;
}  