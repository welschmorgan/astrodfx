//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_CORE_SERIALIZER_H
#define QUASARFX_CORE_SERIALIZER_H

#include <core/String.h>

namespace quasar {
	namespace core {
		template<typename T, typename IStreamT = IStream, typename OStreamT = OStream>
		class Serializer {
		public:
			using value_type        = T;
			using istream_type      = IStreamT;
			using ostream_type      = OStreamT;

			Serializer() = default;
			Serializer(const Serializer &) = default;
			virtual         ~Serializer() noexcept = default;

			Serializer      &operator=(const Serializer &) = default;

			virtual void    read(istream_type &is, value_type &into) = 0;
			virtual void    write(ostream_type &os, const value_type &from) = 0;
		};
	}
}

#endif //QUASARFX_CORE_SERIALIZER_H
