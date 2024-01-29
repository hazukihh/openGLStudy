#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"



namespace Engine
{
	// 初始化为 nullptr
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;


	void Log::Init()
	{
		/*
		* %^ ... %$  : Color Range
		* [%T]		: HH:MM:SS格式的当前时间
		* %n		:  Logger的名字
		* %v		: 实际的文字内容
		*/
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
		//set default level
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

	}



}


