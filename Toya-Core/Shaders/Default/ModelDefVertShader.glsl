#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 _modelMatrixS = mat4(1.0f);
uniform mat4 _viewMatrixS;
uniform mat4 _projectionMatrixS;

void main()
{
    gl_Position = _projectionMatrixS * _viewMatrixS* _modelMatrixS* vec4(position, 1.0f);
    TexCoords = texCoords;
}