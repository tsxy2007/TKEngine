#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace TK
{
	class TK_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
// Core log macros
#define TK_CORE_TRACE(...)		::TK::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TK_CORE_INFO(...)		::TK::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TK_CORE_WARN(...)		::TK::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TK_CORE_ERROR(...)		::TK::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TK_CORE_CRITICAL(...)	::TK::Log::GetCoreLogger()->critical(__VA_ARGS__)


// Clinet log macros
#define TK_TRACE(...)		::TK::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TK_INFO(...)		::TK::Log::GetClientLogger()->info(__VA_ARGS__)
#define TK_WARN(...)		::TK::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TK_ERROR(...)		::TK::Log::GetClientLogger()->error(__VA_ARGS__)
#define TK_CRITICAL(...)	::TK::Log::GetClientLogger()->critical(__VA_ARGS__)

