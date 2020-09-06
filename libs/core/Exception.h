//
// Created by darkboss on 9/6/20.
//

#ifndef QUASARFX_EXCEPTION_H
#define QUASARFX_EXCEPTION_H


#include <stdexcept>
#include "Location.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		class BasicException: public std::runtime_error {
		public:
			using char_type                     = CharT;
			using location_type                 = BasicSourceLocation<char_type>;
			using string_type                   = BasicString<char_type>;
			using line_id_type                  = typename location_type::line_id_type;
			using builder_type                  = std::basic_stringstream<char>;

		protected:
			string_type                         mMessage;
			std::string                         mFullMessage;
			location_type                       mLocation;

			static std::string                  build(const string_type &msg, const location_type &loc) {
				builder_type    builder;
				builder << std::basic_string<char>(msg.begin(), msg.end()) << " ";
				if (loc.hasFunction()) {
					builder << " from " << std::string(loc.getFunction().begin(), loc.getFunction().end());
				}
				if (loc.hasFile()) {
					builder << " in file " << std::string(loc.getFile().begin(), loc.getFile().end());
				}
				if (loc.hasLine()) {
					builder << " at line " << loc.getLine();
				}
				return builder.str();
			}

			BasicException()
				: runtime_error(std::string())
				, mMessage()
				, mFullMessage()
				, mLocation()
			{}

		public:
			BasicException(const std::basic_string<char> &msg, const location_type &loc)
					: runtime_error(std::string())
					, mMessage(string_type(msg.begin(), msg.end()))
					, mFullMessage(build(string_type(msg.begin(), msg.end()), loc))
					, mLocation(loc)
			{}
			BasicException(const std::basic_string<wchar_t> &msg, const location_type &loc)
					: runtime_error(std::string())
					, mMessage(string_type(msg.begin(), msg.end()))
					, mFullMessage(build(string_type(msg.begin(), msg.end()), loc))
					, mLocation(loc)
			{}
			BasicException(const BasicException &rhs) = default;
			virtual ~BasicException() = default;

			BasicException                      &operator=(const BasicException &rhs) = default;

			const string_type                   &getMessage() const noexcept {
				return mMessage;
			}

			const std::string                   &getFullMessage() const noexcept {
				return mFullMessage;
			}

			const location_type                 &getLocation() const noexcept {
				return mLocation;
			}

			const string_type                   &getFunction() const noexcept {
				return mLocation.getFunction();
			}

			const string_type                   &getFile() const noexcept {
				return mLocation.getFile();
			}

			line_id_type                        getLine() const noexcept {
				return mLocation.getLine();
			}

			bool                                hasFunction() const noexcept {
				return mLocation.hasFunction();
			}

			bool                                hasFile() const noexcept {
				return mLocation.hasFile();
			}

			bool                                hasLine() const noexcept {
				return mLocation.hasLine();
			}

			virtual const char                  *what() const noexcept {
				return mFullMessage.c_str();
			}
		};

		extern template class BasicException<char>;
		extern template class BasicException<wchar_t>;

		using Exception = BasicException<Char>;
	}
}

#endif //QUASARFX_EXCEPTION_H
