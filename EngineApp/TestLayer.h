//#ifndef _TEST_LAYER_HPP
//#define _TEST_LAYER_HPP


#ifndef _TEST_LAYER_H
#define _TEST_LAYER_H


#include "./src/Engine.h"
#include "imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



	//using namespace Test;

class TestLayer : public Engine::Layer
{
private:
	unsigned int  textureColorbuffer;
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;

public:
	TestLayer()
		:Layer("TextLayer")
	{




	}
	virtual ~TestLayer() = default;

	virtual void OnAttach() override
	{


	}
	virtual void OnDetach() override {}

	virtual void OnUpdate(const Engine::Timestep&) override
	{

		
		Camera camera(glm::vec3(0.7f, 1.0f, 4.0f));
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

		float vertices[] = {
			//position      //normal
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

		VertexBuffer vbo(vertices, 36 * 6 * sizeof(float));
		//
		VertexArray cubeVao;
		VertexBufferLayout cubeLayout;
		cubeLayout.Push<float>(3);//position
		cubeLayout.Push<float>(3);//normal
		cubeVao.AddBuffer(vbo, cubeLayout);





		//
		VertexArray lightVao;
		VertexBufferLayout lightLayout;
		lightLayout.Push<float>(3);
		lightLayout.Skip<float>(3);
		lightVao.AddBuffer(vbo, lightLayout);

		//shader
		Shader lightingShader("res/shaders/lighting.shader");
		Shader lightCubeShader("res/shaders/lightCube.shader");

		//framebuffer
		unsigned int framebuffer;
		unsigned int rbo;
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			ENGI_ERROR("ERROR::FRAMEBUFFER::Framebuffer is not complete!");

		//
		Renderer renderer;


		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST);

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
		/*renderer.SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		renderer.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/


	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Viewport");
		
		ImGui::Image((unsigned int*)textureColorbuffer, {800,600}, { 0,1 }, { 1,0 });
		ImGui::End();
	}



	virtual void OnEvent(Engine::Event& e) override
	{
		//TEMP
		//camera->OnEvent(E);


		//can't  ,it's wrong
		/*ImVec2 windowSize = ImGui::GetWindowSize();
		SCR_WIDTH = windowSize.x;
		SCR_HEIGHT = windowSize.y;*/

		
	}






};

#endif // !_TEST_LAYER_H
