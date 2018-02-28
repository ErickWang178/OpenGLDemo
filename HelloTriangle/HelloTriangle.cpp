#include<iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#pragma comment (lib,"opengl32.lib")

#pragma comment (lib,"glew32s.lib")
#pragma comment (lib,"glew32.lib")

#pragma comment (lib,"glfw3.lib")
#pragma comment (lib,"glfw3dll.lib")

//按键回调函数
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

	// C++11，其中有一个是新的关键字nullptr,代表空指针，不能被转换成数字
	GLFWwindow* window = glfwCreateWindow(width, height, "Hello Triangle", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Fail to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//将窗口的设置为当前线程的主上下文
	glfwMakeContextCurrent(window);
	
	// 绑定键盘回调函数
	glfwSetKeyCallback(window, key_callback);

	/*
		GLEW是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLEW
		在窗口创建之后调用
	*/
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Fail to init GLEW" << std::endl;

		return -1;
	}

	//设置窗口的维度，即视口（ViewPoint）
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0,0,width, height);

	//顶点坐标输入
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//创建顶点缓冲对象（VBO）
	GLuint VBO;
	glGenBuffers(1,&VBO);

	//绑定缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	//拷贝顶点数据到显存
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//-------------------------------------------------------------//
	//创建顶点着色器
	GLchar * vertexShader = "#version 330 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x,position.y,position.z,1.0);"
		"}\n";

	GLuint vertexSharderId;
	vertexSharderId = glCreateShader(GL_VERTEX_SHADER);
	//将着色器源码附加到着色器对象上,然后编译它
	glShaderSource(vertexSharderId, 1, &vertexShader, NULL);
	glCompileShader(vertexSharderId);

	//判断编译是否正确
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexSharderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexSharderId,sizeof(infoLog), nullptr, infoLog);

		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

    //----------------------------------------------------------//
	//创建片段着色器
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


	glfwTerminate(); //退出程序释放glfw资源
	return 0;
}