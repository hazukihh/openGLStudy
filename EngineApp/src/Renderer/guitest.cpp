/*
miniTest for imgui

tip:
“temp...” ： 暂时的做法，后续要更改，重构

*/
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <sstream>

#include "Utils.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Render.h"
#include "Texture.h"
#include "Camera.hpp"
#include "ImGuiLayer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>





void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void processInput(GLFWwindow* window);


//settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


// camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera(glm::vec3(0.7f, 1.0f, 4.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


//timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

//lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


// temp...
GLFWwindow* window;
GLFWwindow* GetWindowPtr() { return window; }
//Imgui
ImGuiLayer imguiLayer;
unsigned int  textureColorbuffer;


int main()
{

	//glfwInit函数来初始化GLFW
	glfwInit();
	//glfwWindowHint函数来配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//glfwCreateWindow :create window object
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	//注册回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	

	//glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;


	//-----------------------------------------------------

	{
		// configure global opengl state
		// 
		//Z缓冲,深度测试
		//glEnable(GL_DEPTH_TEST);



		//设置顶点数据（和缓冲区）并配置顶点属性

		float vertices[] = {
			//position      //normal 法向量
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
		};


		VertexArray cubeVao;
		VertexBuffer vbo(vertices, 36 * 6 * sizeof(float));
		VertexBufferLayout cubeLayout;
		cubeLayout.Push<float>(3); //position
		cubeLayout.Push<float>(3);//normal
		cubeVao.AddBuffer(vbo, cubeLayout);

		VertexArray lightVao;
		VertexBufferLayout lightLayout;
		lightLayout.Push<float>(3);
		lightLayout.Skip<float>(3);
		lightVao.AddBuffer(vbo, lightLayout);


		//shader
		Shader lightingShader("res/shaders/lighting.shader");
		//lamp , lightingSource
		Shader lightCubeShader("res/shaders/lightCube.shader");


		unsigned int framebuffer;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		
		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
		

		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);  
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);


		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//绑定0 ->: 解绑
		/*
		vao.Unbind();
		vbo.Unbind();
		shader.Unbind();
		*/

		Renderer renderer;
		
		//ImGui
		imguiLayer.OnAttach();


		

		// render loop :渲染循环
		while (!glfwWindowShouldClose(window))
		{

			/*
			glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、
			 更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
			*/
			glfwPollEvents();



			
			// per-frame time logic
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			// input
			processInput(window);



			//render
			//------
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
			glEnable(GL_DEPTH_TEST);

			


			//clear screen
			renderer.SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			renderer.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



			lightingShader.Bind();
			lightingShader.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
			lightingShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
			lightingShader.SetVec3("lightPos", lightPos);
			lightingShader.SetVec3("viewPos", camera.GetPosition());

			glm::mat4 projection = glm::perspective(
				glm::radians(camera.GetZoom()),
				(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			glm::mat4 view = camera.GetViewMatrix();
			glm::mat4 model = glm::mat4(1.0f);

			lightingShader.SetMat4("projection", projection);
			lightingShader.SetMat4("view", view);
			lightingShader.SetMat4("model", model);

			renderer.Draw(cubeVao, lightingShader, 0, 36);

			lightCubeShader.Bind();
			lightCubeShader.SetMat4("projection", projection);
			lightCubeShader.SetMat4("view", view);
			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f));
			lightCubeShader.SetMat4("model", model);

			renderer.Draw(lightVao, lightCubeShader, 0, 36);



			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			renderer.SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			renderer.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			//imgui
			imguiLayer.Begin();
			imguiLayer.OnImGuiRender([]()
			{
				{
					ImGui::Begin("Viewport");
					static glm::vec2 m_LastViewportSize(SCR_WIDTH, SCR_HEIGHT);
					/*std::stringstream ss1;
					ss1 << "lastViewSize:" << "x:" << m_LastViewportSize.x
						<< "y:" << m_LastViewportSize.y;
					ImGui::Text(ss1.str().c_str());*/


					ImVec2 size = ImGui::GetContentRegionAvail();
					glm::vec2 viewportSize = { size.x, size.y };
					/*std::stringstream ss2;
					ss2 << "viewportSize:" << "x:" << viewportSize.x
						<< "y:" << viewportSize.y;
					ImGui::Text(ss2.str().c_str());*/
					if (viewportSize != m_LastViewportSize)
					{
						/*ImGui::Text("!=");
						std::cout << "!=\n";*/
						glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewportSize.x, viewportSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

					}
					ImGui::Image((unsigned int*)textureColorbuffer, size, { 0,1 }, { 1,0 });
					m_LastViewportSize = viewportSize;

					ImGui::End();


				}



				{
					ImGui::Begin("Config?");
					if (ImGui::CollapsingHeader("GLFW"))
					{
						if (ImGui::TreeNode("InputMode"))
						{
							const char* items[] = { "GLFW_CURSOR_NORMAL","GLFW_CURSOR_HIDDEN","GLFW_CURSOR_DISABLED" };
							static int current_item_id = 0;
							int last_item_id = current_item_id;
							ImGui::Combo("Cursor", &current_item_id, items, IM_ARRAYSIZE(items));
							if (current_item_id != last_item_id)
							{

								glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL + current_item_id);
							}
							ImGui::TreePop();
						}
						if (ImGui::TreeNode("Variable"))
						{
							glm::vec3 cameraPosition = camera.GetPosition();
							std::stringstream ss;
							ss << std::string("x:") << cameraPosition.x
								<< std::string("y:") << cameraPosition.y
								<< std::string("z:") << cameraPosition.z;
							ImGui::Text(ss.str().c_str());
							ImGui::TreePop();
						}
					}
					ImGui::End();

				}
			});
			
			imguiLayer.End();

			/*
			glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），
			它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
			*/
			glfwSwapBuffers(window);
			


		}

		glDeleteRenderbuffers(1, &rbo);
		glDeleteFramebuffers(1, &framebuffer);


	}


	imguiLayer.OnDetach();
	glfwDestroyWindow(window);
	//glfw: 终止，清除所有先前分配的GLFW资源。
	glfwTerminate();

	return 0;


}

void processInput(GLFWwindow* window)
{
	//检测按下Esc键关闭窗口
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL );
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL+1);
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL +2);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.ProcessKeyboard(CameraMovement::DOWN, deltaTime);



}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//OpenGL渲染窗口的尺寸大小，即视口(Viewport)
	//通过调用glViewport函数来设置窗口的维度(Dimension)：
	//前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）
	//glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}