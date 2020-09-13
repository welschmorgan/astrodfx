//
// Created by darkboss on 9/13/20.
//

#include "LogManager.h"

namespace quasar {
	namespace core {

		LogManager::LogManager() {
# if QUASAR_SUPPORT_MULTITHREADING
			mThread = std::thread([](LogManager *mgr) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
				mgr->checkFlush();
			}, this);
# endif
		}

		LogManager::~LogManager() {
			flush();
# if QUASAR_SUPPORT_MULTITHREADING
			mThread.join();
# endif
		}

		void LogManager::log(const LogLevel &lvl, const String &msg, const String &channel) {
			if (!hasLogger(channel)) {
				createLogger(channel);
			}
			for (auto const& l: mAdapters) {
				l->append(LogEntry(lvl, channel, msg, std::chrono::system_clock::now()));
			}
		}

		void LogManager::debug(const String &msg, const String &channel) { log(LogLevel::Debug, channel, msg); }

		void LogManager::trace(const String &msg, const String &channel) { log(LogLevel::Trace, channel, msg); }

		void LogManager::info(const String &msg, const String &channel) { log(LogLevel::Info, channel, msg); }

		void LogManager::warn(const String &msg, const String &channel) { log(LogLevel::Warn, channel, msg); }

		void LogManager::error(const String &msg, const String &channel) { log(LogLevel::Error, channel, msg); }

		void LogManager::fatal(const String &msg, const String &channel) { log(LogLevel::Fatal, channel, msg); }

		const Vector<SharedLogAdapter> &LogManager::getAdapters() const noexcept { return mAdapters; }

		void LogManager::setAdapters(const Vector<SharedLogAdapter> &l) noexcept { mAdapters = l; }

		bool LogManager::hasAdapter(const String &name) const noexcept {
			return mAdapters.find([&](const SharedLogAdapter &l) {
				return l->getName() == name;
			}) != mAdapters.end();
		}

		SharedLogAdapter LogManager::getAdapter(const String &name, bool except) const {
			auto found = mAdapters.find([&](const SharedLogAdapter &l) {
				return l->getName() == name;
			});
			if (found == mAdapters.end()) {
				if (except) {
					throw std::runtime_error(std::string(name.begin(), name.end()) + ": unknown log adapter");
				}
				return nullptr;
			}
			return *found;
		}

		SharedLogAdapter LogManager::addAdapter(const SharedLogAdapter &a) {
			if (!a) {
				throw std::runtime_error("cannot add invalid log adapter to LogManager");
			}
			if (hasAdapter(a->getName())) {
				throw std::runtime_error("log adapter '" + std::string(a->getName().begin(), a->getName().end()) + "' already registered");
			}
			for (auto log: mLoggers) {
				log->addAdapter(a);
			}
			mAdapters.add(a);
			return mAdapters->back();
		}

		bool LogManager::hasLogger(const String &name) const noexcept {
			return mLoggers.find([&](const SharedLogger &l) {
				return l->getName() == name;
			}) != mLoggers.end();
		}

		SharedLogger LogManager::getLogger(const String &name, bool except) const {
			auto found = mLoggers.find([&](const SharedLogger &l) {
				return l->getName() == name;
			});
			if (found == mLoggers.end()) {
				if (except) {
					throw std::runtime_error(std::string(name.begin(), name.end()) + ": unknown logger");
				}
				return nullptr;
			}
			return *found;
		}

		void LogManager::setLoggers(const Vector<SharedLogger> &loggers) noexcept { mLoggers = loggers; }

		Vector<SharedLogger> LogManager::getLoggers() const noexcept { return mLoggers; }


		SharedLogger LogManager::addLogger(const SharedLogger &logger) {
			if (!logger) {
				throw std::runtime_error("cannot add invalid log adapter to LogManager");
			}
			if (hasLogger(logger->getName())) {
				throw std::runtime_error("log adapter '" + std::string(logger->getName().begin(), logger->getName().end()) + "' already registered");
			}
			for (auto const& adp: mAdapters) {
				logger->addAdapter(adp);
			}
			mLoggers.add(logger);
			return mLoggers->back();
		}

		void LogManager::clearLoggers() {
			mLoggers.clear();
		}

		void LogManager::checkFlush() {
			for (auto const& adp: mAdapters) {
				if (adp->shouldFlushNow()) {
					adp->flush();
				}
			}
		}

		void LogManager::flush() {
			for (auto const& adapter: mAdapters) {
				adapter->flush();
			}
		}
	}
}