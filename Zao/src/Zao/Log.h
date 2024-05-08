#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Zao {

	class ZAO_API Log
	{
	public:
		Log() {}
		~Log() {}

		static void Init();

		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};
}
