#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct Material{
	vec3 ambient; //环境
	vec3 diffuse; //漫反射
	vec3 specular; //镜面
	float shininess; //发光值
};

struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 cubeColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform vec3 viewPos;

void main(){
	//设置材质
	//环境光
	vec3 ambient = light.ambient * material.ambient;

	//漫反射
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(normal,lightDir),0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//镜面高光
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;

	color = vec4(result,1.0f);
}