//
// Created by darkboss on 8/2/20.
//

#ifndef QUASARFX_CORE_PATH_H
#define QUASARFX_CORE_PATH_H

#include "String.h"

namespace quasar {
	namespace core {
		class Path {
		public:
			static const String Separator;

		protected:
			String          mData;

		public:
			explicit        Path(const String &data);
			explicit        Path(const String::value_type *data);
			Path(const Path &rhs) = default;
			~Path() noexcept;

			Path            &operator=(const Path &rhs) = default;
			Path            &operator=(const String &rhs);
			Path            &operator=(const String::value_type *rhs);

			bool            operator==(const Path &rhs) const noexcept;
			bool            operator!=(const Path &rhs) const noexcept;
			bool            operator<(const Path &rhs) const noexcept;
			bool            operator>(const Path &rhs) const noexcept;
			bool            operator<=(const Path &rhs) const noexcept;
			bool            operator>=(const Path &rhs) const noexcept;

			inline const String::value_type  *c_str() const noexcept;

			const String    &absolute() const noexcept;

			String          base() const noexcept;
			String          ext() const noexcept;
			Path            parent() const noexcept;

			bool            isDir() const noexcept;
			bool            isFile() const noexcept;
			bool            isEmpty() const noexcept;

			Path            join(const Path &p) const noexcept;

			std::vector<Path>   readDir(bool recurs = false, bool (*filter)(const String &) = nullptr) const noexcept(false);
			String              readFile() const noexcept(false);

			bool            removeAll();
			bool            remove();

			bool            makeDir();
			bool            makeDirs();
		};
	}
}

#endif //QUASARFX_CORE_PATH_H
