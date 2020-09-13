//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGLEVEL_H
#define QUASARFX_LOGLEVEL_H

#include "String.h"

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

			LogLevel(const int code, const String &label);

		public:
			LogLevel(const LogLevel &rhs) = default;
			~LogLevel() noexcept = default;

			LogLevel        &operator=(const LogLevel &rhs) = default;

			int             getCode() const noexcept;
			String          getLabel() const noexcept;
		};
	}
}

#endif //QUASARFX_LOGLEVEL_H
