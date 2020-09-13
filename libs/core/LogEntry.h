//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGENTRY_H
#define QUASARFX_LOGENTRY_H

#include <chrono>
#include "LogLevel.h"

namespace quasar {
	namespace core {
		class LogEntry {
		public:
			using time_point = std::chrono::system_clock::time_point;

		protected:
			LogLevel   mLevel;
			String     mChannel;
			time_point mTimestamp;
			String     mMessage;
		public:
			LogEntry(const LogLevel &level, const String &channel, const String &message,
			         const time_point &timestamp = std::chrono::system_clock::now());
			LogEntry(const LogEntry &rhs) = default;
			~LogEntry() = default;

			LogEntry &operator=(const LogEntry &rhs) = default;

			const LogLevel &getLevel() const;
			void setLevel(const LogLevel &level);

			const String &getChannel() const;
			void setChannel(const String &channel);

			const time_point &getTimestamp() const;
			void setTimestamp(const time_point &timestamp);

			const String &getMessage() const;
			void setMessage(const String &message);
		};
	}
}

#endif //QUASARFX_LOGENTRY_H
