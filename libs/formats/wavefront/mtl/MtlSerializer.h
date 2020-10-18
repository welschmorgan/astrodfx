//
// Created by darkboss on 10/17/20.
//

#ifndef QUASARFX_MTLSERIALIZER_H
#define QUASARFX_MTLSERIALIZER_H

# include <core/Serializer.h>
# include <core/Config.h>
# include <core/String.h>
# include <iostream>
# include "formats/wavefront/obj/ObjLexer.h"
# include "formats/wavefront/obj/ObjParser.h"
# include "formats/wavefront/obj/ObjGenerator.h"

namespace quasar {
	namespace formats {
		template<typename IStreamT = core::IStream, typename OStreamT = core::OStream>
		class MtlSerializer : public core::Serializer<core::Material, IStreamT, OStreamT> {
		protected:

		public:
			using base_type     = core::Serializer<core::ConfigNode, IStreamT, OStreamT>;
			using self_type     = MtlSerializer<IStreamT, OStreamT>;

			using value_type    = typename base_type::value_type;
			using istream_type  = typename base_type::istream_type;
			using ostream_type  = typename base_type::ostream_type;

			MtlSerializer() = default;
			MtlSerializer(const MtlSerializer &) = default;
			virtual             ~MtlSerializer() noexcept = default;

			MtlSerializer      &operator=(const MtlSerializer &) = default;

			void                read(istream_type &is, value_type &into) override {
				ObjLexer l;
				ObjParser p;
				p.parse(l.analyse(is), into);
			}

			void                write(ostream_type &os, const value_type &from) override {
				ObjGenerator gen;
				gen.generate(from, os);
			}

		private:
		};
	}
}


#endif //QUASARFX_MTLSERIALIZER_H
