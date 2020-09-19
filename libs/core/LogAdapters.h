//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGADAPTERS_H
#define QUASARFX_LOGADAPTERS_H


#include <iostream>
#include <fstream>
#include "LogAdapter.h"
#include "Path.h"

namespace quasar {
	namespace core {
		class MemoryLogAdapter: public LogAdapter {
		protected:
			OStream                 *mStream;

		public:
			static const String     Type;

			MemoryLogAdapter(OStream *os = nullptr, const String &name = String());
			MemoryLogAdapter(const MemoryLogAdapter &rhs) = default;
			virtual ~MemoryLogAdapter() = default;

			MemoryLogAdapter        &operator=(const MemoryLogAdapter &rhs) = default;

			OStream                 *getStream();
			const OStream           *getStream() const;
			void                    setStream(OStream *os);

			virtual void            flush() override;
		};

		class ConsoleLogAdapter: public MemoryLogAdapter {
		public:
			static const String     Type;

			ConsoleLogAdapter(const String &name = String());
			ConsoleLogAdapter(const ConsoleLogAdapter &rhs) = default;
			virtual ~ConsoleLogAdapter() = default;

			ConsoleLogAdapter       &operator=(const ConsoleLogAdapter &rhs) = default;

			virtual void            flush() override;
		};

		class FileLogAdapter: public LogAdapter {
		protected:
			OFStream                mStream;
			Path                    mPath;

		public:
			static const String     Type;

			FileLogAdapter(const Path &path = Path(), const String &name = String());
			FileLogAdapter(const FileLogAdapter &rhs) = delete;
			virtual ~FileLogAdapter() = default;

			FileLogAdapter          &operator=(const FileLogAdapter &rhs) = delete;

			String                  getName() const noexcept;

			const Path              &getPath() const noexcept;
			void                    setPath(const Path &path) noexcept;

			OFStream                *getStream();
			const OStream           *getStream() const;

			virtual void            flush() override;
		};
	}
}

#endif //QUASARFX_LOGADAPTERS_H
