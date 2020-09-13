//
// Created by darkboss on 8/21/20.
//

#ifndef QUASARFX_RECT_H
#define QUASARFX_RECT_H

#include <algorithm>
#include "Vector.h"

namespace quasar {
	namespace math {
		template<typename T, unsigned short Dim>
		class Rect {
		public:
			using value_type = T;
			using point_type = Vec<T, Dim>;
			using self_type = Rect<T, Dim>;

			static const unsigned short Dimensions = Dim;

		protected:
			point_type mPos;
			point_type mSize;

		public:
			Rect() = default;
			Rect(const point_type &pos, const point_type &size)
				: mPos(pos)
				, mSize(size)
			{}
			Rect(const self_type &rhs) = default;
			~Rect() = default;

			self_type           &operator=(const self_type &rhs) = default;

			point_type          min() const noexcept {
				point_type ret;
				for (unsigned short i = 0; i < Dimensions; i++) {
					ret.data(i) = std::min(mPos.data(i), mPos.data(i) + mSize.data(i));
				}
				return ret;
			}

			point_type          max() const noexcept {
				point_type ret;
				for (unsigned short i = 0; i < Dimensions; i++) {
					ret.data(i) = std::max(mPos.data(i), mPos.data(i) + mSize.data(i));
				}
				return ret;
			}

			const point_type    &position() const noexcept {
				return mPos;
			}

			const point_type    &size() const noexcept {
				return mSize;
			}

			self_type           &grow(const point_type &by) noexcept {
				mSize += by;
				return *this;
			}

			self_type           &shrink(const point_type &by) noexcept {
				mSize -= by;
				mSize.x = std::max(mSize.x, 0);
				mSize.y = std::max(mSize.y, 0);
				return *this;
			}

			self_type           &scale(const point_type &by) noexcept {
				mSize *= by;
				return *this;
			}
		};

		template<typename T> using Rect2 = Rect<T, 2>;
		using Rect2c = Rect2<char>;
		using Rect2s = Rect2<short>;
		using Rect2i = Rect2<int>;
		using Rect2l = Rect2<long>;
		using Rect2uc = Rect2<unsigned char>;
		using Rect2us = Rect2<unsigned short>;
		using Rect2ui = Rect2<unsigned int>;
		using Rect2ul = Rect2<unsigned long>;
		using Rect2f = Rect2<float>;
		using Rect2d = Rect2<double>;
	}
}


#endif //QUASARFX_RECT_H
