//
// Created by darkboss on 10/3/20.
//

#include "GeometryBuffer.h"

namespace quasar {
	namespace core {

		GeometryBuffer::GeometryBuffer(const String &name_, const GeometryBuffer::vertex_list &v,
		                               const GeometryBuffer::normal_list &n, const GeometryBuffer::tex_coord_list &tc,
		                               const GeometryBuffer::triangle_list &triangles,
		                               const GeometryBuffer::quad_list &quads)
			: mName(name_)
			, mVertices(v)
			, mNormals(n)
			, mTexCoords(tc)
			, mTriangles(triangles)
			, mQuads(quads)
		{}

		const Collection<GeometryBuffer::vertex_type> &GeometryBuffer::getVertices() const {
			return mVertices;
		}

		void GeometryBuffer::setVertices(const Collection<GeometryBuffer::vertex_type> &vertices) {
			GeometryBuffer::mVertices = vertices;
		}

		const Collection<GeometryBuffer::normal_type> &GeometryBuffer::getNormals() const {
			return mNormals;
		}

		void GeometryBuffer::setNormals(const Collection<GeometryBuffer::normal_type> &normals) {
			GeometryBuffer::mNormals = normals;
		}

		const Collection<GeometryBuffer::tex_coord_type> &GeometryBuffer::getTexCoords() const {
			return mTexCoords;
		}

		void GeometryBuffer::setTexCoords(const Collection<GeometryBuffer::tex_coord_type> &texCoords) {
			GeometryBuffer::mTexCoords = texCoords;
		}

		const Collection<GeometryBuffer::triangle_type> &GeometryBuffer::getTriangles() const {
			return mTriangles;
		}

		void GeometryBuffer::setTriangles(const Collection<GeometryBuffer::triangle_type> &triangles) {
			GeometryBuffer::mTriangles = triangles;
		}

		const Collection<GeometryBuffer::quad_type> &GeometryBuffer::getQuads() const {
			return mQuads;
		}

		void GeometryBuffer::setQuads(const Collection<GeometryBuffer::quad_type> &quads) {
			GeometryBuffer::mQuads = quads;
		}

		GeometryBuffer &GeometryBuffer::addVertex(const GeometryBuffer::vertex_type &v) {
			mVertices.add(v);
			return *this;
		}

		GeometryBuffer &GeometryBuffer::addNormal(const GeometryBuffer::normal_type &v) {
			mNormals.add(v);
			return *this;
		}

		GeometryBuffer &GeometryBuffer::addTexCoord(const GeometryBuffer::tex_coord_type &tc) {
			mTexCoords.add(tc);
			return *this;
		}

		GeometryBuffer &GeometryBuffer::addTriangle(const GeometryBuffer::triangle_type &v) {
			mTriangles.add(v);
			return *this;
		}

		GeometryBuffer &GeometryBuffer::addTriangle(triangle_type::index_type v0, triangle_type::index_type v1, triangle_type::index_type v2,
		                                            triangle_type::index_type vn0, triangle_type::index_type vn1, triangle_type::index_type vn2,
		                                            triangle_type::index_type vt0, triangle_type::index_type vt1, triangle_type::index_type vt2) {
			mTriangles.add(triangle_type({v0, v1, v2}, {vn0, vn1, vn2}, {vt0, vt1, vt2}));
			return *this;
		}

		GeometryBuffer &GeometryBuffer::addQuad(const quad_type &v) {
			mQuads.add(v);
			return *this;
		}

		GeometryBuffer &GeometryBuffer::addQuad(quad_type::index_type v0, quad_type::index_type v1, quad_type::index_type v2, quad_type::index_type v3,
		                                        quad_type::index_type vn0, quad_type::index_type vn1, quad_type::index_type vn2, quad_type::index_type vn3,
		                                        quad_type::index_type vt0, quad_type::index_type vt1, quad_type::index_type vt2, quad_type::index_type vt3) {
			mQuads.add(quad_type({v0, v1, v2, v3}, {vn0, vn1, vn2, vn3}, {vt0, vt1, vt2, vt3}));
			return *this;
		}

		const String &GeometryBuffer::getName() const {
			return mName;
		}

		void GeometryBuffer::setName(const String &name) {
			mName = name;
		}

		std::basic_ostream<char>        &operator<<(std::basic_ostream<char> &os, const IndexedFace<3> &f) {
			os << "v0 = (v: " << (f.hasVertex(0) ? std::to_string(f.getVertex(0)) : "<none>") << ", vt: " << (f.hasTexCoord(0) ? std::to_string(f.getTexCoord(0)) : "<none>") << ", vn: " << (f.hasNormal(0) ? std::to_string(f.getNormal(0)) : "<none>") << ") ";
			os << "v1 = (v: " << (f.hasVertex(1) ? std::to_string(f.getVertex(1)) : "<none>") << ", vt: " << (f.hasTexCoord(1) ? std::to_string(f.getTexCoord(1)) : "<none>") << ", vn: " << (f.hasNormal(1) ? std::to_string(f.getNormal(1)) : "<none>") << ") ";
			os << "v2 = (v: " << (f.hasVertex(2) ? std::to_string(f.getVertex(2)) : "<none>") << ", vt: " << (f.hasTexCoord(2) ? std::to_string(f.getTexCoord(2)) : "<none>") << ", vn: " << (f.hasNormal(2) ? std::to_string(f.getNormal(2)) : "<none>") << ")";
			return os;
		}

		std::basic_ostream<char>        &operator<<(std::basic_ostream<char> &os, const IndexedFace<4> &f) {
			os << "v0 = (v: " << (f.hasVertex(0) ? std::to_string(f.getVertex(0)) : "<none>") << ", vt: " << (f.hasTexCoord(0) ? std::to_string(f.getTexCoord(0)) : "<none>") << ", vn: " << (f.hasNormal(0) ? std::to_string(f.getNormal(0)) : "<none>") << ") ";
			os << "v1 = (v: " << (f.hasVertex(1) ? std::to_string(f.getVertex(1)) : "<none>") << ", vt: " << (f.hasTexCoord(1) ? std::to_string(f.getTexCoord(1)) : "<none>") << ", vn: " << (f.hasNormal(1) ? std::to_string(f.getNormal(1)) : "<none>") << ") ";
			os << "v2 = (v: " << (f.hasVertex(2) ? std::to_string(f.getVertex(2)) : "<none>") << ", vt: " << (f.hasTexCoord(2) ? std::to_string(f.getTexCoord(2)) : "<none>") << ", vn: " << (f.hasNormal(2) ? std::to_string(f.getNormal(2)) : "<none>") << ") ";
			os << "v3 = (v: " << (f.hasVertex(3) ? std::to_string(f.getVertex(3)) : "<none>") << ", vt: " << (f.hasTexCoord(3) ? std::to_string(f.getTexCoord(3)) : "<none>") << ", vn: " << (f.hasNormal(3) ? std::to_string(f.getNormal(3)) : "<none>") << ")";
			return os;
		}
	}
}