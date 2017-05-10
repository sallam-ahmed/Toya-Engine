#version 330 core
layout (location = 0) in vec4 vertexData; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 _projectionMatrixS;

void main()
{
    gl_Position = _projectionMatrixS * vec4(vertexData.xy, 0.0, 1.0);
    TexCoords = vertexData.zw;
} 