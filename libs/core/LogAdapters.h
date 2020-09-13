//
// Created by darkboss on 9/13/20.
//

#ifndef QUASARFX_LOGADAPTERS_H
#define QUASARFX_LOGADAPTERS_H


#include <iostream>
#include <fstream>
#include "LogAdapter.h"

namespace quasar {
	namespace core {
		class MemoryLogAdapter: public LogAdapter {
		protected:
			OStream                 *mStream;
		public:
			MemoryLogAdapter(OStream *os = nullptr);
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
			ConsoleLogAdapter();
			ConsoleLogAdapter(const ConsoleLogAdapter &rhs) = default;
			virtual ~ConsoleLogAdapter() = default;

			ConsoleLogAdapter       &operator=(const ConsoleLogAdapter &rhs) = default;

			virtual void            flush() override;
		};

		class FileLogAdapter: public LogAdapter {
		protected:
			OFStream                mStream;
		public:
			FileLogAdapter(const String &path);
			FileLogAdapter(const FileLogAdapter &rhs) = delete;
			virtual ~FileLogAdapter() = default;

			FileLogAdapter          &operator=(const FileLogAdapter &rhs) = delete;

			OFStream                *getStream();
			const OStream           *getStream() const;

			virtual void            flush() override;
		};
	}
}

#endif //QUASARFX_LOGADAPTERS_H
