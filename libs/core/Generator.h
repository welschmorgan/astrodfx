 //
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_GENERATOR_H
#define QUASARFX_GENERATOR_H

#include "Lexer.h"
#include "Location.h"
#include "Exception.h"

namespace quasar {
	namespace core {
		template<typename CharT, typename ValueT, typename StreamT = std::basic_ostream<Char>>
		class BasicGenerator {
		public:
			using value_type        = ValueT;
			using char_type         = CharT;
			using string_type       = BasicString<char_type>;
			using stream_type       = std::basic_ostream<char_type>;

		public:
			BasicGenerator() = default;
			BasicGenerator(const BasicGenerator &rhs) = default;
			virtual                 ~BasicGenerator() = default;

			BasicGenerator          &operator=(const BasicGenerator &rhs) = default;

			virtual string_type     generate(const value_type &from) {
				std::basic_stringstream<char_type>  buf;
				generate(from, buf);
				return buf.str();
			}
			virtual void            generate(const value_type &from, stream_type &to) = 0;
		};

		template<typename ValueT, typename StreamT = std::basic_ostream<Char>>
		using Generator             = BasicGenerator<Char, ValueT, StreamT>;
	}
}

#endif //QUASARFX_PARSER_H
