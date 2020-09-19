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
		/**
		 * Represent a flusing delay configuration.
		 */
		class LogFlushDelay {
		public:
			LogFlushDelay(unsigned lines = 0, unsigned milliseconds = 0);
			LogFlushDelay(const LogFlushDelay &rhs) = default;
			~LogFlushDelay() = default;

			LogFlushDelay       &operator=(const LogFlushDelay &rhs) = default;

			/**
			 * Return the number of lines before flushing should happen.
			 */
			unsigned            getLines() const noexcept;

			/**
			 * Define the number of lines before flushing should happen
			 *
			 * @param lines 	Number of lines before flushing.
			 */
			void                setLines(unsigned lines) noexcept;

			/**
			 * Return the number of milliseconds before flushing should happen
			 */
			unsigned            getMilliseconds() const noexcept;

			/**
			 * Define the number of milliseconds before flushing should happen
			 *
			 * @param ms		Number of milliseconds before flushing should happen
			 */
			void                setMilliseconds(unsigned ms) noexcept;

		protected:
			unsigned            mLines;
			unsigned            mMilliseconds;
		};

		/**
		 * Represent a way to format log entries to string
		 */
		class LogEntryFormatter {
		protected:
			String                      mFormat;

		public:
			LogEntryFormatter(const String &formatStr = String());
			LogEntryFormatter(const LogEntryFormatter &rhs) = default;
			virtual ~LogEntryFormatter() = default;

			LogEntryFormatter       &operator=(const LogEntryFormatter &rhs) = default;

			/**
			 * Return the format variables to expand the format with
			 *
			 * @param e 			The log entries to generate vars from
			 *
			 * @return				A map of properties
			 */
			virtual PropertyMap     getFormatVars(const LogEntry &e) const noexcept;

			/**
			 * Retrieve the format string expanded using variables
			 *
			 * @param f				The format string
			 */
			virtual const String    &getFormat() const noexcept;


			/**
			 * Define the format string expanded using variables
			 *
			 * @param f				The format string
			 */
			virtual void            setFormat(const String &f) noexcept;

			/**
			 * Format the given entries with variables generated by getFormatVars
			 *
			 * @param e				The entry to be formatted.
			 *
			 * @return				The formatted string to be logged
			 */
			virtual String          format(const LogEntry &e);
		};

		using SharedLogEntryFormatter = std::shared_ptr<LogEntryFormatter>;

		/**
		 * Represent a log message adapter towards a storage media.
		 * It allows to buffer messages, and flush them under certain conditions
		 *
		 * @see LogFlushDelay
		 */
		class LogAdapter {
		public:
			using time_point            = std::chrono::system_clock::time_point;

			/**
			 * A default flush delay configuration
			 */
			static const LogFlushDelay  DefaultFlushDelay;

			/**
			 * A default format string, to expand entries with
			 */
			static const String         DefaultFormat;

			/**
			 * A default colored format string, to expand entries with
			 */
			static const String         DefaultColoredFormat;

		protected:
			String                      mType;
			String                      mName;
			SharedLogEntryFormatter     mFormatter;
			LogFlushDelay               mFlushDelay;
			time_point                  mLastFlushTime;
			StringVector                mLines;

		public:
			LogAdapter(const String &type, const String &name = String(), const SharedLogEntryFormatter &fmt = SharedLogEntryFormatter());
			LogAdapter(const LogAdapter &rhs) = default;
			virtual ~LogAdapter() = default;

			LogAdapter                  &operator=(const LogAdapter &rhs) = default;

			/**
			 * Return the adapter name (memory, file, console, ...)
			 */
			const String                &getType() const noexcept;

			/**
			 * Return the adapter name (memory, file, console, ...)
			 */
			const String                &getName() const noexcept;

			/**
			 * Return the adapter name (memory, file, console, ...)
			 */
			LogAdapter                  &setName(const String &n) noexcept;

			/**
			 * Return the time point at which this adapter was last flushed
			 */
			time_point                  getLastFlushTime() const noexcept;

			/**
			 * Return true if this adapter should be flushed now
			 */
			bool                        shouldFlushNow() const noexcept;

			/**
			 * Return the flush delay configuration
			 */
			const LogFlushDelay         &getFlushDelay() const noexcept;
			/**
			 * Return the flush delay configuration
			 */
			LogFlushDelay               &getFlushDelay() noexcept;
			/**
			 * Define the flush delay configuration
			 */
			void                        setFlushDelay(const LogFlushDelay &f) noexcept;

			/**
			 * Define the entry formatter used to transform entries to string.
			 */
			void                        setFormatter(SharedLogEntryFormatter fmt) noexcept;

			/**
			 * Define the entry formatter format.
			 *
			 * @see LogAdapter::setFormatter
			 */
			void                        setFormat(const String &f);
			/**
			 * Retrieve the entry formatter format.
			 *
			 * @see LogAdapter::getFormatter
			 */
			String                      getFormat() const;

			/**
			 * Return the formatter used to transform entries to string
			 */
			SharedLogEntryFormatter     getFormatter() const noexcept;

			/**
			 * Return the line buffer containing lines not yet flushed
			 */
			const StringVector          &getBufferedLines() const noexcept;

			/**
			 * Flush lines buffered in this adapter
			 */
			virtual void                flush();

			/**
			 * Append a line to the buffer, to be later flushed
			 */
			virtual void                append(const LogEntry &e);
		};

		using SharedLogAdapter = std::shared_ptr<LogAdapter>;

	}
}

#endif //QUASARFX_LOGADAPTER_H