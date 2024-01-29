

//TEMP
#define DLLPATH  "./src/"
#include "./src/Engine.h"
#include "./src/EntryPoint.h"


#include "TestLayer.h"

class Sandbox :public Engine::Application
{
public:
	Sandbox()
		: Engine::Application()
	{
		ENGI_INFO("create app:Sandbox ");
		PushLayer(new TestLayer());
	}
	~Sandbox()
	{

	}

private:

};


Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}

