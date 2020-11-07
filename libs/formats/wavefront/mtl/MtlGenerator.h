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
			enum TextureType {
				TT_NONE,
				TT_AMBIENT,
				TT_DIFFUSE,
				TT_SPECULAR,
				TT_SHININESS,
				TT_ALPHA,
				TT_BUMP,
				TT_DISPLACEMENT,
				TT_DECAL,
				TT_REFLECTION
			};

			using TextureTypeToStatementMap     = core::Map<TextureType, core::String>;
			using TextureNameToTypeMap          = core::Map<core::String, TextureType>;

		protected:
			TextureTypeToStatementMap           mTextureTypesToStatements;
			TextureNameToTypeMap                mTextureNameToTypes;

		public:
			MtlGenerator();
			MtlGenerator(const MtlGenerator &rhs) = delete;
			virtual ~MtlGenerator() = default;

			MtlGenerator                        &operator=(const MtlGenerator &rhs) = delete;

			TextureTypeToStatementMap           getTextureTypesToStatements() const;
			TextureNameToTypeMap                getTextureNameToTypes() const;

			void                                setTextureNameToType(const core::String &name, TextureType type);
			TextureType                         getTextureType(const core::String &name);

			void                                generate(const value_type &item, stream_type &to) override;

		protected:
			void                                generatePass(const core::Material *mat, const core::MaterialPass *pass, stream_type &to);
		};
	}
}


#endif //QUASARFX_MTLGENERATOR_H
