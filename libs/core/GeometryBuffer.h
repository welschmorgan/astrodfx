//
// Created by darkboss on 10/3/20.
//

#ifndef QUASARFX_MODEL_H
#define QUASARFX_MODEL_H

#include <math/Vector.h>
#include <math/Polygon.h>
#include "Collection.h"
#include "Pointers.h"

namespace quasar {
	namespace core {
		template<unsigned Sides = 4>
		class IndexedFace {
		public:
			using index_type            = long long;

		protected:
			index_type                  mVertices[Sides];
			index_type                  mNormals[Sides];
			index_type                  mTexCoords[Sides];
			bool                        mHasVertices[Sides];
			bool                        mHasNormals[Sides];
			bool                        mHasTexCoords[Sides];

		public:
			IndexedFace()
				: mVertices()
				, mNormals()
				, mTexCoords()
				, mHasVertices()
				, mHasNormals()
				, mHasTexCoords()
			{}
			IndexedFace(const std::initializer_list<index_type> &vertices)
				: mVertices()
				, mNormals()
				, mTexCoords()
				, mHasVertices()
				, mHasNormals()
				, mHasTexCoords()
			{
				setVertices(vertices);
			}
			IndexedFace(const std::initializer_list<index_type> &vertices,
			            const std::initializer_list<index_type> &texCoords)
				: mVertices()
				, mNormals()
				, mTexCoords()
				, mHasVertices()
				, mHasNormals()
				, mHasTexCoords()
			{
				setVertices(vertices);
				setTexCoords(texCoords);
			}
			IndexedFace(const std::initializer_list<index_type> &vertices,
			            const std::initializer_list<index_type> &texCoords,
                        const std::initializer_list<index_type> &normals)
				: mVertices()
				, mNormals()
				, mTexCoords()
				, mHasVertices()
				, mHasNormals()
				, mHasTexCoords()
			{
				setVertices(vertices);
				setTexCoords(texCoords);
				setNormals(normals);
			}
			IndexedFace(const IndexedFace &rhs) = default;
			~IndexedFace() = default;

			IndexedFace                 &operator=(const IndexedFace &rhs) = default;

			bool                        hasVertex(size_t id) const {
				if(id >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " vertices, got " + std::to_string(id));
				}
				return mHasVertices[id];
			}
			index_type                  getVertex(size_t n) const {
				if(n >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " vertices, got " + std::to_string(n));
				}
				return mVertices[n];
			}
			index_type                  *getVertices() const { return &mVertices[0]; }
			index_type                  *getVertices() { return &mVertices[0]; }
			void                        setVertex(size_t i, index_type v) {
				if(i >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " vertices, got " + std::to_string(i));
				}
				mHasVertices[i] = true;
				mVertices[i] = v;
			}
			void                        setVertices(const std::initializer_list<index_type> &vertices) {
				unsigned short i = 0;
				for (i = 0; i < Sides; i++) {
					mHasVertices[i] = false;
				}
				if (vertices.size() > 0) {
					if (vertices.size() != Sides) {
						throw std::range_error("face needs " + std::to_string(Sides) + " vertices, got " +
						                         std::to_string(vertices.size()));
					}
					i = 0;
					for (auto &vert: vertices) {
						setVertex(i++, vert);
					}
				}
			}

			bool                        hasNormal(size_t id) const {
				if(id >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " vertices, got " + std::to_string(id));
				}
				return mHasNormals[id];
			}
			index_type                  getNormal(size_t n) const {
				if(n >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " vertices, got " + std::to_string(n));
				}
				return mNormals[n];
			}
			index_type                  *getNormals() const { return &mNormals[0]; }
			index_type                  *getNormals() { return &mNormals[0]; }
			void                        setNormal(size_t i, index_type v) {
				if(i >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " vertices, got " + std::to_string(i));
				}
				mHasNormals[i] = true;
				mNormals[i] = v;
			}
			void                        setNormals(const std::initializer_list<index_type> &normals) {
				unsigned short i = 0;
				for (i = 0; i < Sides; i++) {
					mHasNormals[i] = false;
				}
				if (normals.size() > 0) {
					if (normals.size() != Sides) {
						throw std::runtime_error("face needs " + std::to_string(Sides) + " normals, got " +
						                         std::to_string(normals.size()));
					}
					i = 0;
					for (auto &vert: normals) {
						setNormal(i++, vert);
					}
				}
			}

			bool                        hasTexCoord(size_t id) const {
				if(id >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " texture coords, got " + std::to_string(id));
				}
				return mHasTexCoords[id];
			}
			index_type                  getTexCoord(unsigned n) const {
				if(n >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " texture coords, got " + std::to_string(n));
				}
				return mTexCoords[n];
			}
			index_type                  *getTexCoords() const { return &mTexCoords[0]; }
			index_type                  *getTexCoords() { return &mTexCoords[0]; }
			void                        setTexCoord(size_t i, index_type v) {
				if(i >= Sides) {
					throw std::range_error("face needs " + std::to_string(Sides) + " texture coords, got " + std::to_string(i));
				}
				mHasTexCoords[i] = true;
				mTexCoords[i] = v;
			}
			void                        setTexCoords(const std::initializer_list<index_type> &texCoords) {
				unsigned short i = 0;
				for (i = 0; i < Sides; i++) {
					mHasTexCoords[i] = false;
				}
				if (texCoords.size() > 0) {
					if (texCoords.size() != Sides) {
						throw std::runtime_error("face needs " + std::to_string(Sides) + " texture coords, got " +
						                         std::to_string(texCoords.size()));
					}
					i = 0;
					for (auto &vert: texCoords) {
						setTexCoord(i++, vert);
					}
				}
			}
		};

		class GeometryBuffer {
		public:
			using vertex_type           = quasar::math::Vec4f;
			using normal_type           = quasar::math::Vec4f;
			using tex_coord_type        = quasar::math::Vec3f;
			using triangle_type         = IndexedFace<3>;
			using quad_type             = IndexedFace<4>;

			using vertex_list           = Collection<vertex_type>;
			using normal_list           = Collection<normal_type>;
			using tex_coord_list        = Collection<tex_coord_type>;

			using triangle_list         = Collection<triangle_type>;
			using quad_list             = Collection<quad_type>;

		protected:
			String                      mName;
			vertex_list                 mVertices;
			normal_list                 mNormals;
			tex_coord_list              mTexCoords;
			triangle_list               mTriangles;
			quad_list                   mQuads;

		public:
			GeometryBuffer() = default;
			GeometryBuffer(const String &name_, const vertex_list &v, const normal_list &n = normal_list(), const tex_coord_list &tc = tex_coord_list(), const triangle_list &triangles = triangle_list(), const quad_list &quads = quad_list());
			GeometryBuffer(const GeometryBuffer &rhs) = default;
			virtual ~GeometryBuffer() = default;

			GeometryBuffer              &operator=(const GeometryBuffer &rhs) = default;

			const String                &getName() const;
			void                        setName(const String &name);

			GeometryBuffer              &addVertex(const vertex_type &v);
			const vertex_list           &getVertices() const;
			void                        setVertices(const Collection<vertex_type> &vertices);

			GeometryBuffer              &addNormal(const normal_type &n);
			const normal_list           &getNormals() const;
			void                        setNormals(const Collection<normal_type> &normals);

			GeometryBuffer              &addTexCoord(const tex_coord_type &tc);
			const tex_coord_list        &getTexCoords() const;
			void                        setTexCoords(const Collection<tex_coord_type> &texCoords);

			GeometryBuffer              &addTriangle(const triangle_type &v);
			GeometryBuffer              &addTriangle(triangle_type::index_type v0, triangle_type::index_type v1, triangle_type::index_type v2,
		                                             triangle_type::index_type vn0, triangle_type::index_type vn1, triangle_type::index_type vn2,
		                                             triangle_type::index_type vt0, triangle_type::index_type vt1, triangle_type::index_type vt2);
			const triangle_list         &getTriangles() const;
			void                        setTriangles(const Collection<triangle_type> &triangles);

			GeometryBuffer              &addQuad(const quad_type &v);
			GeometryBuffer              &addQuad(quad_type::index_type v0, quad_type::index_type v1, quad_type::index_type v2, quad_type::index_type v3,
			                                     quad_type::index_type vn0, quad_type::index_type vn1, quad_type::index_type vn2, quad_type::index_type vn3,
			                                     quad_type::index_type vt0, quad_type::index_type vt1, quad_type::index_type vt2, quad_type::index_type vt3);
			const quad_list             &getQuads() const;
			void                        setQuads(const Collection<quad_type> &quads);

			virtual void                upload() {}
		};

		using SharedGeometryBuffer      = SharedPtr<GeometryBuffer>;

		extern std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const IndexedFace<3> &f);
		extern std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const IndexedFace<4> &f);
	}
}

#endif //QUASARFX_MODEL_H
