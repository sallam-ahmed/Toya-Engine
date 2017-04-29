#version 330 core
out vec4 color;

//in vec3 cubeMapTextureDirection;

uniform vec2 light_pos;
uniform float time_val = 1.0f;

in DATA{
	vec4 pos;
	vec4 color;
	vec2 texCoord;
	vec3 norm;
} fs_in;

uniform sampler2D texture_diffuse;
//uniform samplerCube cubeMapSampler;

void main()
{
	//basic lighting
	float intensity = 1.0 / length(fs_in.pos.xy - light_pos) * 10;
	color =texture(texture_diffuse, fs_in.texCoord).rgba;//,texture(cubeMapSampler,cubeMapTextureDirection);
}