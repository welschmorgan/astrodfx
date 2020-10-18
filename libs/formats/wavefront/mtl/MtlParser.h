//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_MTLPARSER_H
#define QUASARFX_MTLPARSER_H

#include <core/Parser.h>
#include <core/Exception.h>
#include <core/String.h>
#include <core/Config.h>
#include <core/GeometryBuffer.h>
#include <core/Mesh.h>
#include <core/Parser.h>
#include <core/Lexer.h>
#include "MtlLexer.h"

namespace quasar {
	namespace formats {
		struct MtlColor {
			enum type {
				NONE,
				XYZ,
				RGB,
				SPECTRAL
			};

			struct data_rgb {
				float r, g, b;
			};

			struct data_xyz {
				float x, y, z;
			};

			struct data_spectral {
				Char            refl_file[255];
				float           factor;
			};

			type type;
			union {
				decltype(nullptr) none;
				data_xyz xyz;
				data_rgb rgb;
				data_spectral spectral;
			};

			static MtlColor fromRGB(float r, float g, float b) {
				MtlColor col;
				col.type = RGB;
				col.rgb = {r, g, b};
				return col;
			}

			static MtlColor fromXYZ(float x, float y, float z) {
				MtlColor col;
				col.type = XYZ;
				col.rgb = {x, y, z};
				return col;
			}

			static MtlColor fromSpectral(const Char *file, float factor) {
				MtlColor col;
				col.type = SPECTRAL;
				col.spectral.factor = factor;
				std::function<Char *(Char*, const Char*, size_t)> fn;
#ifdef UNICODE
				fn = wcsncpy;
#else
				fn = strncpy;
#endif
				fn(col.spectral.refl_file, file, 255);
				return col;
			}

			MtlColor(enum type t = NONE): type(NONE), none() {}
			MtlColor(const MtlColor &rhs): type(rhs.type), none() {
				*this = rhs;
			}
			~MtlColor() {}

			MtlColor        &operator=(const MtlColor &rhs) {
				type = rhs.type;
				switch (type) {
					case NONE:
						none = rhs.none;
						break;
					case XYZ:
						xyz = rhs.xyz;
						break;
					case RGB:
						rgb = rhs.rgb;
						break;
					case SPECTRAL:
						spectral = rhs.spectral;
						break;
				}
				return *this;
			}

			core::Color3f   toColor() const {
				switch (type) {
					case RGB:
						return core::Color3f(rgb.r, rgb.g, rgb.b);
					case XYZ:
						throw std::runtime_error("cannot transform xyz color to internal format, not yet implemented");
					case SPECTRAL:
						throw std::runtime_error("cannot transform spectral color to internal format, not yet implemented");
					case NONE:
					default:
						throw std::runtime_error("cannot transform color to internal format, type is 'NONE'");
				}
			}
		};

		class MtlParser
			: public core::BasicParser<Char, core::SharedMaterialList, core::Lexer>
		{
		public:
			using lexer_type                    = MtlLexer;
			using self_type                     = MtlParser;
			using base_type                     = core::BasicParser<Char, core::SharedMaterialList, core::Lexer>;
			using token_type                    = typename base_type::token_type;
			using id_type                       = typename token_type::id_type;
			using token_list                    = typename base_type::token_list;
			using result_type                   = typename base_type::result_type;

		protected:
			core::SharedMaterial                mCurrentMaterial;
			core::SharedMaterialPass            mCurrentPass;

		public:
			MtlParser();
			MtlParser(const MtlParser &rhs) = delete;
			virtual ~MtlParser() = default;

			MtlParser                           &operator=(const MtlParser &rhs) = delete;

			void                                reset() override;
			void                                parse(const token_list &tokens, core::SharedMaterialList &into) override;

		protected:
			MtlColor                            parseColor(const token_list *tokens, typename token_list::citer_type &it);


			void                                parseSpace(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseComment(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseMaterial(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorAmbient(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorDiffuse(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseColorSpecular(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseSpecularPower(const token_list *tokens,
			                                                       typename token_list::citer_type &it);
			void                                parseTransparency(const token_list *tokens,
			                                                      typename token_list::citer_type &it);
			void                                parseDissolve(const token_list *tokens,
			                                                  typename token_list::citer_type &it);
			void                                parseIlluminationModel(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseNewLine(const token_list *tokens, typename token_list::citer_type &it);
			void                                parseText(const token_list *tokens, typename token_list::citer_type &it);

			void                                assertMaterialExists(typename token_list::citer_type &command) const;
			void                                assertPassExists(typename token_list::citer_type &command) const;
		};
	}
}


#endif //QUASARFX_MTLPARSER_H
