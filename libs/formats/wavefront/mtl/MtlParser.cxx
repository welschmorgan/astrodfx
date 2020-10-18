//
// Created by darkboss on 9/5/20.
//

#include <core/Location.h>
#include <core/Parser.h>
#include <core/Color.h>
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
				{MtlLexer::ColorSpecularPower, std::bind(&self_type::parseColorSpecularPower, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::ColorTransparency, std::bind(&self_type::parseColorTransparency, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::ColorDissolve, std::bind(&self_type::parseColorDissolve, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::IlluminationModel, std::bind(&self_type::parseIlluminationModel, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::NewLine, std::bind(&self_type::parseNewLine, this, std::placeholders::_1, std::placeholders::_2)},
				{MtlLexer::Text, std::bind(&self_type::parseText, this, std::placeholders::_1, std::placeholders::_2)},
            })
            , mCurrentMaterial(nullptr)
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
			getArgs(argIter, {}, &argStr);
			argStr.trim().unquote();
			if (argStr.empty()) {
				throw core::SyntaxError("'newmtl' command requires exactly one argument, none given: the name of the material to be created", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto  mat = std::make_shared<core::Material>();
			mat->setName(argStr.trim());
			mResult.add(mat);
			mCurrentMaterial = mResult->back();
			it = argIter;
		}

		void MtlParser::assertMaterialExists(typename token_list::citer_type &command) const {
			if (!mCurrentMaterial) {
				throw core::SyntaxError("'" + command->getText() + "' command requires a pre-existing material, but 'newmtl' command not yet encountered", command->getLocation(), QUASAR_SOURCE_LOCATION);
			}
		}

		void MtlParser::parseColorAmbient(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getArgs(it, {MtlLexer::Number});
			if (args.size() != 3) {
				throw core::SyntaxError("'Ka' command requires exactly 3 arguments but " + std::to_string(args.size()) + " given: <r> <g> <b>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			core::Color4f amb;
			amb.r = args[0].getTextAs<float>();
			amb.g = args[1].getTextAs<float>();
			amb.b = args[2].getTextAs<float>();
			mCurrentMaterial->setAmbient(amb);
		}

		void MtlParser::parseColorDiffuse(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getArgs(it, {MtlLexer::Number});
			if (args.size() != 3) {
				throw core::SyntaxError("'Kd' command requires exactly 3 arguments but " + std::to_string(args.size()) + " given: <r> <g> <b>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			core::Color4f diff;
			diff.r = args[0].getTextAs<float>();
			diff.g = args[1].getTextAs<float>();
			diff.b = args[2].getTextAs<float>();
			mCurrentMaterial->setDiffuse(diff);
		}

		void MtlParser::parseColorSpecular(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getArgs(it, {MtlLexer::Number});
			if (args.size() != 3) {
				throw core::SyntaxError("'Ks' command requires exactly 3 arguments but " + std::to_string(args.size()) + " given: <r> <g> <b>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			core::Color4f spec;
			spec.r = args[0].getTextAs<float>();
			spec.g = args[1].getTextAs<float>();
			spec.b = args[2].getTextAs<float>();
			mCurrentMaterial->setSpecular(spec);
		}

		void MtlParser::parseColorSpecularPower(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getArgs(it, {MtlLexer::Number});
			if (args.size() != 1) {
				throw core::SyntaxError("'Ns' command requires exactly 1 argument but " + std::to_string(args.size()) + " given: <power>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto shin = args[0].getTextAs<float>();
			mCurrentMaterial->setShininess(shin);
		}

		void MtlParser::parseIlluminationModel(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getArgs(it, {MtlLexer::Number});
			if (args.size() != 1) {
				throw core::SyntaxError("'illum' command requires exactly 1 argument but " + std::to_string(args.size()) + " given: <model_id>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto illum = args[0].getTextAs<int>();
		}

		void MtlParser::parseNewLine(const token_list *tokens, typename token_list::citer_type &it) {
		}

		void MtlParser::parseText(const token_list *tokens, typename token_list::citer_type &it) {
		}

		MtlParser::token_list   MtlParser::getArgs(typename MtlParser::token_list::citer_type &it, const std::vector<core::Token> &argTypes, core::String *str) {
			MtlParser::token_list args;
			bool validArgType;
			while (it->getType() != MtlLexer::NewLine.getType()) {
				validArgType = argTypes.empty();
				for (auto const &argType: argTypes) {
					if (argType.getType() == it->getType()) {
						validArgType = true;
						break;
					}
				}
				if (validArgType) {
					args.add(*it);
				}
				if (str) {
					*str += it->getText();
				}
#ifndef NDEBUG
				if (validArgType) {
					std::cout << "getArgs(" << args.size() << ") = " << *it << (str != nullptr ? (" / " + *str) : core::String()) << std::endl;
				}
#endif
				it++;
			}
			return args;
		}

		void MtlParser::parseColorTransparency(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getArgs(it, {MtlLexer::Number});
			if (args.size() != 1) {
				throw core::SyntaxError("'Tr' command requires exactly 1 argument but " + std::to_string(args.size()) + " given: <amount>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto tr = args[0].getTextAs<float>();
			auto diff = mCurrentMaterial->getDiffuse();
			auto amb = mCurrentMaterial->getAmbient();
			diff.a = 1 - tr;
			amb.a = 1 - tr;
			mCurrentMaterial->setDiffuse(diff);
			mCurrentMaterial->setAmbient(amb);
		}

		void MtlParser::parseColorDissolve(const token_list *tokens, typename token_list::citer_type &it) {
			assertMaterialExists(it);
			auto args = getArgs(it, {MtlLexer::Number});
			if (args.size() != 1) {
				throw core::SyntaxError("'d' command requires exactly 1 argument but " + std::to_string(args.size()) + " given: <amount>", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			auto d = args[0].getTextAs<float>();
			auto diff = mCurrentMaterial->getDiffuse();
			auto amb = mCurrentMaterial->getAmbient();
			diff.a = d;
			amb.a = d;
			mCurrentMaterial->setDiffuse(diff);
			mCurrentMaterial->setAmbient(amb);
		}
	}
}