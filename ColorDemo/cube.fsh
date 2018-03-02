#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform vec3 cubeColor;
uniform vec3 lightColor;

uniform vec3 lightPos;

uniform vec3 viewPos;

void main(){
	float ambintstrength = 0.2f;
	vec3 ambint = ambintstrength * lightColor;

	//计算光线方向
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 normal = normalize(Normal);

	float diff = max(dot(lightDir,normal),0.0f);
	vec3 diffuse = diff * lightColor;

	

	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
	
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (specular + diffuse + ambint) * cubeColor;
	color = vec4(result,1.0f);
}