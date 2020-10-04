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
		class GeometryBuffer {
		public:
			using vertex_type           = quasar::math::Vec4f;
			using normal_type           = quasar::math::Vec4f;
			using tex_coord_type        = quasar::math::Vec3f;
			using index_type            = size_t;
			using indexed_vertex_type   = quasar::math::Vec4<index_type>;
			using triangle_type         = quasar::math::Triangle4<index_type>;
			using quad_type             = quasar::math::Quad4<index_type>;

			using vertex_list           = Collection<vertex_type>;
			using normal_list           = Collection<normal_type>;
			using tex_coord_list        = Collection<tex_coord_type>;
			using index_list            = Collection<index_type>;
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

			GeometryBuffer              &addTriangle(triangle_type v);
			GeometryBuffer              &addTriangle(const indexed_vertex_type &v0, const indexed_vertex_type &v1, const indexed_vertex_type &v2,
			                                         const indexed_vertex_type &vn0, const indexed_vertex_type &vn1, const indexed_vertex_type &vn2,
			                                         const indexed_vertex_type &vt0, const indexed_vertex_type &vt1, const indexed_vertex_type &vt2);
			const triangle_list         &getTriangles() const;
			void                        setTriangles(const Collection<triangle_type> &triangles);

			GeometryBuffer              &addQuad(quad_type v);
			GeometryBuffer              &addQuad(const indexed_vertex_type &v0, const indexed_vertex_type &v1, const indexed_vertex_type &v2, const indexed_vertex_type &v3,
			                                     const indexed_vertex_type &vn0, const indexed_vertex_type &vn1, const indexed_vertex_type &vn2, const indexed_vertex_type &vn3,
			                                     const indexed_vertex_type &vt0, const indexed_vertex_type &vt1, const indexed_vertex_type &vt2, const indexed_vertex_type &vt3);
			const quad_list             &getQuads() const;
			void                        setQuads(const Collection<quad_type> &quads);

			virtual void                upload() {}
		};

		using SharedGeometryBuffer      = SharedPtr<GeometryBuffer>;
	}
}

#endif //QUASARFX_MODEL_H
