//
// Created by darkboss on 9/5/20.
//

#include <core/Location.h>
#include <core/Parser.h>
#include "ObjParser.h"

namespace quasar {
	namespace formats {
		ObjParser::ObjParser()
			: base_type({
	            {lexer_type::Space, std::bind(&self_type::parseSpace, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Comment, std::bind(&self_type::parseComment, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Vertex, std::bind(&self_type::parseVertex, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Normal, std::bind(&self_type::parseNormal, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::TextureCoord, std::bind(&self_type::parseTextureCoord, this, std::placeholders::_1, std::placeholders::_2)},
	            {lexer_type::FreeFormVertex, std::bind(&self_type::parseFreeFormVertex, this, std::placeholders::_1, std::placeholders::_2)},
	            {lexer_type::MaterialImport, std::bind(&self_type::parseMaterialImport, this, std::placeholders::_1, std::placeholders::_2)},
	            {lexer_type::MaterialUsage, std::bind(&self_type::parseMaterialUsage, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Face, std::bind(&self_type::parseFace, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Line, std::bind(&self_type::parseLine, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Number, std::bind(&self_type::parseNumber, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Object, std::bind(&self_type::parseObject, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Group, std::bind(&self_type::parseGroup, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::FaceElem, std::bind(&self_type::parseFaceElem, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::NewLine, std::bind(&self_type::parseNewLine, this, std::placeholders::_1, std::placeholders::_2)},
            })
            , mInComment(false)
			, mRootObject(nullptr)
            , mCurrentObject(nullptr)
            , mCurrentGroup(nullptr)
		{
			setAnyTokenFunc(std::bind(&self_type::parseAny, this, std::placeholders::_1, std::placeholders::_2));
		}

		void ObjParser::reset() {
			base_type::reset();
			mInComment = false;
			mRootObject = &mResult;
			mCurrentObject = &mResult;
			mCurrentGroup = &mResult;
		}

		void ObjParser::parse(const token_list &tokens, core::Mesh &into) {
			base_type::parse(tokens, into);
		}

		void ObjParser::parseSpace(const token_list *tokens, typename token_list::citer_type &it) {
		}
		void ObjParser::parseComment(const token_list *tokens, typename token_list::citer_type &it) {
			mInComment = true;
		}

		void ObjParser::parseVertex(const token_list *tokens, typename token_list::citer_type &it) {
			if (!mInComment) {
				core::String str;
				token_list args = getArgs(it, {ObjLexer::Number}, &str);
				if (args.size() != 3 && args.size() != 4) {
					throw quasar::core::SyntaxError("invalid vertex declaration, should be 'v <x> <y> <z> [w]' in '" + str + "'", it->getLocation(), QUASAR_SOURCE_LOCATION);
				}
				createVertex(args.at(0).getTextAs<float>(), args.at(1).getTextAs<float>(), args.at(2).getTextAs<float>(), args.size() == 4 ? args.at(3).getTextAs<float>() : 1.0f);
			}
		}
		void ObjParser::parseNormal(const token_list *tokens, typename token_list::citer_type &it) {
			if (!mInComment) {
				core::String str;
				token_list args = getArgs(it, {ObjLexer::Number}, &str);
				if (args.size() != 3) {
					throw quasar::core::SyntaxError("invalid normal declaration, should be 'vn <x> <y> <z>' in '" + str + "'", it->getLocation(), QUASAR_SOURCE_LOCATION);
				}
				createNormal(args.at(0).getTextAs<float>(), args.at(1).getTextAs<float>(), args.at(2).getTextAs<float>());
			}
		}
		void ObjParser::parseTextureCoord(const token_list *tokens, typename token_list::citer_type &it) {
			if (!mInComment) {
				core::String str;
				token_list args = getArgs(it, {ObjLexer::Number}, &str);
				if (args.empty() || args.size() > 3) {
					throw quasar::core::SyntaxError("invalid texture coord declaration, should be 'vt <u> [v] [w]' in '" + str + "'", it->getLocation(), QUASAR_SOURCE_LOCATION);
				}
				auto u = args.at(0).getTextAs<float>();
				auto v = args.size() == 2 ? args.at(1).getTextAs<float>() : 0.0f;
				auto w = args.size() == 3 ? args.at(2).getTextAs<float>() : 0.0f;
				createTexCoord(u, v, w);
			}
		}
		void ObjParser::parseFreeFormVertex(const token_list *tokens, typename token_list::citer_type &it) {

		}
		void ObjParser::parseFace(const token_list *tokens, typename token_list::citer_type &it) {
			core::String str;
			token_list args = getArgs(it, {ObjLexer::FaceElem, ObjLexer::Number}, &str);
			if (args.size() != 3 && args.size() != 4) {
				throw quasar::core::SyntaxError("invalid face declaration, should be 'f <v0> <v1> <v2>', 'f <v0> <v1> <v2> <v3>', 'f <v0>/<vn0> <v1>/<vn1> <v2>/<vn2>', 'f <v0>/<vn0>/<vt0> <v1>/<vn1>/<vt1> <v2>/<vn2>/<vt2>' or 'f <v0>//<vt0> <v1>//<vt1> <v2>//<vt2>' in '" + str + "'", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			std::vector<core::String> a0 = args.at(0).getText().split("/", core::SPLIT_KEEP_EMPTY | core::SPLIT_TRIM), a1 = args.at(1).getText().split("/", core::SPLIT_KEEP_EMPTY | core::SPLIT_TRIM), a2 = args.at(2).getText().split("/", core::SPLIT_KEEP_EMPTY | core::SPLIT_TRIM), a3;
			core::GeometryBuffer::quad_type::index_type vertices[4] = {0};
			core::GeometryBuffer::quad_type::index_type normals[4] = {0};
			core::GeometryBuffer::quad_type::index_type texCoords[4] = {0};
			auto get_indices = [&](size_t n, std::vector<core::String> &parts) {
				std::basic_stringstream<Char> buf;
				buf.clear(); buf.str(parts[0]);
				buf >> vertices[n];
				if (parts.size() > 1) {
					buf.clear();
					buf.str(parts[1]);
					buf >> texCoords[n];
				}
				if (parts.size() > 2) {
					buf.clear();
					buf.str(parts[2]);
					buf >> normals[n];
				}
			};
			get_indices(0, a0);
			get_indices(1, a1);
			get_indices(2, a2);
			if (args.size() == 4) {
				a3 = args.at(3).getText().split("/", core::SPLIT_KEEP_EMPTY | core::SPLIT_TRIM);
				get_indices(3, a3);
				createQuad(vertices, texCoords, normals);
			} else {
				createTriangle(vertices, texCoords, normals);
			}
		}
		void ObjParser::parseLine(const token_list *tokens, typename token_list::citer_type &it) {

		}
		void ObjParser::parseNumber(const token_list *tokens, typename token_list::citer_type &it) {

		}
		void ObjParser::parseFaceElem(const token_list *tokens, typename token_list::citer_type &it) {

		}
		void ObjParser::parseNewLine(const token_list *tokens, typename token_list::citer_type &it) {
			mInComment = false;
		}

		void ObjParser::parseObject(const ObjParser::token_list *tokens, typename token_list::citer_type &it) {
			auto name = it->getText();
			if (!mRootObject->hasSubMesh(name)) {
				mCurrentObject = mRootObject->createSubMesh(name).get();
			} else {
				mCurrentObject = mRootObject->getSubMesh(name).get();
			}
			mCurrentGroup = mCurrentObject;
		}

		void ObjParser::parseGroup(const ObjParser::token_list *tokens, typename token_list::citer_type &it) {
			auto name = it->getText();
			if (!mCurrentObject->hasSubMesh(name)) {
				mCurrentGroup = mCurrentObject->createSubMesh(name).get();
			} else {
				mCurrentGroup = mCurrentObject->getSubMesh(name).get();
			}
		}

		void ObjParser::parseAny(const ObjParser::token_list *tokens, typename token_list::citer_type &it) {
//			std::cout << "got token: " << it->getName() << std::endl;
		}

		void ObjParser::createVertex(float x, float y, float z, float w) {
			typename core::GeometryBuffer::vertex_type vert;
			vert.data(0) = x;
			vert.data(1) = y;
			vert.data(2) = z;
			vert.data(3) = w;
			mCurrentGroup->getGeometry()->addVertex(vert);
		}

		void ObjParser::createNormal(float x, float y, float z) {
			typename core::GeometryBuffer::normal_type norm;
			norm.data(0) = x;
			norm.data(1) = y;
			norm.data(2) = z;
			mCurrentGroup->getGeometry()->addNormal(norm);
		}

		void ObjParser::createTexCoord(float u, float v, float w) {
			typename core::GeometryBuffer::tex_coord_type tc;
			tc.data(0) = u;
			tc.data(1) = v;
			tc.data(2) = w;
			mCurrentGroup->getGeometry()->addTexCoord(tc);
		}

		void ObjParser::createQuad(core::GeometryBuffer::triangle_type::index_type v[3],
		                           core::GeometryBuffer::triangle_type::index_type vt[3],
		                           core::GeometryBuffer::triangle_type::index_type vn[3]) {
			core::GeometryBuffer::quad_type quad;
			for (unsigned char i = 0; i < 4; i++) {
				if (v[i] != 0) {
					quad.setVertex(i, convertRelativeIndexToAbsolute(v[i], DT_VERTEX));
				}
				if (vt[i] != 0) {
					quad.setTexCoord(i, convertRelativeIndexToAbsolute(vt[i], DT_TEXCOORD));
				}
				if (vn[i] != 0) {
					quad.setNormal(i, convertRelativeIndexToAbsolute(vn[i], DT_NORMAL));
				}
			}
			mCurrentGroup->getGeometry()->addQuad(quad);
		}

		void ObjParser::createTriangle(core::GeometryBuffer::triangle_type::index_type v[3],
		                               core::GeometryBuffer::triangle_type::index_type vt[3],
		                               core::GeometryBuffer::triangle_type::index_type vn[3]) {
			core::GeometryBuffer::triangle_type tri;
			for (unsigned char i = 0; i < 3; i++) {
				if (v[i] != 0) {
					tri.setVertex(i, convertRelativeIndexToAbsolute(v[i], DT_VERTEX));
				}
				if (vt[i] != 0) {
					tri.setTexCoord(i, convertRelativeIndexToAbsolute(vt[i], DT_TEXCOORD));
				}
				if (vn[i] != 0) {
					tri.setNormal(i, convertRelativeIndexToAbsolute(vn[i], DT_NORMAL));
				}
			}
			mCurrentGroup->getGeometry()->addTriangle(tri);
		}

		ObjParser::token_list ObjParser::getArgs(typename token_list::citer_type &it, const std::vector<core::Token> &argTypes, core::String *str) {
			token_list args;
			bool validArgType;
			while (it->getType() != ObjLexer::NewLine.getType()) {
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
					std::cout << "getArgs(" << args.size() << ") = " << *it << " / " << (str != nullptr ? *str : core::String()) << std::endl;
				}
#endif
				it++;
			}
			return args;
		}

		unsigned long long ObjParser::convertRelativeIndexToAbsolute(long long idx, DataType type) {
			long long ret = idx;
			if (ret < 0) {
				switch (type) {
					case DT_VERTEX:
						ret += (long long)mCurrentGroup->getGeometry()->getVertices().size();
						break;
					case DT_NORMAL:
						ret += (long long)mCurrentGroup->getGeometry()->getNormals().size();
						break;
					case DT_TEXCOORD:
						ret += (long long)mCurrentGroup->getGeometry()->getTexCoords().size();
						break;
					default:
						throw std::runtime_error("unknown data type: " + std::to_string(type));
				}
			} else {
				ret--;
			}
			return (unsigned long long)ret;
		}

		void ObjParser::parseMaterialImport(const token_list *tokens, typename token_list::citer_type &it) {
			auto args = getArgs(it);
			if (args.empty()) {
				throw core::SyntaxError("Cannot import material, no arguments given to 'mtllib'", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			std::cout << "Importing material: " << args.at(0) << std::endl;
		}

		void ObjParser::parseMaterialUsage(const token_list *tokens, typename token_list::citer_type &it) {
			auto args = getArgs(it);
			if (args.empty()) {
				throw core::SyntaxError("Cannot use material, no arguments given to 'usemtl'", it->getLocation(), QUASAR_SOURCE_LOCATION);
			}
			std::cout << "Using material: " << args.at(0) << std::endl;
		}

	}
}