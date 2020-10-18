//
// Created by darkboss on 9/5/20.
//

#include <core/Location.h>
#include <core/Parser.h>
#include <core/Color.h>
#include <core/String.h>
#include "MtlParser.h"

namespace quasar {
	namespace formats {
		MtlParser::MtlParser()
			: base_type ({
				{MtlLexer::Space, std::bind(&self_type::parseSpace, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::Comment, std::bind(&self_type::parseComment, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::Material, std::bind(&self_type::parseMaterial, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::ColorAmbient, std::bind(&self_type::parseColorAmbient, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::ColorDiffuse, std::bind(&self_type::parseColorDiffuse, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::ColorSpecular, std::bind(&self_type::parseColorSpecular, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::ColorSpecularPower, std::bind(&self_type::parseSpecularPower, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::ColorTransparency, std::bind(&self_type::parseTransparency, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::ColorDissolve, std::bind(&self_type::parseDissolve, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::IlluminationModel, std::bind(&self_type::parseIlluminationModel, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::NewLine, std::bind(&self_type::parseNewLine, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::Text, std::bind(&self_type::parseText, this, std::placeholders::_1, std::placeholders::_2)},
            })
            , mCurrentMaterial()
            , mCurrentPass()
		{}

		void MtlParser::reset() {
			mResult.clear();
			mCurrentMaterial = nullptr;
		}

		void MtlParser::parse(const token_list &tokens, core::SharedMaterialList &into) {
			base_type::parse(tokens, into);
		}

		void MtlParser::parseSpace(const token_list *tokens, typename token_list::citer_type &it) {
		}

		void MtlParser::parseComment(const token_list *tokens, typename token_list::citer_type &it) {
		}

		void MtlParser::parseMaterial(const token_list *tokens, typename token_list::citer_type &it) {
			core::String argStr;
			auto argIter = it + 1;
			getUntil(argIter, {}, &argStr, {MtlLexer::NewLine});
			argStr.trim().unquote();
			if (argStr.empty()) {
				throw core::SyntaxError("'newmtl' command requires exactly one argument, none given: the name of the material to be created", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto nameParts = argStr.split(":", 2, core::SPLIT_KEEP_EMPTY | core::SPLIT_TRIM);
			core::SharedMaterial mat;
			for (auto const &m: mResult) {
				if (m && m->getName() == nameParts[0]) {
					mat = m;
					break;
				}
			}
			if (!mat) {
				mat.reset(new core::Material());
				if (nameParts.size() >= 2) {
					mCurrentPass = mat->getFirstPass();
				}
			} else if (nameParts.size() >= 2) {
				for (auto const &p: mat->getPasses()) {
					if (p && p->getName() == nameParts[1]) {
						mCurrentPass = p;
						break;
					}
				}
			}
			mat->setName(nameParts[0]);
			if (nameParts.size() >= 2) {
				mCurrentPass->setName(nameParts[1]);
			}
			mResult.add(mat);
			mCurrentMaterial = mResult->back();
			it = argIter;
		}

		void MtlParser::parseColorAmbient(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto col = parseColor(tokens, it).toColor();
			mCurrentPass->setAmbient(col.widen());
		}

		void MtlParser::parseColorDiffuse(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto col = parseColor(tokens, it).toColor();
			mCurrentPass->setDiffuse(col.widen());
		}

		void MtlParser::parseColorSpecular(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto col = parseColor(tokens, it).toColor();
			mCurrentPass->setSpecular(col.widen());
		}

		void MtlParser::parseSpecularPower(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getUntil(it, {MtlLexer::Number}, nullptr, {MtlLexer::NewLine});
			if (args.size() != 1) {
				throw core::SyntaxError("'Ns' command requires exactly 1 argument but " + std::to_string(args.size()) + " given: <power>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto shin = args[0].getTextAs<float>();
			mCurrentPass->setShininess(shin);
		}

		void MtlParser::parseTransparency(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getUntil(it, {MtlLexer::Number}, nullptr, {MtlLexer::NewLine});
			if (args.size() != 1) {
				throw core::SyntaxError("'Tr' command requires exactly 1 argument but " + std::to_string(args.size()) + " given: <amount>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto tr = args[0].getTextAs<float>();
			auto diff = mCurrentPass->getDiffuse();
			diff.a = 1 - tr;
			mCurrentPass->setDiffuse(diff);
		}

		void MtlParser::parseDissolve(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getUntil(it, {MtlLexer::Number}, nullptr, {MtlLexer::NewLine});
			if (args.size() != 1) {
				throw core::SyntaxError("'d' command requires exactly 1 argument but " + std::to_string(args.size()) + " given: <amount>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto d = args[0].getTextAs<float>();
			auto diff = mCurrentPass->getDiffuse();
			diff.a = d;
			mCurrentPass->setDiffuse(diff);
		}

		void MtlParser::parseIlluminationModel(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getUntil(it, {MtlLexer::Number}, nullptr, {MtlLexer::NewLine});
			if (args.size() != 1) {
				throw core::SyntaxError("'illum' command requires exactly 1 argument but " + std::to_string(args.size()) + " given: <model_id>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto illum = args[0].getTextAs<int>();
		}

		void MtlParser::parseNewLine(const token_list *tokens, typename token_list::citer_type &it) {
		}

		void MtlParser::parseText(const token_list *tokens, typename token_list::citer_type &it) {
		}

		void MtlParser::assertMaterialExists(typename token_list::citer_type &command) const {
			if (!mCurrentMaterial) {
				throw core::SyntaxError("'" + command->getText() + "' command requires a pre-existing material, but 'newmtl' command not yet encountered", command->getLocation(), QUASAR_SOURCE_LOCATION);
			}
		}

		void MtlParser::assertPassExists(typename token_list::citer_type &command) const {
			if (!mCurrentPass) {
				throw core::SyntaxError("'" + command->getText() + "' command requires a pre-existing material pass, but 'newmtl' command not yet encountered", command->getLocation(), QUASAR_SOURCE_LOCATION);
			}
		}

		MtlColor MtlParser::parseColor(const token_list *tokens, typename token_list::citer_type &it) {
			MtlColor col;
			core::String argStr;
			auto args = getUntil(it, {MtlLexer::XYZ, MtlLexer::Spectral, MtlLexer::Number}, &argStr, {MtlLexer::NewLine});
			if (!args.empty()) {
				if (args[0] == MtlLexer::Number) {
					if (args.size() < 1 || args.size() > 3) {
						throw core::SyntaxError(
								"invalid rgb color format, expected '<r> [g] [b]', got '" + argStr + "'",
								it->getLocation(), QUASAR_SOURCE_LOCATION);
					}
					col = MtlColor::fromRGB(args[0].getTextAs<float>(), args[1].getTextAs<float>(),
					                        args[2].getTextAs<float>());
				} else if (args[0] == MtlLexer::XYZ) {
					if (args.size() < 1 || args.size() > 3) {
						throw core::SyntaxError(
								"invalid xyz color format, expected '<x> [y] [z]', got '" + argStr + "'",
								it->getLocation(), QUASAR_SOURCE_LOCATION);
					}
					col = MtlColor::fromXYZ(args[0].getTextAs<float>(), args[1].getTextAs<float>(),
					                        args[2].getTextAs<float>());
				} else if (args[0] == MtlLexer::Spectral) {
					if (args.size() < 1 || args.size() > 3) {
						throw core::SyntaxError(
								"invalid spectral color format, expected '<file> <factor>', got '" + argStr + "'",
								it->getLocation(), QUASAR_SOURCE_LOCATION);
					}
					auto refl_file = args[1].getText();
					col = MtlColor::fromSpectral(refl_file.data(), args[1].getTextAs<float>());
					col.rgb.b = args[2].getTextAs<float>();
				} else {
					throw core::SyntaxError("unrecognized color format", it->getLocation(),
					                        QUASAR_SOURCE_LOCATION);
				}
			} else {
				throw core::SyntaxError("unexpected end of text", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			return col;
		}

	}
}