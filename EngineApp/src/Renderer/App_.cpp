/* 
version 1.0
*/
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>



#include "Utils.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Render.h"
#include "Texture.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// something var
float r = 0.0f;

int main()
{

	//glfwInit函数来初始化GLFW
	glfwInit();
	//glfwWindowHint函数来配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	//glfwCreateWindow :create window object
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(5);

	//注册一个回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	//-----------------------------------------------------

	{
		//设置顶点数据（和缓冲区）并配置顶点属性
	
		float vertices[] = {
			// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};

		
		unsigned int indices[] = {
			0,1,3,
			1,2,3
		};
		// VBO: vertex buffer object 顶点缓冲对象
		// VAO: vertex array object 顶点数组对象

		//先绑定顶点数组对象，然后绑定并设置顶点缓冲区，再配置顶点属性。
		VertexArray vao;
		VertexBuffer vbo(vertices, 4 * 8 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3); //position
		layout.Push<float>(3); //color
		layout.Push<float>(2); //texture
		vao.AddBuffer(vbo, layout);
		
		IndexBuffer ibo(indices, 6);

		//Texture texture1("res/textures/0202.jpg");
		Texture texture1("res/textures/container.jpg");
		Texture texture2("res/textures/awesomeface.png");
		
		


		//shader
		Shader shader("res/shaders/mvp1.shader");
		shader.Bind();
		shader.SetInt("texture1", 0);
		shader.SetInt("texture2", 1);
		
		
		
		//绑定0 ->: 解绑
		vao.Unbind();
		vbo.Unbind();
		ibo.Unbind();
		shader.Unbind();

		Renderer renderer;

		

		// render loop :渲染循环
		while (!glfwWindowShouldClose(window))
		{


			processInput(window);

			//render

			//clear screen
			renderer.Clear(0.2f, 0.3f, 0.3f, 1.0f);

			//Texture

			texture1.Bind(0);
			texture2.Bind(1);

			// transformations
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

			


			shader.Bind();
			
			
			shader.SetMat4("model", model);
			shader.SetMat4("view", view);
			shader.SetMat4("projection", projection);
			shader.SetFloat("r", r);
			
			
			vao.Bind();
			ibo.Bind();

			renderer.Draw(vao,ibo,shader);

			

			/*
			glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
			它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
			*/
			glfwSwapBuffers(window);

			/*
			glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、
			 更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
			*/
			glfwPollEvents();


		}
		
	}

    //glfw: 终止，清除所有先前分配的GLFW资源。
	glfwTerminate();
	return 0;


}

void processInput(GLFWwindow* window)
{
	//检测按下Esc键关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		r += 0.05f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		r -= 0.05f;
	}


}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//OpenGL渲染窗口的尺寸大小，即视口(Viewport)
	//通过调用glViewport函数来设置窗口的维度(Dimension)：
	//前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
	glViewport(0, 0, width, height);
}