//
// Created by darkboss on 9/13/20.
//

#include "LogAdapter.h"

namespace quasar {
	namespace core {
		const String            LogAdapter::DefaultFormat("[{yyyy}/{m}/{d} {h}:{i}:{s}] [{c}] {l} - {M}");
		const LogFlushDelay     LogAdapter::DefaultFlushDelay(1, 0);

		LogAdapter::LogAdapter(const String &name)
			: mName(name)
			, mFormat(DefaultFormat)
			, mFlushDelay()
			, mLastFlushTime(std::chrono::system_clock::now())
			, mLines()
		{}

		const String &LogAdapter::getName() const noexcept { return mName; }

		const String &LogAdapter::getFormat() const noexcept { return mFormat; }

		void LogAdapter::setFormat(const String &f) noexcept { mFormat = f; }

		LogAdapter::time_point LogAdapter::getLastFlushTime() const noexcept { return mLastFlushTime; }

		bool LogAdapter::shouldFlushNow() const noexcept {
			auto delay             = std::chrono::system_clock::now() - mLastFlushTime;
			bool linesTriggerFlush = mFlushDelay.getLines() > 0 && mLines.size() >= mFlushDelay.getLines();
			bool delayTriggerFlush = delay >= std::chrono::milliseconds(mFlushDelay.getMilliseconds());
			return linesTriggerFlush || delayTriggerFlush;
		}

		const LogFlushDelay &LogAdapter::getFlushDelay() const noexcept { return mFlushDelay; }

		void LogAdapter::setFlushDelay(const LogFlushDelay &f) noexcept { mFlushDelay = f; }

		LogFlushDelay &LogAdapter::getFlushDelay() noexcept { return mFlushDelay; }

		const StringVector &LogAdapter::getBufferedLines() const noexcept { return mLines; }

		PropertyMap LogAdapter::getFormatVars(const LogEntry &e) const noexcept {
			String time, date, year, fullYear, month, day, hour, min, sec;

			std::chrono::system_clock::time_point now    = std::chrono::system_clock::now();
			std::time_t                           now_c  = std::chrono::system_clock::to_time_t(now);
			std::tm                               now_tm = *std::localtime(&now_c);

			year     = std::to_string(now_tm.tm_year + 1900);
			fullYear = std::to_string((now_tm.tm_year + 1900) - 2000);
			month    = std::to_string(now_tm.tm_mon);
			day      = std::to_string(now_tm.tm_mday);
			hour     = std::to_string(now_tm.tm_hour);
			min      = std::to_string(now_tm.tm_min);
			sec      = std::to_string(now_tm.tm_sec);

			time = hour + ":" + min + ":" + sec;
			date = year + "/" + month + "/" + day;

			return Map<String, String>({
					                           {"{T}",        time},
					                           {"{Z}",        date + " " + time},
					                           {"{D}",        date},
					                           {"{yyyy}",     fullYear},
					                           {"{yy}",       year},
					                           {"{m}",        month},
					                           {"{d}",        day},
					                           {"{h}",        hour},
					                           {"{i}",        min},
					                           {"{s}",        sec},
					                           {"{l}",        e.getLevel().getLabel()},
					                           {"{M}",        e.getMessage()},
					                           {"{c}",        e.getChannel()},
					                           {"{lC}",       e.getLevel().getColor() + e.getLevel().getLabel() +
					                                          "\033[0m"},
					                           {"{no_color}", "\033[0m"},
					                           {"{red}",      "\033[1;31m"},
					                           {"{green}",    "\033[1;32m"},
					                           {"{blue}",     "\033[1;33m"},
					                           {"{yellow}",   "\033[1;34m"},
					                           {"{magenta}",  "\033[1;35m"},
					                           {"{cyan}",     "\033[1;36m"},
			                           });
		}

		String LogAdapter::format(const LogEntry &e) {
			String          ret = mFormat;
			size_t          pos;
			for (auto const &d: getFormatVars(e)) {
				if ((pos = ret.find(d.first)) != String::npos) {
					ret.replace(pos, d.first.size(), d.second);
				}
			}
			return ret;
		}

		void LogAdapter::flush() {
			mLastFlushTime = std::chrono::system_clock::now();
		}

		void LogAdapter::append(const LogEntry &e) {
			mLines.add(format(e));
			if (shouldFlushNow()) {
				flush();
			}
		}

		LogFlushDelay::LogFlushDelay(unsigned int lines, unsigned int milliseconds)
				: mLines(lines)
				, mMilliseconds(milliseconds) {}

		unsigned LogFlushDelay::getLines() const noexcept { return mLines; }

		void LogFlushDelay::setLines(unsigned lines) noexcept { mLines = lines; }

		unsigned LogFlushDelay::getMilliseconds() const noexcept { return mMilliseconds; }

		void LogFlushDelay::setMilliseconds(unsigned ms) noexcept { mMilliseconds = ms; }
	}
}