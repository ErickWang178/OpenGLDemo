#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

struct Material{
	vec3 ambient; //����
	vec3 diffuse; //������
	vec3 specular; //����
	float shininess; //����ֵ
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
	//���ò���
	//������
	vec3 ambient = light.ambient * material.ambient;

	//������
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(normal,lightDir),0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//����߹�
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,normal);
	float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	vec3 result = ambient + diffuse + specular;

	color = vec4(result,1.0f);
}