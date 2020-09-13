//
// Created by darkboss on 8/21/20.
//

#ifndef QUASARFX_MATH_RECT_H
#define QUASARFX_MATH_RECT_H

# include <initializer_list>
# include <stdexcept>

namespace quasar {
	namespace math {

		template<typename T, unsigned short Dim>
		class VecBase {
		protected:
			T mData[Dim];

		public:
			using self_type = VecBase<T, Dim>;
			using value_type = T;

			static const unsigned short Dimensions = Dim;

		public:
			VecBase()
				: mData()
			{
				for (auto &p: mData) {
					p = 0;
				}
			}
			VecBase(const T data[Dim])
				: mData()
			{
				*this = data;
			}
			VecBase(const std::initializer_list<T> &data)
				: mData()
			{
				*this = data;
			}
			VecBase(const self_type &rhs) = default;
			~VecBase() = default;

			self_type       &operator=(const self_type &rhs) {
				for (unsigned short i = 0; i < Dimensions; i++) {
					mData[i] = rhs.mData[i];
				}
				return *this;
			}
			self_type       &operator=(const T data[Dim]) {
				for (unsigned short i = 0; i < Dim; i++) {
					mData[i] = data[i];
				}
				return *this;
			}
			self_type       &operator=(const std::initializer_list<T> &data) {
				if (data.size() >= Dimensions) {
					throw std::range_error("Initializer list is too big for vector of size " + std::to_string(Dimensions));
				}
				for (unsigned short i = 0; i < Dim; i++) {
					mData[i] = data[i];
				}
				return *this;
			}

			bool            operator==(T value) const noexcept {
				for (unsigned short i = 0; i < Dimensions; i++) {
					if (mData[i] != value) {
						return false;
					}
				}
				return true;
			}

			bool            operator!=(T value) const noexcept {
				return !(*this == value);
			}

			bool            operator==(const self_type &value) const noexcept {
				for (unsigned short i = 0; i < Dimensions; i++) {
					if (mData[i] != value.mData[i]) {
						return false;
					}
				}
				return true;
			}

			bool            operator!=(const self_type &value) const noexcept {
				return !(*this == value);
			}

			bool            operator<(T value) const noexcept {
				return squaredLength() < value;
			}
			bool            operator<=(T value) const noexcept {
				return squaredLength() <= value;
			}
			bool            operator>(T value) const noexcept {
				return squaredLength() > value;
			}
			bool            operator>=(T value) const noexcept {
				return squaredLength() >= value;
			}

			bool            operator<(const self_type &rhs) const noexcept {
				return squaredLength() < rhs.squaredLength();
			}
			bool            operator<=(const self_type &rhs) const noexcept {
				return squaredLength() <= rhs.squaredLength();
			}
			bool            operator>(const self_type &rhs) const noexcept {
				return squaredLength() > rhs.squaredLength();
			}
			bool            operator>=(const self_type &rhs) const noexcept {
				return squaredLength() >= rhs.squaredLength();
			}

			self_type       operator*(T value) const noexcept {
				self_type   ret(*this);
				for (unsigned short i = 0; i < Dimensions; ++i) {
					ret.mData[i] *= value;
				}
				return ret;
			}

			self_type       operator/(T value) const {
				self_type   ret(*this);
				for (unsigned short i = 0; i < Dimensions; ++i) {
					ret.mData[i] /= value;
				}
				return ret;
			}

			self_type       operator+(T value) const noexcept {
				self_type   ret(*this);
				for (unsigned short i = 0; i < Dimensions; ++i) {
					ret.mData[i] += value;
				}
				return ret;
			}

			self_type       operator-(T value) const noexcept {
				self_type   ret(*this);
				for (unsigned short i = 0; i < Dimensions; ++i) {
					ret.mData[i] -= value;
				}
				return ret;
			}


			self_type       &operator*=(T value) noexcept {
				*this = *this * value;
				return *this;
			}

			self_type       &operator/=(T value) {
				*this = *this / value;
				return *this;
			}

			self_type       &operator+=(T value) noexcept {
				*this = *this + value;
				return *this;
			}

			self_type       &operator-=(T value) noexcept {
				*this = *this - value;
				return *this;
			}

			value_type      operator-() const noexcept {
				return reversed();
			}

			value_type      operator*(const self_type &rhs) const noexcept {
				return dot(rhs);
			}

			self_type      operator+(const self_type &rhs) const noexcept {
				self_type ret;
				for (unsigned short i = 0; i < Dimensions; ++i) {
					ret.mData[i] = mData[i] + rhs.mData[i];
				}
				return ret;
			}

			self_type      operator-(const self_type &rhs) const noexcept {
				return *this + rhs.reversed();
			}

			value_type      operator*=(const self_type &rhs) noexcept {
				return *this = *this * rhs;
			}

			self_type      operator+=(const self_type &rhs) noexcept {
				return *this = *this + rhs;
			}

			self_type      operator-=(const self_type &rhs) noexcept {
				return *this = *this - rhs;
			}

			self_type      reversed() const noexcept {
				return self_type(*this).reverse();
			}

			self_type      &reverse() noexcept {
				for (unsigned short i = 0; i < Dimensions; ++i) {
					mData[i] *= T(-1);
				}
				return *this;
			}

			value_type      dot(const self_type &rhs) const noexcept {
				value_type ret = value_type(0);
				for (unsigned short i = 0; i < Dimensions; ++i) {
					ret += mData[i] * rhs.mData[i];
				}
				return ret;
			}

			T               &data(unsigned short id) noexcept {
				return mData[id];
			}

			T               data(unsigned short id) const noexcept {
				return mData[id];
			}

			T               *data() noexcept {
				return &mData[0];
			}

			const T         *data() const noexcept {
				return &mData[0];
			}

			double          squaredLength() const noexcept {
				float res = .0f;
				for (unsigned short i = 0; i < Dimensions; ++i) {
					res += mData[i] * mData[i];
				}
				return res;
			}

			double          length() const noexcept {
				return sqrt(squaredLength());
			}

			self_type       normalized() const {
				self_type ret(*this);
				ret.normalize();
				return ret;
			}

			double          normalize() {
				auto len = length();
				for (unsigned short i = 0; i < Dimensions; ++i) {
					mData[i] /= len;
				}
				return len;
			}
		};

		template<typename T, unsigned short Dims>
		class Vec: public VecBase<T, Dims> {};

		template<typename T>
		class Vec<T, 2>: public VecBase<T, 2> {
		public:
			using base_type = VecBase<T, 2>;
			using self_type = Vec<T, 2>;

			static const self_type Zero;

			static const self_type UnitX;
			static const self_type UnitY;
			static const self_type UnitScale;

			static const self_type NegativeUnitX;
			static const self_type NegativeUnitY;
			static const self_type NegativeUnitScale;

			T &x;
			T &y;

			Vec()
				: base_type()
				, x(base_type::mData[0])
				, y(base_type::mData[1])
			{}
			Vec(const base_type &b)
				: base_type(b)
				, x(base_type::mData[0])
				, y(base_type::mData[1])
			{ base_type::operator=(b); }
			Vec(T x, T y)
				: base_type()
				, x(base_type::mData[0])
				, y(base_type::mData[1])
			{
				this->x = x;
				this->y = y;
			}
			Vec(const self_type &rhs)
					: base_type()
					, x(base_type::mData[0])
					, y(base_type::mData[1])
			{ *this = rhs; }
			~Vec() = default;

			self_type           &operator=(const self_type &rhs) {
				base_type::operator=(rhs);
				return *this;
			}

			T                   cross(const self_type &rhs) {
				return base_type::mData[0] * rhs.mData[1] - base_type::mData[1] * rhs.mData[0];
			}
		};

		template<typename T>
		class Vec<T, 3>: public VecBase<T, 3> {
		public:
			using base_type = VecBase<T, 3>;
			using self_type = Vec<T, 3>;

			static const self_type Zero;
			static const self_type UnitX;
			static const self_type UnitY;
			static const self_type UnitZ;
			static const self_type UnitScale;
			static const self_type NegativeUnitX;
			static const self_type NegativeUnitY;
			static const self_type NegativeUnitZ;
			static const self_type NegativeUnitScale;

			T &x;
			T &y;
			T &z;

			Vec()
				: base_type()
				, x(base_type::mData[0])
				, y(base_type::mData[1])
				, z(base_type::mData[2])
			{}
			Vec(T x, T y, T z)
					: base_type()
					, x(base_type::mData[0])
					, y(base_type::mData[1])
					, z(base_type::mData[2])
			{
				this->x = x;
				this->y = y;
				this->z = z;
			}
			Vec(const base_type &b)
				: base_type(b)
				, x(base_type::mData[0])
				, y(base_type::mData[1])
				, z(base_type::mData[2])
			{ base_type::operator=(b); }

			Vec(const self_type &rhs)
				: base_type()
				, x(base_type::mData[0])
				, y(base_type::mData[1])
				, z(base_type::mData[2])
			{ *this = rhs; }
			~Vec() = default;

			self_type           &operator=(const self_type &rhs) {
				base_type::operator=(rhs);
				return *this;
			}

			self_type           cross(const self_type &rhs) {
				return self_type(
					base_type::mData[1] * rhs.mData[2] - base_type::mData[2] * rhs.mData[1],
					base_type::mData[2] * rhs.mData[0] - base_type::mData[0] * rhs.mData[2],
					base_type::mData[0] * rhs.mData[1] - base_type::mData[1] * rhs.mData[0]
				);
			}
		};

		template<typename T>
		class Vec<T, 4>: public VecBase<T, 4> {
		public:
			using base_type = VecBase<T, 4>;
			using self_type = Vec<T, 4>;

			static const self_type Zero;
			static const self_type UnitX;
			static const self_type UnitY;
			static const self_type UnitZ;
			static const self_type UnitW;
			static const self_type UnitScale;
			static const self_type NegativeUnitX;
			static const self_type NegativeUnitY;
			static const self_type NegativeUnitZ;
			static const self_type NegativeUnitW;
			static const self_type NegativeUnitScale;

			T &x;
			T &y;
			T &z;
			T &w;

			Vec()
				: base_type()
				, x(base_type::mData[0])
				, y(base_type::mData[1])
				, z(base_type::mData[2])
				, w(base_type::mData[3])
			{}
			Vec(T x, T y, T z, T w = T(1))
				: base_type()
				, x(base_type::mData[0])
				, y(base_type::mData[1])
				, z(base_type::mData[2])
				, w(base_type::mData[3])
			{
				this->x = x;
				this->y = y;
				this->z = z;
				this->w = w;
			}
			Vec(const self_type &rhs)
				: base_type()
				, x(base_type::mData[0])
				, y(base_type::mData[1])
				, z(base_type::mData[2])
				, w(base_type::mData[3])
			{ base_type::operator=(rhs); }
			Vec(const base_type &b)
				: base_type(b)
				, x(base_type::mData[0])
				, y(base_type::mData[1])
				, z(base_type::mData[2])
				, w(base_type::mData[3])
			{ *this = b; }
			~Vec() = default;

			self_type           &operator=(const self_type &rhs) {
				base_type::operator=(rhs);
				return *this;
			}
		};

		template<typename T> using Vec2 = Vec<T, 2>;
		template<typename T> const Vec2<T> Vec2<T>::UnitX = Vec2<T>(1, 0);
		template<typename T> const Vec2<T> Vec2<T>::UnitY = Vec2<T>(0, 1);
		template<typename T> const Vec2<T> Vec2<T>::Zero = Vec2<T>(0, 0);
		template<typename T> const Vec2<T> Vec2<T>::UnitScale = Vec2<T>(1, 1);
		template<typename T> const Vec2<T> Vec2<T>::NegativeUnitX = Vec2<T>(-1, 0);
		template<typename T> const Vec2<T> Vec2<T>::NegativeUnitY = Vec2<T>(0, -1);
		template<typename T> const Vec2<T> Vec2<T>::NegativeUnitScale = Vec2<T>(-1, -1);

		template<typename T> using Vec3 = Vec<T, 3>;
		template<typename T> const Vec3<T> Vec3<T>::UnitX = Vec3<T>(1, 0, 0);
		template<typename T> const Vec3<T> Vec3<T>::UnitY = Vec3<T>(0, 1, 0);
		template<typename T> const Vec3<T> Vec3<T>::UnitZ = Vec3<T>(0, 0, 1);
		template<typename T> const Vec3<T> Vec3<T>::Zero = Vec3<T>(0, 0, 0);
		template<typename T> const Vec3<T> Vec3<T>::UnitScale = Vec3<T>(1, 1, 1);
		template<typename T> const Vec3<T> Vec3<T>::NegativeUnitX = Vec3<T>(-1, 0, 0);
		template<typename T> const Vec3<T> Vec3<T>::NegativeUnitY = Vec3<T>(0, -1, 0);
		template<typename T> const Vec3<T> Vec3<T>::NegativeUnitZ = Vec3<T>(0, 0, -1);
		template<typename T> const Vec3<T> Vec3<T>::NegativeUnitScale = Vec3<T>(-1, -1, -1);

		template<typename T> using Vec4 = Vec<T, 4>;
		template<typename T> const Vec4<T> Vec4<T>::UnitX = Vec4<T>(1, 0, 0, 1);
		template<typename T> const Vec4<T> Vec4<T>::UnitY = Vec4<T>(0, 1, 0, 1);
		template<typename T> const Vec4<T> Vec4<T>::UnitZ = Vec4<T>(0, 0, 1, 1);
		template<typename T> const Vec4<T> Vec4<T>::Zero = Vec4<T>(0, 0, 0, 1);
		template<typename T> const Vec4<T> Vec4<T>::UnitScale = Vec4<T>(1, 1, 1, 1);
		template<typename T> const Vec4<T> Vec4<T>::NegativeUnitX = Vec4<T>(-1, 0, 0, 1);
		template<typename T> const Vec4<T> Vec4<T>::NegativeUnitY = Vec4<T>(0, -1, 0, 1);
		template<typename T> const Vec4<T> Vec4<T>::NegativeUnitZ = Vec4<T>(0, 0, -1, 1);
		template<typename T> const Vec4<T> Vec4<T>::NegativeUnitScale = Vec4<T>(-1, -1, -1, 1);

		using Vec2c = Vec2<char>;
		using Vec2s = Vec2<short>;
		using Vec2i = Vec2<int>;
		using Vec2l = Vec2<long>;
		using Vec2uc = Vec2<unsigned char>;
		using Vec2us = Vec2<unsigned short>;
		using Vec2ui = Vec2<unsigned int>;
		using Vec2ul = Vec2<unsigned long>;
		using Vec2f = Vec2<float>;
		using Vec2d = Vec2<double>;

		using Vec3c = Vec3<char>;
		using Vec3s = Vec3<short>;
		using Vec3i = Vec3<int>;
		using Vec3l = Vec3<long>;
		using Vec3uc = Vec3<unsigned char>;
		using Vec3us = Vec3<unsigned short>;
		using Vec3ui = Vec3<unsigned int>;
		using Vec3ul = Vec3<unsigned long>;
		using Vec3f = Vec3<float>;
		using Vec3d = Vec3<double>;

		using Vec4c = Vec4<char>;
		using Vec4s = Vec4<short>;
		using Vec4i = Vec4<int>;
		using Vec4l = Vec4<long>;
		using Vec4uc = Vec4<unsigned char>;
		using Vec4us = Vec4<unsigned short>;
		using Vec4ui = Vec4<unsigned int>;
		using Vec4ul = Vec4<unsigned long>;
		using Vec4f = Vec4<float>;
		using Vec4d = Vec4<double>;
	}
}


#endif //QUASARFX_RECT_H
