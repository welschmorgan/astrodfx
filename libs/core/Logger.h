//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGGER_H
#define QUASARFX_LOGGER_H

#include <iostream>
#include "String.h"
#include "Collection.h"

namespace quasar {
	namespace core {
		class LogLevel {
		public:
			static const LogLevel Debug;
			static const LogLevel Trace;
			static const LogLevel Info;
			static const LogLevel Warn;
			static const LogLevel Error;
			static const LogLevel Fatal;

		protected:
			int             mCode;
			String          mLabel;

			LogLevel(const int code, const String &label)
				: mCode(code)
				, mLabel(label)
			{}

		public:
			LogLevel(const LogLevel &rhs) = default;
			~LogLevel() noexcept = default;

			LogLevel        &operator=(const LogLevel &rhs) = default;

			int             getCode() const noexcept { return mCode; }
			String          getLabel() const noexcept { return mLabel; }
		};

		class LogEntry {
			LogLevel        mLevel;
			String          mChannel;
			String          mTimestamp;
			String          mMessage;
		public:
			LogEntry(const LogLevel &level, const String &channel, const String &message, const String &timestamp)
				: mLevel(level), mChannel(channel), mMessage(message), mTimestamp(timestamp)
			{}
			LogEntry(const LogEntry &rhs) = default;
			~LogEntry() = default;

			LogEntry      &operator=(const LogEntry &rhs) = default;

			const LogLevel &getLevel() const {
				return mLevel;
			}

			void setLevel(const LogLevel &level) {
				mLevel = level;
			}

			const String &getChannel() const {
				return mChannel;
			}

			void setChannel(const String &channel) {
				mChannel = channel;
			}

			const String &getTimestamp() const {
				return mTimestamp;
			}

			void setTimestamp(const String &timestamp) {
				mTimestamp = timestamp;
			}

			const String &getMessage() const {
				return mMessage;
			}

			void setMessage(const String &message) {
				mMessage = message;
			}
		};

		class LogAdapter {
		public:
			static const String     DefaultFormat;
		protected:
			String          mName;
			String          mFormat;
		public:
			LogAdapter(const String &name = String()): mName(name), mFormat(DefaultFormat) {}
			LogAdapter(const LogAdapter &rhs) = default;
			virtual ~LogAdapter() = default;

			LogAdapter      &operator=(const LogAdapter &rhs) = default;

			const String    &getName() const noexcept { return mName; }

			const String    &getFormat() const noexcept { return mFormat; }
			void            setFormat(const String &f) noexcept { mFormat = f; }

			PropertyMap     getFormatVars(const LogEntry &e) const noexcept {
				return Map<String, String>({
					{"{t}", e.getTimestamp()},
					{"{l}", e.getLevel().getLabel()},
					{"{m}", e.getMessage()},
					{"{c}", e.getChannel()},
				});
			}

			String          format(const LogEntry &e) {
				String ret = mFormat;
				size_t pos;
				for (auto const &d: getFormatVars(e)) {
					if ((pos = ret.find(d.first)) != String::npos) {
						ret.replace(pos, d.first.size(), d.second);
					}
				}
				return ret;
			}

			virtual void    flush() = 0;
			virtual void    append(const LogEntry &e) = 0;
		};

		using SharedLogAdapter = std::shared_ptr<LogAdapter>;

		class Logger {
		public:
			using log_adapter_list  = Vector<SharedLogAdapter>;

		protected:
			String                  mName;
			log_adapter_list        mAdapters;
		public:
			Logger(const String &name = String()): mName(name) {}
			Logger(const Logger &rhs) = default;
			~Logger() = default;

			Logger                  &operator=(const Logger &rhs) = default;

			void                    log(const LogLevel &lvl, const String &msg) {
				for (auto const& l: mAdapters) {
					l->append(LogEntry(lvl, mName, msg, "19:20:13"));
				}
			}
			void                    debug(const String &msg) { log(LogLevel::Debug, msg); }
			void                    trace(const String &msg) { log(LogLevel::Trace, msg); }
			void                    info(const String &msg) { log(LogLevel::Info, msg); }
			void                    warn(const String &msg) { log(LogLevel::Warn, msg); }
			void                    error(const String &msg) { log(LogLevel::Error, msg); }
			void                    fatal(const String &msg) { log(LogLevel::Fatal, msg); }

			void                    setName(const String &name) { mName = name; }
			const String            &getName() const noexcept { return mName; }

			bool                    hasAdapter(const String &name) {
				auto found = mAdapters.find([&](const SharedLogAdapter &a) {
					return a->getName() == name;
				});
				return found != mAdapters.end();
			}
			const log_adapter_list  &getAdapters() const noexcept { return mAdapters; }
			void                    setAdapters(const log_adapter_list &l) noexcept { mAdapters = l; }
			SharedLogAdapter        addAdapter(const SharedLogAdapter &a) { mAdapters.add(a); return mAdapters->back(); }
			void                    clearAdapters() { mAdapters.clear(); }
		};

		using SharedLogger = std::shared_ptr<Logger>;

		class LogManager {
		protected:
			Vector<SharedLogAdapter>    mAdapters;
			Vector<SharedLogger>        mLoggers;
		public:
			LogManager() = default;
			LogManager(const LogManager &rhs) = default;
			virtual ~LogManager() = default;

			LogManager      &operator=(const LogManager &rhs) = default;

			const Vector<SharedLogAdapter> &getAdapters() const noexcept { return mAdapters; }
			void                    setAdapters(const Vector<SharedLogAdapter> &l) noexcept { mAdapters = l; }
			bool                    hasAdapter(const String &name) const noexcept {
				return mAdapters.find([&](const SharedLogAdapter &l) {
					return l->getName() == name;
				}) != mAdapters.end();
			}

			SharedLogAdapter        getAdapter(const String &name, bool except = true) const {
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
			template<typename T, typename ...Args>
			SharedLogAdapter        createAdapter(Args ...args) {
				auto inst = std::make_shared<T>(args...);
				return addAdapter(std::dynamic_pointer_cast<LogAdapter>(inst));
			}
			SharedLogAdapter        addAdapter(const SharedLogAdapter &a) {
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
			void                    clearAdapters() { mAdapters.clear(); }

			bool                    hasLogger(const String &name) const noexcept {
				return mLoggers.find([&](const SharedLogger &l) {
					return l->getName() == name;
				}) != mLoggers.end();
			}
			SharedLogger            getLogger(const String &name, bool except = true) const {
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
			void                    setLoggers(const Vector<SharedLogger> &loggers) noexcept { mLoggers = loggers; }
			Vector<SharedLogger>    getLoggers() const noexcept { return mLoggers; }
			template<typename T = Logger, typename ...Args>
			SharedLogger            createLogger(const String &name, Args ...args) {
				auto inst = std::make_shared<T>(name, args...);
				return addLogger(std::dynamic_pointer_cast<Logger>(inst));
			}
			SharedLogger            addLogger(const SharedLogger &logger) {
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
			void                    clearLoggers() {
				mLoggers.clear();
			}
		};

		class ConsoleLogAdapter: public LogAdapter {
			StringVector            mLines;
		public:
			ConsoleLogAdapter(): LogAdapter("console") {}
			ConsoleLogAdapter(const ConsoleLogAdapter &rhs) = default;
			~ConsoleLogAdapter() = default;

			ConsoleLogAdapter       &operator=(const ConsoleLogAdapter &rhs) = default;

			virtual void            flush() {
				for (auto const& line: mLines) {
					std::cout << line << std::endl;
				}
				std::cout.flush();
			}
			void                    append(const LogEntry &e) {
				mLines.add(format(e));
			}
		};
	}
}


#endif //QUASARFX_LOGGER_H
