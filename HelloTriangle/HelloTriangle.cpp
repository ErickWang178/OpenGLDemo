#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#pragma comment (lib,"opengl32.lib")

#pragma comment (lib,"glew32s.lib")
#pragma comment (lib,"glew32.lib")

#pragma comment (lib,"glfw3.lib")
#pragma comment (lib,"glfw3dll.lib")

//�����ص�����
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	int width = 600;
	int height = 400;

	// C++11��������һ�����µĹؼ���nullptr,�����ָ�룬���ܱ�ת��������
	GLFWwindow* window = glfwCreateWindow(width, height, "Hello Triangle", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Fail to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//�����ڵ�����Ϊ��ǰ�̵߳���������
	glfwMakeContextCurrent(window);
	
	// �󶨼��̻ص�����
	glfwSetKeyCallback(window, key_callback);

	/*
		GLEW����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLEW
		�ڴ��ڴ���֮�����
	*/
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Fail to init GLEW" << std::endl;

		return -1;
	}

	//���ô��ڵ�ά�ȣ����ӿڣ�ViewPoint��
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0,0,width, height);

	//������������
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//�������㻺�����VBO��
	GLuint VBO;
	glGenBuffers(1,&VBO);

	//�󶨻������
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	//�����������ݵ��Դ�
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//-------------------------------------------------------------//
	//����������ɫ��
	GLchar * vertexShader = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x,position.y,position.z,1.0);"
		"}\n";

	GLuint vertexSharderId;
	vertexSharderId = glCreateShader(GL_VERTEX_SHADER);
	//����ɫ��Դ�븽�ӵ���ɫ��������,Ȼ�������
	glShaderSource(vertexSharderId, 1, &vertexShader, NULL);
	glCompileShader(vertexSharderId);

	//�жϱ����Ƿ���ȷ
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexSharderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexSharderId,sizeof(infoLog), nullptr, infoLog);

		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

    //----------------------------------------------------------//
	//����Ƭ����ɫ��
	GLchar* fragmentShader = "#version 330 core\n "
		"out vec4 color; "
		"void main(){ "
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f); "
		"}";

	GLuint fragmentShaderId;
	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
	glCompileShader(fragmentShaderId);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), nullptr, infoLog);

		std::cout << "ERROR::SHADER::FRAMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(1.0f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);
	}


	glfwTerminate(); //�˳������ͷ�glfw��Դ
	return 0;
}