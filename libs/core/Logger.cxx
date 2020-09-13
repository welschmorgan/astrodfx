//
// Created by darkboss on 9/13/20.
//

#include "Logger.h"

namespace quasar {
	namespace core {
		const LogLevel LogLevel::Debug(0, "debug");
		const LogLevel LogLevel::Trace(1, "trace");
		const LogLevel LogLevel::Info(2, "info");
		const LogLevel LogLevel::Warn(3, "warn");
		const LogLevel LogLevel::Error(4, "error");
		const LogLevel LogLevel::Fatal(5, "fatal");

		const String    LogAdapter::DefaultFormat("[{t}] [{c}] {l} - {m}");
	}
}