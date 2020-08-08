#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void frambuffer_size_callback(GLFWwindow* pWindow,int nWidth,int nHeight);
void processInput(GLFWwindow* pWindow);

//������ɫ��
const char * pVertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 apos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(apos.x, apos.y, apos.z, 1.0);\n"
"}\n";

//Ƭ����ɫ��
const char* pFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

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

	//���������붥����ɫ��
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

	//����������Ƭ����ɫ��
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

	//������ɫ������
	unsigned int unShaderProgram;
	unShaderProgram = glCreateProgram();
	//������ɫ��
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
	//������ɣ�ɾ��Shader
	glDeleteShader(unVertexShader);
	glDeleteShader(unFragmentShader);

	//��������
	float vertices[] = {
		0.5f, 0.5f, 0.0f, //���Ͻ�
		0.5f, -0.5f, 0.0f,//���½�
		-0.5f, -0.5f, 0.0f,//���½�
		-0.5f, 0.5f, 0.0f//���Ͻ�
	};

	//������������
	unsigned int unIndices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO,VBO,EBO;
	glGenVertexArrays(1, &VAO);//����һ��VAO
	glGenBuffers(1, &VBO);//����һ��VBO�������
	glGenBuffers(1, &EBO);//����һ��EBO	

	glBindVertexArray(VAO);//��VAO
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//���������󶨵�GL_ARRAY_BUFFRĿ����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���û����ݸ��Ƶ��󶨵Ļ�����

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unIndices), unIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);//���ö�������
	glEnableVertexAttribArray(0);//�Զ�������λ����Ϊ������������������

	glBindBuffer(GL_ARRAY_BUFFER,0);//���VBO
	glBindVertexArray(0);//���VAO

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(pWindow))//���glfw�Ƿ�Ҫ���˳�
	{
		processInput(pWindow);

		//��Ⱦָ��
		glClearColor(0.2f,0.3f,0.3f,1.0f);//���������ɫ״̬��Ϣ
		glClear(GL_COLOR_BUFFER_BIT);//ʹ�������ɫ

		glUseProgram(unShaderProgram);//ʹ����ɫ������
		glBindVertexArray(VAO);//�󶨶���
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//���ð�������������л���
		//glDrawArrays(GL_TRIANGLES, 0, 3);//���û��Ʒ�ʽ�Ͷ�����ʼλ�ü�����

		/*������ɫ���壬������GLFW���ڵ�ÿ��������ɫֵ�Ļ��棬����
		һ�����б��������ƣ����ҽ���Ϊ�����ʾ����Ļ��*/
		glfwSwapBuffers(pWindow);
		glfwPollEvents();//����Ƿ����¼�����
	}

	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
	glDeleteProgram(unShaderProgram);

	glfwTerminate();//�ͷŷ�����Դ
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