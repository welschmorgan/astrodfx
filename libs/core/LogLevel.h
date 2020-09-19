//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGLEVEL_H
#define QUASARFX_LOGLEVEL_H

#include "String.h"

namespace quasar {
	namespace core {
		/**
		 * Represent a log message level.
		 */
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
			String          mColor;

			LogLevel(const int code, const String &label, const String &color = String());

		public:
			LogLevel(const LogLevel &rhs) = default;
			~LogLevel() noexcept = default;

			LogLevel        &operator=(const LogLevel &rhs) = default;

			bool            operator==(const LogLevel &rhs) const noexcept {
				return mCode == rhs.mCode;
			}

			bool            operator!=(const LogLevel &rhs) const noexcept {
				return !(*this == rhs);
			}

			bool            operator<(const LogLevel &rhs) const noexcept {
				return mCode < rhs.mCode;
			}

			bool            operator<=(const LogLevel &rhs) const noexcept {
				return mCode <= rhs.mCode;
			}

			bool            operator>(const LogLevel &rhs) const noexcept {
				return mCode > rhs.mCode;
			}

			bool            operator>=(const LogLevel &rhs) const noexcept {
				return mCode >= rhs.mCode;
			}

			int             getCode() const noexcept;
			String          getLabel() const noexcept;
			String          getColor() const noexcept;
		};
	}
}

#endif //QUASARFX_LOGLEVEL_H
