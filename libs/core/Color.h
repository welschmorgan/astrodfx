//
// Created by darkboss on 9/12/20.
//

#ifndef QUASARFX_COLOR_H
#define QUASARFX_COLOR_H

#include <ostream>
#include "String.h"

namespace quasar {
	namespace core {
		template<typename T, unsigned char N>
		class ColorBase {
		public:
			using value_type    = T;
			using self_type     = ColorBase<T, N>;

			static const unsigned char nparts = N;

		protected:
			T                   mData[N];

		public:
			ColorBase(): mData() {}
			ColorBase(const T data[N]): mData(data) {}
			ColorBase(const ColorBase &rhs) = default;
			virtual             ~ColorBase() noexcept = default;

			ColorBase           &operator=(const ColorBase &rhs) = default;

			bool                operator<(const ColorBase &rhs) const noexcept {
				for (unsigned char i = 0; i < N; i++) {
					if (mData[i] >= rhs.mData[i]) {
						return false;
					}
				}
				return true;
			}

			bool                operator<=(const ColorBase &rhs) const noexcept {
				for (unsigned char i = 0; i < N; i++) {
					if (mData[i] > rhs.mData[i]) {
						return false;
					}
				}
				return true;
			}

			bool                operator>(const ColorBase &rhs) const noexcept {
				for (unsigned char i = 0; i < N; i++) {
					if (mData[i] <= rhs.mData[i]) {
						return false;
					}
				}
				return true;
			}

			bool                operator>=(const ColorBase &rhs) const noexcept {
				for (unsigned char i = 0; i < N; i++) {
					if (mData[i] < rhs.mData[i]) {
						return false;
					}
				}
				return true;
			}

			bool                operator==(const ColorBase &rhs) const noexcept {
				for (unsigned char i = 0; i < N; i++) {
					if (mData[i] != rhs.mData[i]) {
						return false;
					}
				}
				return true;
			}

			bool                operator!=(const ColorBase &rhs) const noexcept {
				return !(*this == rhs);
			}

			T                   &data(unsigned char i) {
				return mData[i];
			}

			T                   data(unsigned char i) const {
				return mData[i];
			}

			T                   *data() {
				return mData;
			}

			const T             *data() const {
				return mData;
			}

			ColorBase           operator+(const ColorBase &rhs) {
				ColorBase       ret(*this);
				for (unsigned char i = 0; i < N; i++) {
					ret.mData[i] += rhs.mData[i];
				}
				return ret;
			}

			ColorBase           operator-(const ColorBase &rhs) {
				ColorBase       ret(*this);
				for (unsigned char i = 0; i < N; i++) {
					ret.mData[i] -= rhs.mData[i];
				}
				return ret;
			}

			ColorBase           operator*(const ColorBase &rhs) {
				ColorBase       ret(*this);
				for (unsigned char i = 0; i < N; i++) {
					ret.mData[i] *= rhs.mData[i];
				}
				return ret;
			}

			ColorBase           operator/(const ColorBase &rhs) {
				ColorBase       ret(*this);
				for (unsigned char i = 0; i < N; i++) {
					ret.mData[i] /= rhs.mData[i];
				}
				return ret;
			}

			ColorBase           &operator+=(const ColorBase &rhs) {
				return *this = *this + rhs;
			}

			ColorBase           &operator-=(const ColorBase &rhs) {
				return *this = *this - rhs;
			}
			ColorBase           &operator*=(const ColorBase &rhs) {
				return *this = *this * rhs;
			}
			ColorBase           &operator/=(const ColorBase &rhs) {
				return *this = *this / rhs;
			}


			ColorBase           operator+(const T scale) {
				ColorBase       ret(*this);
				for (unsigned char i = 0; i < N; i++) {
					ret.mData[i] += scale;
				}
				return ret;
			}

			ColorBase           operator-(const T scale) {
				ColorBase       ret(*this);
				for (unsigned char i = 0; i < N; i++) {
					ret.mData[i] -= scale;
				}
				return ret;
			}

			ColorBase           operator*(const T scale) {
				ColorBase       ret(*this);
				for (unsigned char i = 0; i < N; i++) {
					ret.mData[i] *= scale;
				}
				return ret;
			}

			ColorBase           operator/(const T scale) {
				ColorBase       ret(*this);
				for (unsigned char i = 0; i < N; i++) {
					ret.mData[i] /= scale;
				}
				return ret;
			}

			ColorBase           &operator+=(const T scale) {
				return *this = *this + scale;
			}

			ColorBase           &operator-=(const T scale) {
				return *this = *this - scale;
			}
			ColorBase           &operator*=(const T scale) {
				return *this = *this * scale;
			}
			ColorBase           &operator/=(const T scale) {
				return *this = *this / scale;
			}

		};

		template<typename T, unsigned char N>
		class Color;

		template<typename T>
		class Color<T, 1>: public ColorBase<T, 1> {
		public:
			using base_type             = ColorBase<T, 1>;
			using value_type            = typename base_type::value_type ;

		public:
			static const unsigned char  nparts  = base_type::nparts;

			value_type                  &r;
		public:
			explicit Color(value_type r_ = value_type()): base_type(), r(base_type::mData[0])
			{ r = r_; }
			Color(const Color &rhs): base_type(rhs), r(base_type::mData[0]) {}
			virtual ~Color() noexcept = default;

			Color                       &operator=(const Color &rhs) {
				base_type::operator=(rhs);
				r = base_type::mData[0];
				return *this;
			}

			Color<T, 2>                 widen() const {
				return Color<T, 2>(r, value_type(0));
			}
		};


		template<typename T>
		class Color<T, 2>: public ColorBase<T, 2> {
		public:
			using base_type             = ColorBase<T, 2>;
			using value_type            = typename base_type::value_type;

		public:
			static const unsigned char  nparts  = base_type::nparts;

			value_type                  &r;
			value_type                  &g;
		public:
			explicit Color(value_type r_ = value_type(), value_type g_ = value_type()): base_type(), r(base_type::mData[0]), g(base_type::mData[1])
			{ r = r_; g = g_; }
			Color(const Color &rhs): base_type(rhs), r(base_type::mData[0]), g(base_type::mData[1]) {}
			virtual ~Color() noexcept = default;

			Color                       &operator=(const Color &rhs) {
				base_type::operator=(rhs);
				r = base_type::mData[0];
				g = base_type::mData[1];
				return *this;
			}
			Color<T, 3>                 widen() const {
				return Color<T, 3>(r, g, value_type(0));
			}
			Color<T, 1>                 narrow() const {
				return Color<T, 1>(r);
			}
		};

		template<typename T>
		class Color<T, 3>: public ColorBase<T, 3> {
		public:
			using base_type             = ColorBase<T, 3>;
			using value_type            = typename base_type::value_type;

		public:
			static const unsigned char  nparts  = base_type::nparts;

			value_type                  &r;
			value_type                  &g;
			value_type                  &b;
		public:
			explicit Color(value_type r_ = value_type(), value_type g_ = value_type(), value_type b_ = value_type())
				: base_type(), r(base_type::mData[0]), g(base_type::mData[1]), b(base_type::mData[2])
			{ r = r_; g = g_; b = b_; }
			Color(const Color &rhs): base_type(rhs), r(base_type::mData[0]), g(base_type::mData[1]), b(base_type::mData[2]) {}
			virtual ~Color() noexcept = default;

			Color                  &operator=(const Color &rhs) {
				base_type::operator=(rhs);
				r = base_type::mData[0];
				g = base_type::mData[1];
				b = base_type::mData[2];
				return *this;
			}
			Color<T, 4>                 widen() const {
				return Color<T, 4>(r, g, b, value_type(1));
			}
			Color<T, 2>                 narrow() const {
				return Color<T, 2>(r, g);
			}
		};

		template<typename T>
		class Color<T, 4>: public ColorBase<T, 4> {
		public:
			using base_type             = ColorBase<T, 4>;
			using value_type            = typename base_type::value_type;

		public:
			static const unsigned char  nparts  = base_type::nparts;

			value_type                  &r;
			value_type                  &g;
			value_type                  &b;
			value_type                  &a;
		public:
			explicit Color(value_type r_ = value_type(), value_type g_ = value_type(), value_type b_ = value_type(), value_type a_ = value_type(1))
				: base_type(), r(base_type::mData[0]), g(base_type::mData[1]), b(base_type::mData[2]), a(base_type::mData[3])
			{ r = r_; g = g_; b = b_; a = a_; }
			Color(const Color &rhs): base_type(rhs), r(base_type::mData[0]), g(base_type::mData[1]), b(base_type::mData[2]), a(base_type::mData[3]) {}
			virtual ~Color() noexcept = default;

			Color                  &operator=(const Color &rhs) {
				base_type::operator=(rhs);
				r = base_type::mData[0];
				g = base_type::mData[1];
				b = base_type::mData[2];
				a = base_type::mData[3];
				return *this;
			}

			Color<T, 3>                 narrow() const {
				return Color<T, 3>(r, g, b);
			}
		};

		template<typename T, unsigned char N>
		::std::basic_ostream<char>     &operator<<(::std::basic_ostream<char> &os, const ::quasar::core::Color<T, N> &col) {
			if (os) {
				bool isCharOrUChar = typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char);
				os << "rgba(";
				for (unsigned char i = 0; i < N; i++) {
					if (i > 0) {
						os << ", ";
					}
					if (isCharOrUChar) {
						os << (int)col.data(i);
					} else {
						os << col.data(i);
					}
				}
				os << ")";
			}
			return os;
		}

		template<typename T, unsigned char N>
		::std::basic_istream<char>     &operator>>(::std::basic_istream<char> &is, ::quasar::core::Color<T, N> &col) {
			if (is) {
				quasar::core::BasicString<char> type, values;
				char buf[255] = {0};
				is.getline(buf, 255, '(');
				type = buf;
				is.getline(buf, 255, ')');
				values = buf;
				type.rtrim("(").trim();
				bool isCharOrUChar = typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char);
				auto parts = values.split(",");
				std::basic_stringstream<char> conv;
				for (unsigned char i = 0; i < N; i++) {
					conv.clear();
					conv.str(parts[i]);
					if (isCharOrUChar) {
						conv >> (int&)col.data(i);
					} else {
						conv >> col.data(i);
					}
				}
			}
			return is;
		}

		template<typename T, unsigned char N>
		::std::basic_ostream<wchar_t>     &operator<<(::std::basic_ostream<wchar_t> &os, const ::quasar::core::Color<T, N> &col) {
			if (os) {
				bool isCharOrUChar = typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char);
				os << "rgba(";
				for (unsigned wchar_t i = 0; i < N; i++) {
					if (i > 0) {
						os << ", ";
					}
					if (isCharOrUChar) {
						os << (int)col.data(i);
					} else {
						os << col.data(i);
					}
				}
				os << ")";
			}
			return os;
		}

		template<typename T, unsigned wchar_t N>
		::std::basic_istream<wchar_t>     &operator>>(::std::basic_istream<wchar_t> &is, ::quasar::core::Color<T, N> &col) {
			if (is) {
				quasar::core::BasicString<wchar_t> type, values;
				wchar_t buf[255] = {0};
				is.getline(buf, 255, L'(');
				type = buf;
				is.getline(buf, 255, L')');
				values = buf;
				type.rtrim(L"(").trim();
				bool isCharOrUChar = typeid(T) == typeid(char) || typeid(T) == typeid(unsigned char);
				auto parts = values.split(L",");
				std::basic_stringstream<wchar_t> conv;
				for (unsigned char i = 0; i < N; i++) {
					conv.clear();
					conv.str(parts[i]);
					if (isCharOrUChar) {
						conv >> (int&)col.data(i);
					} else {
						conv >> col.data(i);
					}
				}
			}
			return is;
		}

		template<typename T> using Color1 = Color<T, 1>;
		template<typename T> using Color2 = Color<T, 2>;
		template<typename T> using Color3 = Color<T, 3>;
		template<typename T> using Color4 = Color<T, 4>;

		using Color1uc = Color<unsigned char, 1>;
		using Color1us = Color<unsigned short, 1>;
		using Color1ui = Color<unsigned int, 1>;
		using Color1ul = Color<unsigned long, 1>;

		using Color1c = Color<char, 1>;
		using Color1s = Color<short, 1>;
		using Color1i = Color<int, 1>;
		using Color1l = Color<long, 1>;

		using Color1d = Color<double, 1>;
		using Color1f = Color<float, 1>;

		using Color2uc = Color<unsigned char, 2>;
		using Color2us = Color<unsigned short, 2>;
		using Color2ui = Color<unsigned int, 2>;
		using Color2ul = Color<unsigned long, 2>;

		using Color2c = Color<char, 2>;
		using Color2s = Color<short, 2>;
		using Color2i = Color<int, 2>;
		using Color2l = Color<long, 2>;

		using Color2d = Color<double, 2>;
		using Color2f = Color<float, 2>;

		using Color3uc = Color<unsigned char, 3>;
		using Color3us = Color<unsigned short, 3>;
		using Color3ui = Color<unsigned int, 3>;
		using Color3ul = Color<unsigned long, 3>;

		using Color3c = Color<char, 3>;
		using Color3s = Color<short, 3>;
		using Color3i = Color<int, 3>;
		using Color3l = Color<long, 3>;

		using Color3d = Color<double, 3>;
		using Color3f = Color<float, 3>;

		using Color4uc = Color<unsigned char, 4>;
		using Color4us = Color<unsigned short, 4>;
		using Color4ui = Color<unsigned int, 4>;
		using Color4ul = Color<unsigned long, 4>;

		using Color4c = Color<char, 4>;
		using Color4s = Color<short, 4>;
		using Color4i = Color<int, 4>;
		using Color4l = Color<long, 4>;

		using Color4d = Color<double, 4>;
		using Color4f = Color<float, 4>;
	}
}

#endif //QUASARFX_COLOR_H
