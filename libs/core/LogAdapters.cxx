//
// Created by darkboss on 9/13/20.
//

#include "LogAdapters.h"

namespace quasar {
	namespace core {
		MemoryLogAdapter::MemoryLogAdapter(quasar::core::OStream *os)
			: LogAdapter("memory"), mStream(os) {}

		OStream *MemoryLogAdapter::getStream() { return mStream; }

		const OStream *MemoryLogAdapter::getStream() const { return mStream; }

		void MemoryLogAdapter::setStream(OStream *os) { mStream = os; }

		void MemoryLogAdapter::flush() {
			LogAdapter::flush();
			for (auto const& line: mLines) {
				*mStream << line << std::endl;
			}
			mStream->flush();
			mLines.clear();
		}

		ConsoleLogAdapter::ConsoleLogAdapter()
				: MemoryLogAdapter(&std::cout) { mName = "console"; }

		void ConsoleLogAdapter::flush() {
			LogAdapter::flush();
			for (auto const& line: mLines) {
				std::cout << line << std::endl;
			}
			std::cout.flush();
			mLines.clear();
		}

		FileLogAdapter::FileLogAdapter(const String &path)
				: LogAdapter("file"), mStream(path, std::ios::out | std::ios::app) {}

		OFStream *FileLogAdapter::getStream() { return &mStream; }

		const OStream *FileLogAdapter::getStream() const { return &mStream; }

		void FileLogAdapter::flush() {
			LogAdapter::flush();
			for (auto const& line: mLines) {
				mStream << line << std::endl;
			}
			mStream.flush();
			mLines.clear();
		}
	}
}