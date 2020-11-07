//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_CORE_SERIALIZER_H
#define QUASARFX_CORE_SERIALIZER_H

#include <core/String.h>

namespace quasar {
	namespace core {
		template<typename T, typename IStreamT = IStream>
		class ISerializer {
		public:
			using value_type        = T;
			using istream_type      = IStreamT;

			ISerializer() = default;
			ISerializer(const ISerializer &) = default;
			virtual         ~ISerializer() noexcept = default;

			ISerializer     &operator=(const ISerializer &) = default;

			virtual void    read(istream_type &is, value_type &into) = 0;
		};

		template<typename T, typename OStreamT = OStream>
		class OSerializer {
		public:
			using value_type        = T;
			using ostream_type      = OStreamT;

			OSerializer() = default;
			OSerializer(const OSerializer &) = default;
			virtual         ~OSerializer() noexcept = default;

			OSerializer     &operator=(const OSerializer &) = default;

			virtual void    write(ostream_type &os, const value_type &from) = 0;
		};

		template<typename T, typename IStreamT = IStream, typename OStreamT = OStream>
		class Serializer
			: public ISerializer<T, IStreamT>
			, public OSerializer<T, OStreamT>
		{
		public:
			using value_type        = T;
			using istream_type      = IStreamT;
			using ostream_type      = OStreamT;

			Serializer() = default;
			Serializer(const Serializer &) = default;
			virtual         ~Serializer() noexcept = default;

			Serializer      &operator=(const Serializer &) = default;
		};
	}
}

#endif //QUASARFX_CORE_SERIALIZER_H
