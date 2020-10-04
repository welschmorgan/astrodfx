//
// Created by darkboss on 10/3/20.
//

#ifndef QUASARFX_POLYGON_H
#define QUASARFX_POLYGON_H

#include <math/Vector.h>
#include <tuple>
#include <sstream>

namespace quasar {
	namespace math {
		template<typename T, size_t DIMENSIONS, size_t SIDES>
		class Polygon {
		public:
			using vertex_type               = math::Vec<T, DIMENSIONS>;
			using normal_type               = math::Vec<T, DIMENSIONS>;
			using tex_coord_type            = math::Vec<T, DIMENSIONS>;
			using value_type                = typename vertex_type::value_type;

			static const size_t Dimensions  = DIMENSIONS;
			static const size_t Sides       = SIDES;

		protected:
			vertex_type                     mVertices[Sides];
			normal_type                     mNormals[Sides];
			tex_coord_type                  mTexCoords[Sides];

		public:
			Polygon() = default;
			Polygon(const vertex_type verts[Sides], const normal_type normals[Sides], const tex_coord_type texcoords[Sides])
				: mVertices(verts)
				, mNormals(normals)
				, mTexCoords(texcoords)
			{}
			Polygon(const vertex_type &v0, const vertex_type &v1, const vertex_type &v2,
			        const normal_type &vn0, const normal_type &vn1, const normal_type &vn2,
                    const tex_coord_type &vt0, const tex_coord_type &vt1, const tex_coord_type &vt2)
				: mVertices()
				, mNormals()
				, mTexCoords()
			{
				if (3 != Sides) {
					throw std::range_error(std::to_string(Dimensions) + "D polygon has " + std::to_string(Sides) + " vertices, given 3");
				}
				mVertices[0] = v0;
				mVertices[1] = v1;
				mVertices[2] = v2;
				mNormals[0] = vn0;
				mNormals[1] = vn1;
				mNormals[2] = vn2;
				mTexCoords[0] = vt0;
				mTexCoords[1] = vt1;
				mTexCoords[2] = vt2;
			}
			Polygon(const vertex_type &v0, const vertex_type &v1, const vertex_type &v2, const vertex_type &v3,
			        const normal_type &vn0, const normal_type &vn1, const normal_type &vn2, const normal_type &vn3,
			        const tex_coord_type &vt0, const tex_coord_type &vt1, const tex_coord_type &vt2, const tex_coord_type &vt3)
		        : mVertices()
		        , mNormals()
		        , mTexCoords()
	        {
				if (4 != Sides) {
					throw std::range_error(std::to_string(Dimensions) + "D polygon has " + std::to_string(Sides) + " vertices, given 4");
				}
				mVertices[0] = v0;
				mVertices[1] = v1;
				mVertices[2] = v2;
				mVertices[3] = v3;
				mNormals[0] = vn0;
				mNormals[1] = vn1;
				mNormals[2] = vn2;
				mNormals[3] = vn3;
				mTexCoords[0] = vt0;
				mTexCoords[1] = vt1;
				mTexCoords[2] = vt2;
				mTexCoords[3] = vt3;
			}
			Polygon(const Polygon &rhs) = default;
			~Polygon() = default;

			Polygon             &operator=(const Polygon &rhs) = default;

			void                clear() {
				for (size_t i = 0; i < Sides; i++) {
					mVertices[i] = vertex_type();
					mNormals[i] = normal_type();
					mTexCoords[i] = tex_coord_type();
				}
			}

			vertex_type         *vertices() const { return &mVertices[0]; }
			normal_type         *normals() const { return &mNormals[0]; }
			tex_coord_type      *texCoords() const { return &mTexCoords[0]; }

			vertex_type         &vertex(size_t id) noexcept(false) {
				if (id > (Sides - 1)) {
					throw std::range_error(std::to_string(Dimensions) + "D polygon has " + std::to_string(Sides) + " vertices, given " + std::to_string(id));
				}
				return mVertices[id];
			}

			vertex_type         vertex(size_t id) const noexcept(false) {
				if (id > (Sides - 1)) {
					throw std::range_error(std::to_string(Dimensions) + "D polygon has " + std::to_string(Sides) + " vertices, given " + std::to_string(id));
				}
				return mVertices[id];
			}

			normal_type         &normal(size_t id) noexcept(false) {
				if (id > (Sides - 1)) {
					throw std::range_error(std::to_string(Dimensions) + "D polygon has " + std::to_string(Sides) + " normals, given " + std::to_string(id));
				}
				return mVertices[id];
			}

			normal_type         normal(size_t id) const noexcept(false) {
				if (id > (Sides - 1)) {
					throw std::range_error(std::to_string(Dimensions) + "D polygon has " + std::to_string(Sides) + " normals, given " + std::to_string(id));
				}
				return mVertices[id];
			}

			tex_coord_type      &texCoord(size_t id) noexcept(false) {
				if (id > (Sides - 1)) {
					throw std::range_error(std::to_string(Dimensions) + "D polygon has " + std::to_string(Sides) + " texCoords, given " + std::to_string(id));
				}
				return mVertices[id];
			}

			tex_coord_type      texCoord(size_t id) const noexcept(false) {
				if (id > (Sides - 1)) {
					throw std::range_error(std::to_string(Dimensions) + "D polygon has " + std::to_string(Sides) + " texCoords, given " + std::to_string(id));
				}
				return mVertices[id];
			}


			vertex_type center() const {
				vertex_type         accu;
				for (size_t i = 0; i < Sides; i++) {
					accu += mVertices[i];
				}
				accu /= int(Sides);
				return accu;
			}
		};

		template<typename T, size_t Dimensions, size_t Sides>
		std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const Polygon<T, Dimensions, Sides> &p) {
			std::basic_stringstream<char> verts, norms, texcoords;
			for (size_t n = 0; n < Sides; n++) {
				if (n != 0) {
					verts << std::string(", ");
					norms << std::string(", ");
					texcoords << std::string(", ");
				}
				verts << std::string("v") << std::to_string(n) << std::string("(") << p.vertex(n) << std::string(")");
				norms << std::string("n") << std::to_string(n) << std::string("(") << p.normal(n) << std::string(")");
				texcoords << std::string("tc") << std::to_string(n) << std::string("(") << p.texCoord(n) << std::string(")");
			}
			os << verts.str() << std::endl;
			os << norms.str() << std::endl;
			os << texcoords.str() << std::endl;
			return os;
		}

		template<typename T, size_t Sides>
		using Polygon2 = Polygon<T, 2, Sides>;

		template<typename T>
		using Polygon2D3 = Polygon2<T, 3>;
		using Polygon2D3c = Polygon2D3<char>;
		using Polygon2D3s = Polygon2D3<short>;
		using Polygon2D3i = Polygon2D3<int>;
		using Polygon2D3l = Polygon2D3<long>;
		using Polygon2D3uc = Polygon2D3<unsigned char>;
		using Polygon2D3us = Polygon2D3<unsigned short>;
		using Polygon2D3ui = Polygon2D3<unsigned int>;
		using Polygon2D3ul = Polygon2D3<unsigned long>;
		using Polygon2D3f = Polygon2D3<float>;
		using Polygon2D3d = Polygon2D3<double>;

		template<typename T>
		using Polygon2D4 = Polygon2<T, 4>;
		using Polygon2D4c = Polygon2D4<char>;
		using Polygon2D4s = Polygon2D4<short>;
		using Polygon2D4i = Polygon2D4<int>;
		using Polygon2D4l = Polygon2D4<long>;
		using Polygon2D4uc = Polygon2D4<unsigned char>;
		using Polygon2D4us = Polygon2D4<unsigned short>;
		using Polygon2D4ui = Polygon2D4<unsigned int>;
		using Polygon2D4ul = Polygon2D4<unsigned long>;
		using Polygon2D4f = Polygon2D4<float>;
		using Polygon2D4d = Polygon2D4<double>;

		template<typename T>
		using Triangle2 = Polygon2D3<T>;
		using Triangle2c = Triangle2<char>;
		using Triangle2s = Triangle2<short>;
		using Triangle2i = Triangle2<int>;
		using Triangle2l = Triangle2<long>;
		using Triangle2uc = Triangle2<unsigned char>;
		using Triangle2us = Triangle2<unsigned short>;
		using Triangle2ui = Triangle2<unsigned int>;
		using Triangle2ul = Triangle2<unsigned long>;
		using Triangle2f = Triangle2<float>;
		using Triangle2d = Triangle2<double>;

		template<typename T>
		using Quad2 = Polygon2D4<T>;
		using Quad2c = Quad2<char>;
		using Quad2s = Quad2<short>;
		using Quad2i = Quad2<int>;
		using Quad2l = Quad2<long>;
		using Quad2uc = Quad2<unsigned char>;
		using Quad2us = Quad2<unsigned short>;
		using Quad2ui = Quad2<unsigned int>;
		using Quad2ul = Quad2<unsigned long>;
		using Quad2f = Quad2<float>;
		using Quad2d = Quad2<double>;

		template<typename T, size_t Sides>
		using Polygon3 = Polygon<T, 3, Sides>;

		template<typename T>
		using Polygon3D3 = Polygon3<T, 3>;
		using Polygon3D3c = Polygon3D3<char>;
		using Polygon3D3s = Polygon3D3<short>;
		using Polygon3D3i = Polygon3D3<int>;
		using Polygon3D3l = Polygon3D3<long>;
		using Polygon3D3uc = Polygon3D3<unsigned char>;
		using Polygon3D3us = Polygon3D3<unsigned short>;
		using Polygon3D3ui = Polygon3D3<unsigned int>;
		using Polygon3D3ul = Polygon3D3<unsigned long>;
		using Polygon3D3f = Polygon3D3<float>;
		using Polygon3D3d = Polygon3D3<double>;

		template<typename T>
		using Polygon3D4 = Polygon3<T, 4>;
		using Polygon3D4c = Polygon3D4<char>;
		using Polygon3D4s = Polygon3D4<short>;
		using Polygon3D4i = Polygon3D4<int>;
		using Polygon3D4l = Polygon3D4<long>;
		using Polygon3D4uc = Polygon3D4<unsigned char>;
		using Polygon3D4us = Polygon3D4<unsigned short>;
		using Polygon3D4ui = Polygon3D4<unsigned int>;
		using Polygon3D4ul = Polygon3D4<unsigned long>;
		using Polygon3D4f = Polygon3D4<float>;
		using Polygon3D4d = Polygon3D4<double>;

		template<typename T>
		using Triangle3 = Polygon3D3<T>;
		using Triangle3c = Triangle3<char>;
		using Triangle3s = Triangle3<short>;
		using Triangle3i = Triangle3<int>;
		using Triangle3l = Triangle3<long>;
		using Triangle3uc = Triangle3<unsigned char>;
		using Triangle3us = Triangle3<unsigned short>;
		using Triangle3ui = Triangle3<unsigned int>;
		using Triangle3ul = Triangle3<unsigned long>;
		using Triangle3f = Triangle3<float>;
		using Triangle3d = Triangle3<double>;

		template<typename T>
		using Quad3 = Polygon3D4<T>;
		using Quad3c = Quad3<char>;
		using Quad3s = Quad3<short>;
		using Quad3i = Quad3<int>;
		using Quad3l = Quad3<long>;
		using Quad3uc = Quad3<unsigned char>;
		using Quad3us = Quad3<unsigned short>;
		using Quad3ui = Quad3<unsigned int>;
		using Quad3ul = Quad3<unsigned long>;
		using Quad3f = Quad3<float>;
		using Quad3d = Quad3<double>;

		template<typename T, size_t Sides>
		using Polygon4 = Polygon<T, 4, Sides>;

		template<typename T>
		using Polygon4D3 = Polygon4<T, 3>;
		using Polygon4D3c = Polygon4D3<char>;
		using Polygon4D3s = Polygon4D3<short>;
		using Polygon4D3i = Polygon4D3<int>;
		using Polygon4D3l = Polygon4D3<long>;
		using Polygon4D3uc = Polygon4D3<unsigned char>;
		using Polygon4D3us = Polygon4D3<unsigned short>;
		using Polygon4D3ui = Polygon4D3<unsigned int>;
		using Polygon4D3ul = Polygon4D3<unsigned long>;
		using Polygon4D3f = Polygon4D3<float>;
		using Polygon4D3d = Polygon4D3<double>;

		template<typename T>
		using Polygon4D4 = Polygon4<T, 4>;
		using Polygon4D4c = Polygon4D4<char>;
		using Polygon4D4s = Polygon4D4<short>;
		using Polygon4D4i = Polygon4D4<int>;
		using Polygon4D4l = Polygon4D4<long>;
		using Polygon4D4uc = Polygon4D4<unsigned char>;
		using Polygon4D4us = Polygon4D4<unsigned short>;
		using Polygon4D4ui = Polygon4D4<unsigned int>;
		using Polygon4D4ul = Polygon4D4<unsigned long>;
		using Polygon4D4f = Polygon4D4<float>;
		using Polygon4D4d = Polygon4D4<double>;

		template<typename T>
		using Triangle4 = Polygon4D3<T>;
		using Triangle4c = Triangle4<char>;
		using Triangle4s = Triangle4<short>;
		using Triangle4i = Triangle4<int>;
		using Triangle4l = Triangle4<long>;
		using Triangle4uc = Triangle4<unsigned char>;
		using Triangle4us = Triangle4<unsigned short>;
		using Triangle4ui = Triangle4<unsigned int>;
		using Triangle4ul = Triangle4<unsigned long>;
		using Triangle4f = Triangle4<float>;
		using Triangle4d = Triangle4<double>;

		template<typename T>
		using Quad4 = Polygon4D4<T>;
		using Quad4c = Quad4<char>;
		using Quad4s = Quad4<short>;
		using Quad4i = Quad4<int>;
		using Quad4l = Quad4<long>;
		using Quad4uc = Quad4<unsigned char>;
		using Quad4us = Quad4<unsigned short>;
		using Quad4ui = Quad4<unsigned int>;
		using Quad4ul = Quad4<unsigned long>;
		using Quad4f = Quad4<float>;
		using Quad4d = Quad4<double>;

	}
}

#endif //QUASARFX_POLYGON_H
