//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGADAPTER_H
#define QUASARFX_LOGADAPTER_H

#include <chrono>
#include "String.h"
#include "Collection.h"
#include "LogEntry.h"

namespace quasar {
	namespace core {

		class LogFlushDelay {
		public:
			LogFlushDelay(unsigned lines = 0, unsigned milliseconds = 0);
			LogFlushDelay(const LogFlushDelay &rhs) = default;
			~LogFlushDelay() = default;

			LogFlushDelay       &operator=(const LogFlushDelay &rhs) = default;

			unsigned            getLines() const noexcept;
			void                setLines(unsigned lines) noexcept;

			unsigned            getMilliseconds() const noexcept;
			void                setMilliseconds(unsigned ms) noexcept;
		protected:
			unsigned            mLines;
			unsigned            mMilliseconds;
		};

		class LogAdapter {
		public:
			using time_point            = std::chrono::system_clock::time_point;

			static const String         DefaultFormat;
			static const String         DefaultColoredFormat;
			static const LogFlushDelay  DefaultFlushDelay;
		protected:
			String                      mName;
			String                      mFormat;
			LogFlushDelay               mFlushDelay;
			time_point                  mLastFlushTime;
			StringVector                mLines;

		public:
			LogAdapter(const String &name = String());
			LogAdapter(const LogAdapter &rhs) = default;
			virtual ~LogAdapter() = default;

			LogAdapter          &operator=(const LogAdapter &rhs) = default;

			const String        &getName() const noexcept;
			const String        &getFormat() const noexcept;

			void                setFormat(const String &f) noexcept;

			time_point          getLastFlushTime() const noexcept;

			bool                shouldFlushNow() const noexcept;

			const LogFlushDelay &getFlushDelay() const noexcept;
			LogFlushDelay       &getFlushDelay() noexcept;
			void                setFlushDelay(const LogFlushDelay &f) noexcept;

			const StringVector  &getBufferedLines() const noexcept;

			PropertyMap         getFormatVars(const LogEntry &e) const noexcept;

			String              format(const LogEntry &e);

			virtual void        flush();
			virtual void        append(const LogEntry &e);
		};

		using SharedLogAdapter = std::shared_ptr<LogAdapter>;

	}
}

#endif //QUASARFX_LOGADAPTER_H
