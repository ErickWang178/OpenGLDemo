/*
��ȷ���ڰ���GLFW��ͷ�ļ�֮ǰ������GLEW��ͷ�ļ���
�ڰ���glew.hͷ�ļ�ʱ���������OpenGL��Ҫ��ͷ�ļ�������GL/gl.h����
��������Ҫ�ڰ�������������OpenGL��ͷ�ļ�֮ǰ�Ȱ���GLEW��
*/
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#pragma comment (lib, "opengl32.lib")

#pragma comment (lib, "glfw3.lib")
#pragma comment (lib, "glfw3dll.lib")

#pragma comment (lib,"glew32s.lib")
#pragma comment (lib,"glew32.lib")

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}