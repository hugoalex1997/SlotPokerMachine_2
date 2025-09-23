
#include "logger.hpp"
#include "filesystem.hpp"

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace sdk {

	namespace {
		inline decltype(auto) CreateLogger(const LoggerConfig& config) {
			auto logger = std::make_shared<spdlog::logger>(config.name);

			if (config.console) {
				auto console = std::make_shared<spdlog::sinks::stdout_color_sink_st>();

				logger->sinks().emplace_back(std::move(console));
			}

			if (!config.file.empty()) {
				auto log = (sdk::fs::GetLogsPath() / config.file).string();

				auto file = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log, false);

				logger->sinks().emplace_back(std::move(file));
			}

			{  // main log file - always created
				auto mainLog = sdk::fs::GetMainLogPath().string();

				auto mainFile = std::make_shared<spdlog::sinks::basic_file_sink_mt>(mainLog, false);

				logger->sinks().emplace_back(std::move(mainFile));
			}

			return logger;
		}
	}  // namespace

	std::shared_ptr<spdlog::logger> Logger::Create(const LoggerConfig& config) {
		if (auto logger = Get(config.name)) {
			MainLogWarn("Logger '{}' already exists", config.name);
			return logger;	// Already exists
		}

		spdlog::flush_every(std::chrono::seconds(1));

		auto logger = CreateLogger(config);

		spdlog::register_logger(logger);

		MainLogInfo("Logger '{}' created", config.name);

		return logger;
	}

	bool Logger::Destroy(const std::string& name) {
		if (auto logger = Get(name)) {
			spdlog::drop(name);
			return true;
		}

		MainLogWarn("Logger '{}' does not exist", name);
		return false;
	}

	bool Logger::SetDefaultLogger(const std::string& name) {
		if (auto logger = Get(name)) {
			spdlog::set_default_logger(logger);
			return true;
		}

		MainLogWarn("Logger '{}' does not exist", name);
		return false;
	}

	void Logger::Shutdown() {
		spdlog::drop_all();
		spdlog::shutdown();
	}
}  // namespace sdk
