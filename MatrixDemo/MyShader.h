/**
�Զ�����ɫ���࣬���ڱ��������ɫ����
���ܣ������Դ�Ӳ�̶�ȡ��ɫ����Ȼ����벢�������ǣ��������ǽ��д�����
*/

#ifndef MY_SHADER_H
#define MY_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // GLEW_STATIC

#include <GL/glew.h> // ����glew����ȡ���еı���OpenGLͷ�ļ�

class MyShader
{
public:
	GLuint mProgram;

	MyShader(const GLchar *vertextPath, const GLchar *fragmentPath);
	void use();
};


MyShader::MyShader(const GLchar *vertextPath, const GLchar *fragmentPath){
	if (vertextPath == nullptr || fragmentPath == nullptr) {
		std::cout << "File path can not be null" << std::endl;
		return;
	}

	//ʹ��C++�������ȡ�ļ�
	std::string vertexCode, framgmentCode;
	std::ifstream vShaderFile, fShaderFile;

	//��֤ifstream��������׳��쳣
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		//���ļ�
		vShaderFile.open(vertextPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShderStream, fShaderStream;

		//��ȡ�ļ��Ļ������ݵ�����
		vShderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//�ر��ļ�
		vShaderFile.close();
		fShaderFile.close();

		//ת����ֵGLchar����
		vertexCode = vShderStream.str();
		framgmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = framgmentCode.c_str();

	//�����������ɫ��
	GLuint vertex, fragment;
	GLint success;
	GLchar inforLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//���������
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, sizeof(inforLog), NULL, inforLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << inforLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//���������
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, sizeof(inforLog), NULL, inforLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << inforLog << std::endl;
	}

	//��ɫ������
	this->mProgram = glCreateProgram();
	glAttachShader(this->mProgram, vertex);
	glAttachShader(this->mProgram, fragment);
	glLinkProgram(this->mProgram);

	glGetProgramiv(this->mProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->mProgram, sizeof(inforLog), NULL, inforLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << inforLog << std::endl;
	}

	//ɾ����ɫ��
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void MyShader::use(){
	glUseProgram(this->mProgram);
}

#endif