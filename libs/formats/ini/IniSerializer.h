//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_INISERIALIZER_H
# define QUASARFX_INISERIALIZER_H

# include <core/Serializer.h>
# include <core/Config.h>
# include <core/String.h>
#include "IniLexer.h"
#include "IniParser.h"
#include "IniGenerator.h"
# include <iostream>

namespace quasar {
	namespace formats {
		template<typename IStreamT = core::IStream, typename OStreamT = core::OStream>
		class IniSerializer : public core::Serializer<core::ConfigNode, IStreamT, OStreamT> {
		public:
			using base_type     = core::Serializer<core::ConfigNode, IStreamT, OStreamT>;
			using self_type     = IniSerializer<IStreamT, OStreamT>;

			using value_type    = typename base_type::value_type;
			using istream_type  = typename base_type::istream_type;
			using ostream_type  = typename base_type::ostream_type;

			static constexpr core::String::value_type   DefaultSectionName[] = "";
			static const core::String::value_type       Dot = '.';
			static constexpr core::String::value_type   CommentDelims[] = "#;";
			static const size_t                         NCommentDelims = 2;
			static const core::String::value_type       SectionDelimL = '[';
			static const core::String::value_type       SectionDelimR = ']';
			static constexpr core::String::value_type   StoreSectionDelim[] = "::";
			static const core::String::value_type       PropertyDelim = '=';

			IniSerializer() = default;
			IniSerializer(const IniSerializer &) = default;
			virtual ~IniSerializer() noexcept = default;

			IniSerializer &operator=(const IniSerializer &) = default;

			void    read(istream_type &is, value_type &into) override {
				IniLexer        lexer;
				IniParser       parser;
				value_type      ini;

				auto tokens = lexer.analyse(is);
				parser.parse(tokens, ini);

				into = ini;
			}

			void    write(ostream_type &os, const value_type &from) override {
				IniGenerator    gen;
				gen.generate(from, os);
			}

		};
	}
}


#endif //QUASARFX_INISERIALIZER_H
