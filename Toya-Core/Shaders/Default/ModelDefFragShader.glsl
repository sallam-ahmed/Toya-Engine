#version 330 core

in vec2 TexCoords;

out vec4 color;
struct Material{
	float shininess;
	
};
uniform Material material;
uniform sampler2D texture_diffuse;
//uniform sampler2D texture_diffuse2;
//uniform sampler2D texture_diffuse1;

void main()
{    
    color = vec4(texture(texture_diffuse, TexCoords));// + texture(texture_diffuse2, TexCoords) );// * vec4(.4f,.3f,.1f,1.0f);
}