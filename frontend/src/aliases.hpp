#pragma once
#include "sdk/logger.hpp"

//======================== Frontend Logger Macros ========================//

#define LogTrace(...) sdk::Logger::GetFrontendLogger()->Trace(__VA_ARGS__)
#define LogDebug(...) sdk::Logger::GetFrontendLogger()->Debug(__VA_ARGS__)
#define LogInfo(...) sdk::Logger::GetFrontendLogger()->Info(__VA_ARGS__)
#define LogWarn(...) sdk::Logger::GetFrontendLogger()->Warn(__VA_ARGS__)
#define LogError(...) sdk::Logger::GetFrontendLogger()->Error(__VA_ARGS__)
#define LogCritical(...) sdk::Logger::GetFrontendLogger()->Critical(__VA_ARGS__)

//========================================================================//