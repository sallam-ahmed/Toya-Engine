#version 330 core
out vec3 color;


/***************************************************************/
//Ambient Color Set Sent By Lighting Settings
uniform float ambientStrength = 0.1f;
uniform vec4 ambientLightColor = vec4(.4f,.4f,.4f,1.0f);
/***************************************************************/
//Light Source Properties
uniform vec3 lightPosition; // Light Source Position
uniform vec4 lightColor;
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

//TEXTURE UNIT FOR MODEL WITH SINGLE TEXTURE
uniform sampler2D texture_diffuse;

void main()
{

	vec3 textureColor = texture(texture_diffuse,fs_in.texCoord).rgb;

	//Ambient Color
	vec3 ambient = (ambientLightColor * ambientStrength).xyz;
	
	//Calculating Diffuse Color
	vec3 normalV = normalize(fs_in.norm	);
	vec3 lightDir = normalize(lightPosition - fs_in.pos.xyz);  
	float diff = max(dot(normalV, lightDir), 0.0); // Brightness Amount
	vec3 diffuse = diff * lightColor.xyz; //Colored Brightness
	
	//Calculating  Specular Color
	float specularStrength = 0.5f;
	vec3 viewDirection = normalize(eyePosition - fs_in.pos.xyz);
	vec3 reflectDirection = reflect(-lightPosition,normalV);
	float specularity = max(dot(reflectDirection , viewDirection),0.0);
	
	float specularExpo = 32.0f;
	
	specularity = pow(specularity,specularExpo);
	vec3 specular = specularStrength * specularity * lightColor.xyz;   
	vec3 clampedSpec = clamp(specular,0.0f,1.0f);
	vec3 finalColor = ambient + diffuse + clampedSpec; // + Diff + Spec + Ambient
	*/
	color = textureColor * ;// * finalColor ;//mix(textureColor,finalColor,0.05);//,texture(cubeMapSampler,cubeMapTextureDirection);
}