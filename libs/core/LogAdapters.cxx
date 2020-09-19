//
// Created by darkboss on 9/13/20.
//

#include "LogAdapters.h"

namespace quasar {
	namespace core {
		const String MemoryLogAdapter::Type = "memory";

		MemoryLogAdapter::MemoryLogAdapter(quasar::core::OStream *os, const String &name)
			: LogAdapter(Type, name), mStream(os) {}

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

		const String ConsoleLogAdapter::Type = "console";

		ConsoleLogAdapter::ConsoleLogAdapter(const String &name)
			: MemoryLogAdapter(&std::cout, name)
		{ mType = Type; }

		void ConsoleLogAdapter::flush() {
			LogAdapter::flush();
			for (auto const& line: mLines) {
				std::cout << line << std::endl;
			}
			std::cout.flush();
			mLines.clear();
		}

		const String FileLogAdapter::Type = "file";

		FileLogAdapter::FileLogAdapter(const Path &path, const String &name)
			: LogAdapter(Type, name.empty() ? path.base() : name)
			, mStream(path.absolute(), std::ios::out | std::ios::app)
			, mPath(path)
		{}

		OFStream *FileLogAdapter::getStream() { return &mStream; }

		const OStream *FileLogAdapter::getStream() const { return &mStream; }

		void FileLogAdapter::flush() {
			LogAdapter::flush();
			if (!mLines.empty()) {
				if (!mStream.is_open()) {
					throw std::runtime_error(std::string(mPath.begin(), mPath.end()) + ": failed to open stream");
				}
				for (auto const &line: mLines) {
					mStream << line << std::endl;
				}
				mStream.flush();
				mLines.clear();
			}
		}

		const Path &FileLogAdapter::getPath() const noexcept { return mPath; }

		void FileLogAdapter::setPath(const Path &path) noexcept {
			if (mName.empty()) {
				mName = path.base();
			}
			mPath = path;
		}

		String FileLogAdapter::getName() const noexcept {
			if (mName.empty()) {
				return mPath.base();
			}
			return mName;
		}
	}
}