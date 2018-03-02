#version 330 core

layout (location = 0) in vec3 position;


uniform mat4 lightmodel;
uniform mat4 lightview;
uniform mat4 lightprojection;

void main(){
	gl_Position = lightprojection * lightview * lightmodel * vec4(position,1.0f);
}