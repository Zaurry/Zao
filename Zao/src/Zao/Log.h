#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h" //enable to log custom type 但没起卵用

namespace Zao {

	class ZAO_API Log
	{
	public:
		Log() {}
		~Log() {}

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}

//CoreLogger Macros
#define ZAO_CORE_TRACE(...)	    ::Zao::Log::getCoreLogger()->trace(__VA_ARGS__)
#define ZAO_CORE_DEBUG(...)	    ::Zao::Log::getCoreLogger()->debug(__VA_ARGS__)
#define ZAO_CORE_INFO(...)	    ::Zao::Log::getCoreLogger()->info(__VA_ARGS__)
#define ZAO_CORE_WARN(...)	    ::Zao::Log::getCoreLogger()->warn(__VA_ARGS__)
#define ZAO_CORE_ERRER(...)	    ::Zao::Log::getCoreLogger()->error(__VA_ARGS__)
#define ZAO_CORE_CRITICAL(...)  ::Zao::Log::getCoreLogger()->critical(__VA_ARGS__)

//ClientLogger Macros
#define ZAO_TRACE(...)	    ::Zao::Log::getClientLogger()->trace(__VA_ARGS__)
#define ZAO_DEBUG(...)	    ::Zao::Log::getClientLogger()->debug(__VA_ARGS__)
#define ZAO_INFO(...)	    ::Zao::Log::getClientLogger()->info(__VA_ARGS__)
#define ZAO_WARN(...)	    ::Zao::Log::getClientLogger()->warn(__VA_ARGS__)
#define ZAO_ERRER(...)	    ::Zao::Log::getClientLogger()->error(__VA_ARGS__)
#define ZAO_CRITICAL(...)   ::Zao::Log::getClientLogger()->critical(__VA_ARGS__)