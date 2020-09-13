//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGGER_H
#define QUASARFX_LOGGER_H

#include <iostream>
#include <thread>
#include <fstream>
#include "String.h"
#include "Collection.h"
#include "Platform.h"
#include "LogAdapter.h"

namespace quasar {
	namespace core {
		class Logger {
		public:
			using log_adapter_list  = Vector<SharedLogAdapter>;

		protected:
			String                  mName;
			log_adapter_list        mAdapters;
		public:
			Logger(const String &name = String());
			Logger(const Logger &rhs) = default;
			~Logger() = default;

			Logger                  &operator=(const Logger &rhs) = default;

			void                    log(const LogLevel &lvl, const String &msg);
			void                    debug(const String &msg);
			void                    trace(const String &msg);
			void                    info(const String &msg);
			void                    warn(const String &msg);
			void                    error(const String &msg);
			void                    fatal(const String &msg);

			void                    setName(const String &name);
			const String            &getName() const noexcept;

			bool                    hasAdapter(const String &name);
			const log_adapter_list  &getAdapters() const noexcept;
			void                    setAdapters(const log_adapter_list &l) noexcept;
			SharedLogAdapter        addAdapter(const SharedLogAdapter &a);
			void                    clearAdapters();

			void                    flush();
		};

		using SharedLogger = std::shared_ptr<Logger>;
	}
}


#endif //QUASARFX_LOGGER_H
