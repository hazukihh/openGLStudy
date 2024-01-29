#pragma once

#include <memory>

#include "spdlog/spdlog.h"


namespace Engine
{
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}


	};

}

//Log Macros

#define ENGI_CORE_TRACE(...)	::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGI_CORE_INFO(...)	::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGI_CORE_WARN(...)	::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGI_CORE_ERROR(...)	::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGI_CORE_FATAL(...)	::Engine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define ENGI_TRACE(...)	::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGI_INFO(...)	::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGI_WARN(...)	::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGI_ERROR(...)	::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENGI_FATAL(...)	::Engine::Log::GetClientLogger()->fatal(__VA_ARGS__)