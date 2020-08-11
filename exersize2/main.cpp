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

const char * pFragmentShader1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f,1.0f);\n"
"}\n";

const char * pFragmentShader2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"	FragColor = ourColor;\n"
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

	//创建并编译片段着色器
	unsigned int unFragementShader1 = 0;
	unFragementShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(unFragementShader1,1,&pFragmentShader1,NULL);
	glCompileShader(unFragementShader1);

	int nSucess1 = 0;
	char cInfoLog1[512] = { 0 };
	glGetShaderiv(unFragementShader1,GL_COMPILE_STATUS,&nSucess1);
	if (!nSucess1)
	{
		glGetShaderInfoLog(unFragementShader1, 512, NULL, cInfoLog1);
		std::cout << "ERROR::SHADER::FRAGMENT_COMPILE_FAILE\n" << cInfoLog1<< std::endl;
	}

	//创建并编译片段着色器
	unsigned int unFragmentShader2 = 0;
	unFragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(unFragmentShader2, 1, &pFragmentShader2, NULL);
	glCompileShader(unFragmentShader2);

	int nSuccess3 = 0;
	char cInfoLog3[512] = { 0 };
	glGetShaderiv(unFragmentShader2, GL_COMPILE_STATUS, &nSuccess3);
	if (!nSuccess3)
	{
		glGetShaderInfoLog(unFragmentShader2, 512, NULL, cInfoLog3);
		std::cout << "ERROR::SHADER::FRAGMENT2_COMPILE_FAILE\n" << cInfoLog3 << std::endl;
	}

	//创建并链接着色程序
	unsigned int unShaderProgram1 = 0;
	unShaderProgram1 = glCreateProgram();
	glAttachShader(unShaderProgram1,unVertexShader);
	glAttachShader(unShaderProgram1, unFragementShader1);
	glLinkProgram(unShaderProgram1);

	int nSuccess2 = 0;
	char cInfoLog2[512] = { 0 };
	glGetProgramiv(unShaderProgram1, GL_LINK_STATUS, &nSuccess2);
	if (!nSuccess2)
	{
		glGetProgramInfoLog(unShaderProgram1, 512, NULL, cInfoLog2);
		std::cout << "ERROR::PROGRAM_LINK_FAILE\n" << cInfoLog2 << std::endl;
	}

	unsigned int unShaderProgram2 = 0;
	unShaderProgram2 = glCreateProgram();
	glAttachShader(unShaderProgram2, unVertexShader);
	glAttachShader(unShaderProgram2, unFragmentShader2);
	glLinkProgram(unShaderProgram2);

	int nSuccess4 = 0;
	char cInfoLog4[512] = { 0 };
	glGetProgramiv(unShaderProgram2, GL_LINK_STATUS, &nSuccess4);
	if (!nSuccess4)
	{
		glGetProgramInfoLog(unShaderProgram2, 512, NULL, cInfoLog4);
		std::cout << "ERROR::PROGRAM_LINK_FAILE\n" << cInfoLog4 << std::endl;
	}

	glDeleteShader(unVertexShader);
	glDeleteShader(unFragementShader1);
	glDeleteShader(unFragmentShader2);

	float vertices1[] = {
		-0.5f,0.5f,0.0f,
		0.0f,0.5f,0.0f,
		-0.5f,0.0f,0.0f
	};

	float vertices2[] = {
		0.0f,0.0f,0.0f,
		0.5f,0.0f,0.0f,
		0.0f,-0.5f,0.0f
	};

	unsigned int VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 0,(void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(pWindow))
	{
		processInput(pWindow);
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(unShaderProgram1);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(unShaderProgram2);
		//使用Uniform更新颜色
		float fTimeValue = glfwGetTime();
		float fGreenValue = sin(fTimeValue) / 2.0f + 0.5;
		int nVertexColorLocation = glGetUniformLocation(unShaderProgram2, "ourColor");
		glUniform4f(nVertexColorLocation, 0.0f, fGreenValue, 0.0f, 0.0f);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glDeleteProgram(unShaderProgram1);
	glDeleteProgram(unShaderProgram2);
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
