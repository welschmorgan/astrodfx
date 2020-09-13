//
// Created by darkboss on 9/13/20.
//

#include "LogLevel.h"

namespace quasar {
	namespace core {
		const LogLevel          LogLevel::Debug(0, "debug", "\033[0m");
		const LogLevel          LogLevel::Trace(1, "trace", "\033[1;30m");
		const LogLevel          LogLevel::Info(2, "info", "\033[1;34m");
		const LogLevel          LogLevel::Warn(3, "warn", "\033[1;33m");
		const LogLevel          LogLevel::Error(4, "error", "\033[1;31m");
		const LogLevel          LogLevel::Fatal(5, "fatal", "\033[48;5;124m");

		LogLevel::LogLevel(const int code, const String &label, const String &color)
			: mCode(code)
			, mLabel(label)
			, mColor(color) {}

		int LogLevel::getCode() const noexcept { return mCode; }

		String LogLevel::getLabel() const noexcept { return mLabel; }

		String LogLevel::getColor() const noexcept { return mColor; }
	}
}