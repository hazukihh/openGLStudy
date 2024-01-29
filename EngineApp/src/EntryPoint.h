#pragma once

#include "Application.h"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();

	ENGI_CORE_WARN("Initialized Log");


	//auto app = Engine::CreateApplication({ argc, argv });
	auto app = Engine::CreateApplication();

	app->Run();

	delete app;
}