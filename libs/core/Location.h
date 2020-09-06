//
// Created by darkboss on 9/6/20.
//

#ifndef QUASARFX_SOURCELOCATION_H
#define QUASARFX_SOURCELOCATION_H

#include "String.h"

namespace quasar {
	namespace core {

		template<typename CharT>
		class BasicSourceLocation {
		public:
			using string_type           = BasicString<CharT>;
			using line_id_type          = unsigned long;

		protected:
			string_type                 mFunc;
			string_type                 mFile;
			line_id_type                mLine;

		public:
			BasicSourceLocation(const string_type &func = string_type(), const string_type &file = string_type(), const line_id_type line = 0)
					: mFunc(func)
					, mFile(file)
					, mLine(line)
			{}
			BasicSourceLocation(const BasicSourceLocation &rhs) = default;
			~BasicSourceLocation() = default;

			BasicSourceLocation         &operator=(const BasicSourceLocation &rhs) = default;

			void                        reset() {
				mFunc.clear();
				mFile.clear();
				mLine = 0;
			}

			bool                        hasFunction() const noexcept {
				return !mFunc.empty();
			}

			bool                        hasFile() const noexcept {
				return !mFile.empty();
			}

			bool                        hasLine() const noexcept {
				return mLine != 0;
			}

			const string_type           &getFunction() const noexcept {
				return mFunc;
			}

			void                        setFunction(const string_type &func) {
				mFunc = func;
			}

			const string_type           &getFile() const noexcept {
				return mFile;
			}

			void                        setFile(const string_type &file) {
				mFile = file;
			}

			line_id_type                getLine() const noexcept {
				return mLine;
			}

			void                        setLine(line_id_type line) {
				mLine = line;
			}
		};

		extern template class BasicSourceLocation<char>;
		extern template class BasicSourceLocation<wchar_t>;

		using SourceLocation            = BasicSourceLocation<Char>;

		template<typename CharT>
		class BasicScriptLocation {
		public:
			using string_type           = BasicString<CharT>;
			using line_id_type          = unsigned long;
			using column_id_type        = unsigned short;
			using offset_type           = std::streamoff;

		protected:
			string_type                 mFile;
			line_id_type                mLine;
			column_id_type              mColumn;
			offset_type                 mOffset;

		public:
			BasicScriptLocation(const string_type &file = string_type(), const line_id_type line = 0, const column_id_type column = 0, const offset_type offset = 0)
				: mFile(file)
				, mLine(line)
				, mColumn(column)
				, mOffset(offset)
			{}
			BasicScriptLocation(const BasicScriptLocation &rhs) = default;
			~BasicScriptLocation() = default;

			BasicScriptLocation         &operator=(const BasicScriptLocation &rhs) = default;

			void                        reset() {
				mFile.clear();
				mLine = 0;
			}

			bool                        hasFile() const noexcept {
				return !mFile.empty();
			}

			bool                        hasLine() const noexcept {
				return mLine != 0;
			}

			bool                        hasColumn() const noexcept {
				return mColumn != 0;
			}

			bool                        hasOffset() const noexcept {
				return mOffset != 0;
			}

			const string_type           &getFile() const noexcept {
				return mFile;
			}

			void                        setFile(const string_type &file) {
				mFile = file;
			}

			line_id_type                getLine() const noexcept {
				return mLine;
			}

			void                        setLine(line_id_type line) {
				mLine = line;
			}

			column_id_type              getColumn() const noexcept {
				return mColumn;
			}

			void                        setColumn(column_id_type column) {
				mColumn = column;
			}

			offset_type                 getOffset() const noexcept {
				return mOffset;
			}

			void                        setOffset(offset_type offset) {
				mOffset = offset;
			}
		};

		extern template class BasicScriptLocation<char>;
		extern template class BasicScriptLocation<wchar_t>;

		using ScriptLocation            = BasicScriptLocation<Char>;
	}
}

# define QUASAR_SOURCE_LOCATION quasar::core::SourceLocation(T(__FUNCTION__), T(__FILE__), __LINE__)

#endif //QUASARFX_SOURCELOCATION_H
