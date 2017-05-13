#version 330 core
out vec4 color;
in vec3 TextureDirection;

uniform samplerCube skybox;
uniform int gray;
void main(){
	if(gray == 0)
		color = texture(skybox,TextureDirection);
	else{
		vec4 col = texture(skybox,TextureDirection);
		float g = (col.x + col.y + col.z) /3;
		color = vec4(g,g,g,1.0f);
	}
}