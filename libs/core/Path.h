//
// Created by darkboss on 8/2/20.
//

#ifndef QUASARFX_CORE_PATH_H
#define QUASARFX_CORE_PATH_H

#include <cstring>
#include "String.h"

namespace quasar {
	namespace core {
		class PathExt {
		protected:
			String mValue;

		public:
			PathExt() = default;
			explicit PathExt(const String &v);
			explicit PathExt(const String::value_type *v);
			PathExt(const PathExt &rhs) = default;
			~PathExt() = default;

			PathExt         &operator=(const PathExt &rhs);
			PathExt         &operator=(const String &rhs);

			bool            operator==(const PathExt &rhs) const noexcept;
			bool            operator!=(const PathExt &rhs) const noexcept;

			bool            operator==(const String &rhs) const noexcept;
			bool            operator!=(const String &rhs) const noexcept;

			bool            operator==(const String::value_type *rhs) const noexcept;
			bool            operator!=(const String::value_type *rhs) const noexcept;

			bool            operator<=(const PathExt &rhs) const noexcept;
			bool            operator<(const PathExt &rhs) const noexcept;

			bool            operator>=(const PathExt &rhs) const noexcept;
			bool            operator>(const PathExt &rhs) const noexcept;

			const String    &str() const noexcept;

			void            sanitize();
		};

		class Path {
		public:
			using iterator              = String::iterator;
			using const_iterator        = String::const_iterator;
			using reverse_iterator      = String::reverse_iterator;
			using const_reverse_iterator= String::const_reverse_iterator;

			static const String         Separator;

		protected:
			String          mData;

		public:
			Path() = default;
			explicit        Path(const String &data);
			explicit        Path(const String::value_type *data);
			Path(const Path &rhs) = default;
			~Path() noexcept;

			Path            &operator=(const Path &rhs) = default;
			Path            &operator=(const String &rhs);
			Path            &operator=(const String::value_type *rhs);

			String          &operator*();
			const String    &operator*() const;

			String          *operator->();
			const String    *operator->() const;

			Path            operator+(const Path &rhs) const;
			String          operator+(const String &rhs) const;
			String          operator+(const String::value_type *rhs) const;

			Path            &operator+=(const Path &rhs);
			Path            &operator+=(const String &rhs);
			Path            &operator+=(const String::value_type *rhs);


			bool            operator==(const Path &rhs) const noexcept;
			bool            operator!=(const Path &rhs) const noexcept;
			bool            operator<(const Path &rhs) const noexcept;
			bool            operator>(const Path &rhs) const noexcept;
			bool            operator<=(const Path &rhs) const noexcept;
			bool            operator>=(const Path &rhs) const noexcept;

			inline const String::value_type  *c_str() const noexcept;

			const String    &absolute() const noexcept;

			String          base() const noexcept;
			PathExt         ext() const noexcept;
			Path            parent() const noexcept;

			bool            exists() const noexcept;
			bool            isDir() const noexcept;
			bool            isFile() const noexcept;
			bool            empty() const noexcept;

			Path            join(const Path &p) const noexcept;
			Path            join(const String &p) const noexcept;
			Path            join(const String::value_type *p) const noexcept;

			std::vector<Path>   readDir(bool recurs = false, bool (*filter)(const String &) = nullptr) const noexcept(false);
			String              readFile() const noexcept(false);

			bool            removeAll();
			bool            remove();

			bool            makeDir();
			bool            makeDirs();


			iterator                    begin() { return mData.begin(); }
			const_iterator              begin() const { return mData.begin(); }
			const_iterator              cbegin() const { return mData.begin(); }

			iterator                    end() { return mData.end(); }
			const_iterator              end() const { return mData.end(); }
			const_iterator              cend() const { return mData.end(); }

			reverse_iterator            rbegin() { return mData.rbegin(); }
			const_reverse_iterator      rbegin() const { return mData.rbegin(); }
			const_reverse_iterator      crbegin() const { return mData.crbegin(); }

			reverse_iterator            rend() { return mData.rend(); }
			const_reverse_iterator      rend() const { return mData.rend(); }
			const_reverse_iterator      crend() const { return mData.crend(); }
		};

		using PathVector = std::vector<Path>;
		using PathList = std::list<Path>;
		template<typename V>
        using PathMap = std::map<Path, V>;
	}
}

quasar::core::OStream       &operator<<(quasar::core::OStream &os, const quasar::core::Path &p);
quasar::core::IStream       &operator>>(quasar::core::IStream &is, quasar::core::Path &p);

bool                        operator==(const quasar::core::String &lhs, const quasar::core::PathExt &rhs);
bool                        operator!=(const quasar::core::String &lhs, const quasar::core::PathExt &rhs);

bool                        operator==(const quasar::core::String::value_type *lhs, const quasar::core::PathExt &rhs);
bool                        operator!=(const quasar::core::String::value_type *lhs, const quasar::core::PathExt &rhs);

quasar::core::OStream       &operator<<(quasar::core::OStream &os, const quasar::core::PathExt &p);
quasar::core::IStream       &operator>>(quasar::core::IStream &is, quasar::core::PathExt &p);

#endif //QUASARFX_CORE_PATH_H
