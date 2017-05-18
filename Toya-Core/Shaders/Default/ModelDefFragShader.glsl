#version 330 core
out vec4 color;

in DATA{
    vec4 fragPos;
    vec2 TexCoords;
    vec3 fragNormal;
} fs_in;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight 
{
    vec3 direction;

	vec4 color;

	float dFactor;
	float sFactor;
};  
struct PointLight {    
    vec3 position;
    
	vec4 color;
    
	float constant;
    float linear;
    float quadratic;  
	
	float dFactor;
	float sFactor;
};  

#define MAX_POINT_LIGHTS 100 
#define ALPHA_THRESHOLD .1
/*Uniforms*/
uniform DirLight dirLight;
uniform Material material;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform vec4 ambientColor;

uniform vec3 viewPos;


uniform int LightCount;

uniform int gray;
/*Func Proto*/
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
/*****************************/


void main(){
  
    vec3 norm = normalize(fs_in.fragNormal);
    vec3 viewDir = normalize(viewPos - fs_in.fragPos.xyz);
    
    vec4 result = CalcDirLight(dirLight, norm, viewDir);
    
    for(int i = 0; i < LightCount; i++)
       result += CalcPointLight(pointLights[i], norm, fs_in.fragPos.xyz, viewDir);
	
	if(result.a < ALPHA_THRESHOLD)
	   discard;

	if(gray == 0)
	 {
		color = result;
	 }
	 else
		{
			float g = (result.r + result.g + result.b) / 3;
			color = vec4(g,g,g,1.0f);
		}
}

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(lightDir, normal),0.0f);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    // Combine results
    vec4 ambient  = (ambientColor  * 1.0f		   ) * texture(material.diffuse, fs_in.TexCoords);
    vec4 diffuse  = (light.color   * light.dFactor) * diff * texture(material.diffuse, fs_in.TexCoords);
    vec4 specular = (light.color   * light.sFactor) * spec * texture(material.specular, fs_in.TexCoords);
    return (ambient + diffuse + specular);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir,reflectDir), 0.0), material.shininess);
    // Attenuation
    float _distance  = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * _distance + light.quadratic * (_distance * _distance));    
    // Combine
    vec4 ambient  = (ambientColor * 1.0f		 ) * texture(material.diffuse, fs_in.TexCoords);
    vec4 diffuse  = (light.color  * light.dFactor) * diff * texture(material.diffuse, fs_in.TexCoords);
    vec4 specular = (light.color  * light.sFactor) * spec * texture(material.specular, fs_in.TexCoords);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 