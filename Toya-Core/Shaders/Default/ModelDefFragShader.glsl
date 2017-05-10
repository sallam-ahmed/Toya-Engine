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
/*Uniforms*/
uniform DirLight dirLight;
uniform Material material;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform vec4 ambientColor;

uniform vec3 viewPos;

uniform int isGray;


uniform int LightCount;
/*Func Proto*/
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
/*****************************/


void main(){
   
    vec3 norm = normalize(fs_in.fragNormal);
    vec3 viewDir = normalize(viewPos - fs_in.fragPos.xyz);
    
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    
    for(int i = 0; i < LightCount; i++)
       result += CalcPointLight(pointLights[i], norm, fs_in.fragPos.xyz, viewDir);
    
    color = /*texture(material.diffuse,fs_in.TexCoords);//*/vec4(result, 1.0);
	//if(isGray == 1)
	//{
	//float gray = (color.r+color.g+color.b)/3;
	//color.r = gray;
	//color.g = gray;
	//color.b = gray;
	//}
	
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir){
    vec3 final = vec3(1.0f,0.0f,1.0f);

    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
    vec3 ambient  = ambientColor.xyz  * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse  = (light.color.xyz   * light.dFactor) * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 specular = (light.color.xyz   * light.sFactor) * spec * vec3(texture(material.diffuse, fs_in.TexCoords));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
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
    vec3 ambient  = ambientColor.xyz  * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 diffuse  = (light.color.xyz * light.dFactor) * diff * vec3(texture(material.diffuse, fs_in.TexCoords));
    vec3 specular = (light.color.xyz * light.sFactor) * spec * vec3(texture(material.specular, fs_in.TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 