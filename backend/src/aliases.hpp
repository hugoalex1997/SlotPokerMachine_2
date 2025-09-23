#pragma once
#include "sdk/logger.hpp"

//======================== Backend Logger Macros ========================//

#define LogTrace(...) sdk::Logger::GetBackendLogger()->Trace(__VA_ARGS__)
#define LogDebug(...) sdk::Logger::GetBackendLogger()->Debug(__VA_ARGS__)
#define LogInfo(...) sdk::Logger::GetBackendLogger()->Info(__VA_ARGS__)
#define LogWarn(...) sdk::Logger::GetBackendLogger()->Warn(__VA_ARGS__)
#define LogError(...) sdk::Logger::GetBackendLogger()->Error(__VA_ARGS__)
#define LogCritical(...) sdk::Logger::GetBackendLogger()->Critical(__VA_ARGS__)

//========================================================================//
