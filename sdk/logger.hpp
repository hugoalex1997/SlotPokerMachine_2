#pragma once
#include <spdlog/spdlog.h>

//======================== Logger instance macros ========================//

#define __LogSourceLoc \
	spdlog::source_loc { __FILE__, __LINE__, static_cast<const char*>(__FUNCTION__) }

#define Trace(...) log(__LogSourceLoc, spdlog::level::trace, __VA_ARGS__)
#define Debug(...) log(__LogSourceLoc, spdlog::level::debug, __VA_ARGS__)
#define Info(...) log(__LogSourceLoc, spdlog::level::info, __VA_ARGS__)
#define Warn(...) log(__LogSourceLoc, spdlog::level::warn, __VA_ARGS__)
#define Error(...) log(__LogSourceLoc, spdlog::level::err, __VA_ARGS__)
#define Critical(...) log(__LogSourceLoc, spdlog::level::critical, __VA_ARGS__)

//======================== Main instance logger macros ========================//

#define MainLogTrace(...) sdk::Logger::Get()->Trace(__VA_ARGS__)
#define MainLogDebug(...) sdk::Logger::Get()->Debug(__VA_ARGS__)
#define MainLogInfo(...) sdk::Logger::Get()->Info(__VA_ARGS__)
#define MainLogWarn(...) sdk::Logger::Get()->Warn(__VA_ARGS__)
#define MainLogError(...) sdk::Logger::Get()->Error(__VA_ARGS__)
#define MainLogCritical(...) sdk::Logger::Get()->Critical(__VA_ARGS__)

//========================================================================//

namespace sdk {
	enum class LoggingLevel : std::uint8_t {
		Trace = spdlog::level::trace,
		Debug = spdlog::level::debug,
		Info = spdlog::level::info,
		Warn = spdlog::level::warn,
		Error = spdlog::level::err,
		Critical = spdlog::level::critical,
		Off = spdlog::level::off,
	};

	struct LoggerConfig {
		std::string name;
		bool console{false};
		std::string file;
	};

	class Logger {
	public:
		using RefT = std::shared_ptr<spdlog::logger>;

		static decltype(auto) Get() {
			return spdlog::default_logger();  //
		}

		static decltype(auto) Get(const std::string& name) {
			return spdlog::get(name);  //
		}

		static decltype(auto) GetFrontendLogger() {
			auto logger = Get("__frontend__");

			if (!logger) {
				sdk::LoggerConfig config{"__frontend__"};
				config.console = true;
				config.file = "frontend.log";

				Create(config);
				SetDefaultLogger(config.name);

				return Get("__frontend__");
			}
			return logger;
		}

		static decltype(auto) GetBackendLogger() {
			auto logger = Get("__backend__");

			if (!logger) {
				sdk::LoggerConfig config{"__backend__"};
				config.console = true;
				config.file = "backend.log";

				Create(config);
				return Get("__backend__");
			}
			return logger;
		}

		static std::shared_ptr<spdlog::logger> Create(const LoggerConfig& config);

		static bool Destroy(const std::string& name);

		static bool SetDefaultLogger(const std::string& name);

		static void Shutdown();
	};
}  // namespace sdk