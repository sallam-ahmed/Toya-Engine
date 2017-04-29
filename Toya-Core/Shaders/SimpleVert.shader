#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertexColor;

uniform mat4 _viewMatrix = mat4(1.0);
uniform mat4 _modelMatrix = mat4(1.0);
uniform mat4 _projectionMatrix = mat4(1.0);

out DATA{
	vec4 pos;
	vec4 color;
} vs_out;


void main() {
	gl_Position = (_projectionMatrix *  _viewMatrix * _modelMatrix) * vec4(vertexPosition_modelspace,1);
	vs_out.pos = _modelMatrix * vec4(vertexPosition_modelspace,1);
	vs_out.color = vertexColor;
}