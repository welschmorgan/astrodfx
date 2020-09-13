//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGMANAGER_H
#define QUASARFX_LOGMANAGER_H

#include "LogAdapter.h"
#include "Logger.h"

namespace quasar {
	namespace core {
		class LogManager {
		protected:
			Vector<SharedLogAdapter>        mAdapters;
			Vector<SharedLogger>            mLoggers;
# if QUASAR_SUPPORT_MULTITHREADING
			std::thread                     mThread;
# endif

		public:
			LogManager();
			LogManager(const LogManager &rhs) = delete;
			virtual ~LogManager();

			LogManager                      &operator=(const LogManager &rhs) = delete;

			void                            log(const LogLevel &lvl, const String &msg, const String &channel = String());
			void                            debug(const String &msg, const String &channel = String());
			void                            trace(const String &msg, const String &channel = String());
			void                            info(const String &msg, const String &channel = String());
			void                            warn(const String &msg, const String &channel = String());
			void                            error(const String &msg, const String &channel = String());
			void                            fatal(const String &msg, const String &channel = String());

			const Vector<SharedLogAdapter>  &getAdapters() const noexcept;
			void                            setAdapters(const Vector<SharedLogAdapter> &l) noexcept;
			bool                            hasAdapter(const String &name) const noexcept;

			SharedLogAdapter                getAdapter(const String &name, bool except = true) const;

			template<typename T, typename... Args>
			SharedLogAdapter                createAdapter(Args... args) {
				auto inst = std::make_shared<T>(args...);
				return addAdapter(std::dynamic_pointer_cast<LogAdapter>(inst));
			}

			SharedLogAdapter                addAdapter(const SharedLogAdapter &a);
			void                            clearAdapters() { mAdapters.clear(); }

			bool                            hasLogger(const String &name) const noexcept;
			SharedLogger                    getLogger(const String &name, bool except = true) const;
			void                            setLoggers(const Vector<SharedLogger> &loggers) noexcept;
			Vector<SharedLogger>            getLoggers() const noexcept;

			template<typename T = Logger, typename... Args>
			SharedLogger                    createLogger(const String &name, Args... args) {
				auto inst = std::make_shared<T>(name, args...);
				return addLogger(std::dynamic_pointer_cast<Logger>(inst));
			}

			SharedLogger                    addLogger(const SharedLogger &logger);
			void                            clearLoggers();

			void                            checkFlush();

			void                            flush();
		};

		using SharedLogManager              = std::shared_ptr<LogManager>;
	}
}

#endif //QUASARFX_LOGMANAGER_H
