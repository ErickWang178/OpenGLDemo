/**
自定义着色器类，用于编译和理着色器。
功能：它可以从硬盘读取着色器，然后编译并链接它们，并对它们进行错误检测
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

#include <GL/glew.h> // 包含glew来获取所有的必须OpenGL头文件



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

	//使用C++流对象读取文件
	std::string vertexCode, framgmentCode;
	std::ifstream vShaderFile, fShaderFile;

	//保证ifstream对象可以抛出异常
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		//打开文件
		vShaderFile.open(vertextPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShderStream, fShaderStream;

		//读取文件的缓冲内容到流中
		vShderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//关闭文件
		vShaderFile.close();
		fShaderFile.close();

		//转换流值GLchar数组
		vertexCode = vShderStream.str();
		framgmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = framgmentCode.c_str();

	//编译和链接着色器
	GLuint vertex, fragment;
	GLint success;
	GLchar inforLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	//检测编译错误
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, sizeof(inforLog), NULL, inforLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << inforLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	//检测编译错误
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, sizeof(inforLog), NULL, inforLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << inforLog << std::endl;
	}

	//着色器程序
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

	//删除着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void MyShader::use(){
	glUseProgram(this->mProgram);
}

#endif

