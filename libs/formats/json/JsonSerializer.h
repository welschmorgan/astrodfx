//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_JSONSERIALIZER_H
# define QUASARFX_JSONSERIALIZER_H

# include <core/Serializer.h>
# include <core/Config.h>
# include <core/String.h>
# include <iostream>
#include "JsonLexer.h"
#include "JsonParser.h"
#include "JsonGenerator.h"

namespace quasar {
	namespace formats {
		template<typename IStreamT = core::IStream, typename OStreamT = core::OStream>
		class JsonSerializer : public core::Serializer<core::ConfigNode, IStreamT, OStreamT> {
		protected:

		public:
			using base_type     = core::Serializer<core::ConfigNode, IStreamT, OStreamT>;
			using self_type     = JsonSerializer<IStreamT, OStreamT>;

			using value_type    = typename base_type::value_type;
			using istream_type  = typename base_type::istream_type;
			using ostream_type  = typename base_type::ostream_type;

			JsonSerializer() = default;
			JsonSerializer(const JsonSerializer &) = default;
			virtual             ~JsonSerializer() noexcept = default;

			JsonSerializer      &operator=(const JsonSerializer &) = default;

			void                read(istream_type &is, value_type &into) override {
				JsonLexer l;
				JsonParser p;
				p.parse(l.analyse(is), into);
			}

			void                write(ostream_type &os, const value_type &from) override {
				JsonGenerator gen;
				gen.generate(from, os);
			}

		private:
		};
	}
}


#endif //QUASARFX_JSONSERIALIZER_H
