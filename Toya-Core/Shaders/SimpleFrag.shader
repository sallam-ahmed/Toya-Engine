#version 330 core
// Ouput data
out vec4 color;
uniform vec2 light_pos;
uniform float time_val = 1.0f;
in DATA{
	vec4 pos;
	vec4 color;
} fs_in;

void main()
{
	//basic lighting
	float intensity = 1.0 / length(fs_in.pos.xy - light_pos) * 10;
	color = (fs_in.color )/** sin(time_val) / 2 + 0.5 )*/ * intensity; 
}