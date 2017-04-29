#version 330 core
out vec3 color;
struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

/***************************************************************/
// Camera Position [Eye]
uniform vec3 eyePosition;
/***************************************************************/
//Sent from Vertex Shader for each frag
in DATA{
	vec4 pos;
	vec4 color;
	vec2 texCoord;
	vec3 norm;
} fs_in;

uniform Material material;
uniform Light light;
//TEXTURE UNIT FOR MODEL WITH SINGLE TEXTURE
uniform sampler2D texture_diffuse;

void main()
{

	vec3 textureColor = texture(texture_diffuse,fs_in.texCoord).rgb;
	//Ambient Color
	vec3 ambient = light.ambient * material.ambient;
	
	//Calculating Diffuse Color
	vec3 normalV = normalize(fs_in.norm	);
	vec3 lightDir = normalize(light.position - fs_in.pos.xyz);  
	float diff = max(dot(normalV, lightDir), 0.0); // Brightness Amount
	vec3 diffuse = light.diffuse * (diff * material.diffuse); //Colored Brightness
	//Calculating  Specular Color
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(eyePosition - fs_in.pos.xyz);
	vec3 reflectDirection = reflect(-lightPosition,normalV);
	float specularity = max(dot(viewDirection,reflectDirection),0.0);
	specularity = pow(specularity,material.shininess);
	vec3 specular = light.specular * ( specularity * material.specular);   
	vec3 finalColor = ambient + diffuse + specular; // + Diff + Spec + Ambient
	color = mix(textureColor,finalColor,0.05);//,texture(cubeMapSampler,cubeMapTextureDirection);
}