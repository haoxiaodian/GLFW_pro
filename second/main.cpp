/*********************************************
*	  修改顶点着色器，让三角形上下颠倒		 *
*********************************************/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* pWindow = glfwCreateWindow(800,600,"GLSL",nullptr,nullptr);
	if (!pWindow)
	{
		std::cout << "ERROR::CREATE_WINDOW_FAILE\n" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(pWindow);


	return 0;
}

