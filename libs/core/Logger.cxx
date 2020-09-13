//
// Created by darkboss on 9/13/20.
//

#include "Logger.h"

namespace quasar {
	namespace core {
		Logger::Logger(const String &name)
				: mName(name), mAdapters() {}

		void Logger::log(const LogLevel &lvl, const String &msg) {
			for (auto const& l: mAdapters) {
				l->append(LogEntry(lvl, mName, msg));
			}
		}

		void Logger::debug(const String &msg) { log(LogLevel::Debug, msg); }

		void Logger::trace(const String &msg) { log(LogLevel::Trace, msg); }

		void Logger::info(const String &msg) { log(LogLevel::Info, msg); }

		void Logger::warn(const String &msg) { log(LogLevel::Warn, msg); }

		void Logger::error(const String &msg) { log(LogLevel::Error, msg); }

		void Logger::fatal(const String &msg) { log(LogLevel::Fatal, msg); }

		void Logger::setName(const String &name) { mName = name; }

		const String &Logger::getName() const noexcept { return mName; }

		bool Logger::hasAdapter(const String &name) {
			auto found = mAdapters.find([&](const SharedLogAdapter &a) {
				return a->getName() == name;
			});
			return found != mAdapters.end();
		}

		const Logger::log_adapter_list &Logger::getAdapters() const noexcept { return mAdapters; }

		void Logger::setAdapters(const Logger::log_adapter_list &l) noexcept { mAdapters = l; }

		SharedLogAdapter Logger::addAdapter(const SharedLogAdapter &a) { mAdapters.add(a); return mAdapters->back(); }

		void Logger::clearAdapters() { mAdapters.clear(); }

		void Logger::flush() {
			for (auto const& adapter: mAdapters) {
				adapter->flush();
			}
		}
	}
}