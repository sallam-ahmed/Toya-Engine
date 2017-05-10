#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;


uniform mat4 _modelMatrix = mat4(1.0f);
uniform mat4 _viewMatrix = mat4(1.0f);
uniform mat4 _projectionMatrix = mat4(1.0f);

out DATA{
    vec4 fragPos;
    vec2 TexCoords;
    vec3 fragNormal;
} vs_out;

void main()
{
    gl_Position = _projectionMatrix * _viewMatrix * _modelMatrix* vec4(position, 1.0f);

	vs_out.fragPos = _modelMatrix * vec4(position,1);
	vs_out.TexCoords = texCoords;
	vs_out.fragNormal =  mat3(transpose(inverse(_modelMatrix))) * normal;  

}