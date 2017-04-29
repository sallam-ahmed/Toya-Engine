#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 vertex_color;
layout(location = 2) in vec2 vertex_tex_coord;
layout(location = 3) in vec3 vertex_normal;

uniform mat4 _modelMatrix = mat4(1.0f);
uniform mat4 _projectionMatrix= mat4(1.0f);
uniform mat4 _viewMatrix= mat4(1.0f);
//Data For Shader Output Params
out DATA{
	vec4 pos;
	vec4 color;
	vec2 texCoord;
	vec3 norm;
} vs_out;

void main(){
	gl_Position = (_projectionMatrix *  _viewMatrix * _modelMatrix) * vec4(vertexPosition_modelspace,1);	
	
	vs_out.pos = _modelMatrix * vec4(vertexPosition_modelspace,1);
	vs_out.color = vertex_color;
	vs_out.texCoord = vertex_tex_coord;
	vs_out.norm = vertex_normal;
}