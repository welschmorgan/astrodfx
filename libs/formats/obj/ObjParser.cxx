//
// Created by darkboss on 9/5/20.
//

#include <core/Location.h>
#include "ObjParser.h"

namespace quasar {
	namespace formats {
		ObjParser::ObjParser()
			: MeshParser({
	            {lexer_type::Space.getType(), std::bind(&self_type::parseSpace, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Comment.getType(), std::bind(&self_type::parseComment, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Vertex.getType(), std::bind(&self_type::parseVertex, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Normal.getType(), std::bind(&self_type::parseNormal, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::TextureCoord.getType(), std::bind(&self_type::parseTextureCoord, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::FreeFormVertex.getType(), std::bind(&self_type::parseFreeFormVertex, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Face.getType(), std::bind(&self_type::parseFace, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Line.getType(), std::bind(&self_type::parseLine, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Number.getType(), std::bind(&self_type::parseNumber, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Object.getType(), std::bind(&self_type::parseObject, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::Group.getType(), std::bind(&self_type::parseGroup, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::FaceElem.getType(), std::bind(&self_type::parseFaceElem, this, std::placeholders::_1, std::placeholders::_2)},
                {lexer_type::NewLine.getType(), std::bind(&self_type::parseNewLine, this, std::placeholders::_1, std::placeholders::_2)},
            })
            , mInComment(false)
			, mRootObject(nullptr)
            , mCurrentObject(nullptr)
            , mCurrentGroup(nullptr)
		{
			setAnyTokenFunc(std::bind(&self_type::parseAny, this, std::placeholders::_1, std::placeholders::_2));
		}

		void ObjParser::reset() {
			MeshParser::reset();
			mInComment = false;
			mRootObject = &mResult;
			mCurrentObject = &mResult;
			mCurrentGroup = &mResult;
		}

		void ObjParser::parse(const token_list &tokens, core::Mesh &into) {
			MeshParser::parse(tokens, into);
		}

		void ObjParser::parseSpace(const token_list *tokens, typename token_list::citer_type &it) {
		}
		void ObjParser::parseComment(const token_list *tokens, typename token_list::citer_type &it) {
			mInComment = true;
			std::cout << (it->getText()) << std::endl;
		}

		void ObjParser::parseVertex(const token_list *tokens, typename token_list::citer_type &it) {
			if (!mInComment) {
				core::String str;
				token_list args = getArgs(it, &str);
				if (args.size() != 3 && args.size() != 4) {
					throw quasar::core::SyntaxError("invalid vertex declaration, should be 'v <x> <y> <z> [w]' in '" + str + "'", it->getLocation(), QUASAR_SOURCE_LOCATION);
				}
				createVertex(args.at(0).getTextAs<float>(), args.at(1).getTextAs<float>(), args.at(2).getTextAs<float>(), args.size() == 4 ? args.at(3).getTextAs<float>() : 1.0f);
			}
		}
		void ObjParser::parseNormal(const token_list *tokens, typename token_list::citer_type &it) {
			if (!mInComment) {
				core::String str;
				token_list args = getArgs(it, &str);
				if (args.size() != 3) {
					throw quasar::core::SyntaxError("invalid normal declaration, should be 'vn <x> <y> <z>' in '" + str + "'", it->getLocation(), QUASAR_SOURCE_LOCATION);
				}
				createNormal(args.at(0).getTextAs<float>(), args.at(1).getTextAs<float>(), args.at(2).getTextAs<float>());
			}
		}
		void ObjParser::parseTextureCoord(const token_list *tokens, typename token_list::citer_type &it) {
			if (!mInComment) {
				core::String str;
				token_list args = getArgs(it, &str);
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
			std::cout << "got token: " << it->getName() << std::endl;
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

		ObjParser::token_list ObjParser::getArgs(typename token_list::citer_type &it, core::String *str) {
			token_list args;
			while (it->getType() != ObjLexer::NewLine.getType()) {
				if (it->getType() == ObjLexer::Number.getType()) {
					args.add(*it);
				}
				if (str) {
					*str += it->getText();
				}
				it++;
			}
			return args;
		}

	}
}