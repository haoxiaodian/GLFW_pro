#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* pWindow,int nWidth,int nHeight);
void processInput(GLFWwindow*pWindow);

//������ɫ��
const char * pVertexShader = "#version 330 core\n"
"layout(location = 0) in vec3 apos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(apos.x,apos.y,apos.z,1.0f);\n"
"}\n";

//Ƭ����ɫ��
const char * pFragmentShader = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* pWindow = glfwCreateWindow(800, 600, "exersize1", NULL, NULL);
	if (!pWindow)
	{
		std::cout << "ERROR::OPENGL::CREATE_WINDOW_FAILE" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(pWindow);//���õ�ǰ����������
	glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);//ע��ص�����

	//ʹ��GLAD��ʼ��OPENGL
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "ERROR::OPENGL::GLAD_INIT_FAILE" << std::endl;
		glfwTerminate();
		return -1;
	}

	//���������붥����ɫ��
	unsigned int unVertexShader = 0;
	unVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(unVertexShader,1, &pVertexShader,NULL);
	glCompileShader(unVertexShader);

	int nSuccess;
	char cInfoLog[512] = { 0 };
	glGetShaderiv(unVertexShader,GL_COMPILE_STATUS,&nSuccess);
	if (!nSuccess)
	{
		glGetShaderInfoLog(unVertexShader,512,NULL,cInfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE_FAILE\n"<<cInfoLog<<std::endl;
	}

	//����������Ƭ����ɫ��
	unsigned int unFragmentShader = 0;
	unFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(unFragmentShader,1,&pFragmentShader,NULL);
	glCompileShader(unFragmentShader);

	int nSuccess1;
	char cInfoLog1[512] = {0};
	glGetShaderiv(unFragmentShader,GL_COMPILE_STATUS,&nSuccess1);
	if (!nSuccess1)
	{
		glGetShaderInfoLog(unFragmentShader,512,NULL,cInfoLog1);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILE_FAILE\n" << cInfoLog1 << std::endl;
	}

	//������ɫ������
	unsigned int unShaderProgram = 0;
	unShaderProgram = glCreateProgram();
	glAttachShader(unShaderProgram,unVertexShader);
	glAttachShader(unShaderProgram, unFragmentShader);
	glLinkProgram(unShaderProgram);

	int nSuccess2;
	char cInfoLog2[512] = { 0 };
	glGetProgramiv(unShaderProgram,GL_LINK_STATUS,&nSuccess2);
	if (!nSuccess2)
	{
		glGetProgramInfoLog(unShaderProgram,512,NULL,cInfoLog2);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILE\n" << cInfoLog2 << std::endl;
	}

	//������ɣ�ɾ����ɫ��
	glDeleteShader(unVertexShader);
	glDeleteShader(unFragmentShader);

	float vertices[] = {
		//��һ��������
		-0.5f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		//�ڶ���������
		0.5f,0.5f,0.0f,
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1,&VBO);

	glBindVertexArray(VAO);//�󶨶����������
	glBindBuffer(GL_ARRAY_BUFFER,VBO);//�󶨶��㻺�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_COPY);

	//���ö�������
	/*
		ÿ������ʹ������float���ֽ�����ʾ���ӵ�0��λ�ÿ�ʼ������׼������
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);//ʹ�ö�����ʼλ����Ϊ���������ö�������

	glBindBuffer(GL_ARRAY_BUFFER, 0);//���VBO
	glBindVertexArray(0);//���VAO

	while (!glfwWindowShouldClose(pWindow))//��ⴰ���Ƿ���Ҫ���ر�
	{
		processInput(pWindow);
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//ʹ��SHADER
		glUseProgram(unShaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,6);//�ӵ�0��λ�ÿ�ʼ������6����

		glfwSwapBuffers(pWindow);//��������Ƶ�������
		glfwPollEvents();//����Ƿ����¼�����
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* pWindow, int nWidth, int nHeight)
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
