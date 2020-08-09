#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow*pWindow,int nWidth,int nHeight);
void processInput(GLFWwindow*pWindow);

const char * pVertexShader = "#version 330 core\n"
"layout(location = 0) in vec3 apos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(apos.x,apos.y,apos.z,1.0f);\n"
"}\n";

int main()
{
	//glfw初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* pWindow = glfwCreateWindow(800, 600, "two_triangles", NULL, NULL);
	if (!pWindow)
	{
		std::cout << "ERROR::GLFW::CREATE_WINDOW_FAILE" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindow);
	glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "ERROR::GLAD_INIT_FAILE" << std::endl;
		glfwTerminate();
		return -1;
	}

	//创建并编译顶点着色器
	unsigned int unVertexShader = 0;
	unVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(unVertexShader, 1, &pVertexShader, NULL);
	glCompileShader(unVertexShader);

	int nSuccess = 0;
	char cInfoLog[512] = { 0 };
	glGetShaderiv(unVertexShader,GL_COMPILE_STATUS,&nSuccess);
	if (!nSuccess)
	{
		glGetShaderInfoLog(unVertexShader,512,NULL,cInfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILE\n" << cInfoLog << std::endl;
	}

	glDeleteShader(unVertexShader);

	while (!glfwWindowShouldClose(pWindow))
	{
		processInput(pWindow);
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow*pWindow, int nWidth, int nHeight)
{
	glViewport(0,0,nWidth,nHeight);
}

void processInput(GLFWwindow*pWindow)
{
	if (glfwGetKey(pWindow,GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
}
