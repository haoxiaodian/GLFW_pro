#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void frambuffer_size_callback(GLFWwindow* pWindow,int nWidth,int nHeight);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//��֪GLFWʹ��OpenGL���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//��֪GLFWʹ��OpenGL���汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ģʽ
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//MAC os

	//����һ������
	GLFWwindow * pWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (pWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindow);

	//ע��ص�����
	glfwSetFramebufferSizeCallback(pWindow, frambuffer_size_callback);

	//ʹ��GLAD����OPENGLָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init OpenGl by glad!" << std::endl;
		return -1;
	}

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(pWindow))//���glfw�Ƿ�Ҫ���˳�
	{
		/*������ɫ���壬������GLFW���ڵ�ÿ��������ɫֵ�Ļ��棬����
		һ�����б��������ƣ����ҽ���Ϊ�����ʾ����Ļ��*/
		glfwSwapBuffers(pWindow);
		glfwPollEvents();//����Ƿ����¼�����
	}

	glfwTerminate();//�ͷŷ�����Դ
	return 0;
}

void frambuffer_size_callback(GLFWwindow* pWindow, int nWidth, int nHeight)
{
	glViewport(0, 0, 800, 600);
}