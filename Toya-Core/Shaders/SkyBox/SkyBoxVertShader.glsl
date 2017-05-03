#version 330 core
layout (location = 0) in vec3 vertexPosition_ModelSpace;
out vec3 TextureDirection;

uniform mat4 _projectionMatrix = mat4(1.0f);
uniform mat4 _viewMatrix = mat4(1.0f);


void main()
{
	vec4 pos = _projectionMatrix * _viewMatrix* vec4(vertexPosition_ModelSpace, 1.0);
    gl_Position = pos.xyww;
    TextureDirection = vertexPosition_ModelSpace;
}  