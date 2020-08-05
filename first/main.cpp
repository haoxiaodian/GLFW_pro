#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void frambuffer_size_callback(GLFWwindow* pWindow,int nWidth,int nHeight);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//告知GLFW使用OpenGL主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//告知GLFW使用OpenGL副版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//MAC os

	//创建一个窗口
	GLFWwindow * pWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (pWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindow);

	//注册回调函数
	glfwSetFramebufferSizeCallback(pWindow, frambuffer_size_callback);

	//使用GLAD管理OPENGL指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init OpenGl by glad!" << std::endl;
		return -1;
	}

	//渲染循环
	while (!glfwWindowShouldClose(pWindow))//检查glfw是否要求被退出
	{
		/*交换颜色缓冲，它存着GLFW窗口的每个像素颜色值的缓存，在这
		一迭代中被用来绘制，并且将作为输出显示在屏幕上*/
		glfwSwapBuffers(pWindow);
		glfwPollEvents();//检查是否有事件触发
	}

	glfwTerminate();//释放分配资源
	return 0;
}

void frambuffer_size_callback(GLFWwindow* pWindow, int nWidth, int nHeight)
{
	glViewport(0, 0, 800, 600);
}