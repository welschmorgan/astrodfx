//
// Created by darkboss on 9/12/20.
//

#ifndef QUASARFX_MTLGENERATOR_H
#define QUASARFX_MTLGENERATOR_H

#include <core/Generator.h>
#include <core/Config.h>
#include <locale>
#include <core/Mesh.h>

namespace quasar {
	namespace formats {
		class MtlGenerator: public core::BasicGenerator<Char, core::Material> {
		public:
			MtlGenerator();
			MtlGenerator(const MtlGenerator &rhs) = delete;
			virtual ~MtlGenerator() = default;

			MtlGenerator        &operator=(const MtlGenerator &rhs) = delete;

			void                generate(const value_type &item, stream_type &to) override;

		protected:
		};
	}
}


#endif //QUASARFX_MTLGENERATOR_H
