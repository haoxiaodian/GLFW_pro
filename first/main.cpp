#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void frambuffer_size_callback(GLFWwindow* pWindow,int nWidth,int nHeight);
void processInput(GLFWwindow* pWindow);

//顶点着色器
const char * pVertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 apos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(apos.x, apos.y, apos.z, 1.0);\n"
"}\n";

//片段着色器
const char* pFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

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

	//创建并编译顶点着色器
	unsigned int unVertexShader;
	unVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(unVertexShader,1,&pVertexShaderSource,NULL);
	glCompileShader(unVertexShader);

	int nSuccess;
	char cInfoLog[512] = {0};
	glGetShaderiv(unVertexShader,GL_COMPILE_STATUS,&nSuccess);
	if (!nSuccess)
	{
		glGetShaderInfoLog(unVertexShader,512,NULL,cInfoLog);
		std::cout <<"ERROR::SHADER::VERTEX::COMPILE_FAILE\n"<< cInfoLog << std::endl;
	}

	//创建并编译片段着色器
	unsigned int unFragmentShader;
	unFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(unFragmentShader,1,&pFragmentShaderSource,NULL);
	glCompileShader(unFragmentShader);
	int nSuccess1;
	char cInforLog1[512] = { 0 };
	glGetShaderiv(unFragmentShader,GL_COMPILE_STATUS,&nSuccess1);
	if (!nSuccess1)
	{
		glGetShaderInfoLog(unFragmentShader,512,NULL,cInforLog1);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILE\n" << cInforLog1 << std::endl;
	}

	//创建着色器程序
	unsigned int unShaderProgram;
	unShaderProgram = glCreateProgram();
	//连接着色器
	glAttachShader(unShaderProgram,unVertexShader);
	glAttachShader(unShaderProgram, unFragmentShader);
	glLinkProgram(unShaderProgram);

	int unSuccess2;
	char cInfoLog2[512] = { 0 };
	glGetProgramiv(unShaderProgram,GL_LINK_STATUS,&unSuccess2);
	if (!unSuccess2)
	{
		glGetProgramInfoLog(unShaderProgram, 512, NULL, cInfoLog2);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILE_FAILE\n" << cInfoLog2 << std::endl;
	}
	//编译完成，删除Shader
	glDeleteShader(unVertexShader);
	glDeleteShader(unFragmentShader);

	//顶点数组
	float vertices[] = {
		0.5f, 0.5f, 0.0f, //右上角
		0.5f, -0.5f, 0.0f,//右下角
		-0.5f, -0.5f, 0.0f,//左下角
		-0.5f, 0.5f, 0.0f//左上角
	};

	//顶点链接索引
	unsigned int unIndices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO,VBO,EBO;
	glGenVertexArrays(1, &VAO);//创建一个VAO
	glGenBuffers(1, &VBO);//创建一个VBO缓存对象
	glGenBuffers(1, &EBO);//创建一个EBO	

	glBindVertexArray(VAO);//绑定VAO
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//将缓冲对象绑定到GL_ARRAY_BUFFR目标上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将用户数据复制到绑定的缓冲中

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unIndices), unIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);//设置顶点属性
	glEnableVertexAttribArray(0);//以顶点属性位置作为参数，启动顶点属性

	glBindBuffer(GL_ARRAY_BUFFER,0);//解绑定VBO
	glBindVertexArray(0);//解绑定VAO

	//渲染循环
	while (!glfwWindowShouldClose(pWindow))//检查glfw是否要求被退出
	{
		processInput(pWindow);

		//渲染指令
		glClearColor(0.2f,0.3f,0.3f,1.0f);//设置清除颜色状态信息
		glClear(GL_COLOR_BUFFER_BIT);//使用清除颜色

		glUseProgram(unShaderProgram);//使用着色器程序
		glBindVertexArray(VAO);//绑定顶点
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//设置按照索引缓存进行绘制
		//glDrawArrays(GL_TRIANGLES, 0, 3);//设置绘制方式和顶点起始位置及数量

		/*交换颜色缓冲，它存着GLFW窗口的每个像素颜色值的缓存，在这
		一迭代中被用来绘制，并且将作为输出显示在屏幕上*/
		glfwSwapBuffers(pWindow);
		glfwPollEvents();//检查是否有事件触发
	}

	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteProgram(unShaderProgram);

	glfwTerminate();//释放分配资源
	return 0;
}

void frambuffer_size_callback(GLFWwindow* pWindow, int nWidth, int nHeight)
{
	glViewport(0, 0, 800, 600);
}

void processInput(GLFWwindow* pWindow)
{
	if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
}