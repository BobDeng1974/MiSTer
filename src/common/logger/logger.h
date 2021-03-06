#ifndef COMMON_LOGGER_LOGGER_H_
#define COMMON_LOGGER_LOGGER_H_

#include <chrono>

#define MAX_LOG_MESSAGE_LENGTH 4096

// Shortcuts
#define LOGINFO(format, ...) logger::info(format, ##__VA_ARGS__)
#define LOGWARN(format, ...) logger::warning(format, ##__VA_ARGS__)
#define LOGERROR(format, ...) logger::error(format, ##__VA_ARGS__)

#define LOGINFOLN(format, ...) logger::info(format, ##__VA_ARGS__); logger::log("\n")
#define LOGWARNLN(format, ...) logger::warning(format, ##__VA_ARGS__); logger::log("\n")
#define LOGERRORLN(format, ...) logger::error(format, ##__VA_ARGS__); logger::log("\n")

#define LOGSYSTEMERROR() logger::error("%s\n", logger::geterror())

#ifdef _ENABLE_DEBUG
#define DEBUG(format, ...) logger::debug(format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif


#ifdef _ENABLE_TRACE
#define TRACE(format, ...) logger::trace(format, ##__VA_ARGS__)
#else
#define TRACE(format, ...)
#endif

// Reference application start time (monotonic clock value, recorded immediately after application start)
extern std::chrono::steady_clock::time_point applicationStart;

class logger
{
private:
	// Preallocate message buffer
	static char buffer[MAX_LOG_MESSAGE_LENGTH];

	static void log();

public:
	static void log(const char* message);

	static void info(const char* format, ...);
	static void warning(const char* format, ...);
	static void error(const char* format, ...);

	static void debug(const char* format, ...);
	static void trace(const char* format, ...);

	// System errors processing helpers
	static char* geterror();

private:
	/// Static class, disallow objects creation
	logger();
};

#endif /* COMMON_LOGGER_LOGGER_H_ */
