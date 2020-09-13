//
// Created by darkboss on 8/30/20.
//

#ifndef QUASARFX_EITHER_H
#define QUASARFX_EITHER_H

#include <stdexcept>
#include "String.h"

namespace quasar {
	namespace core {
		template<typename LeftT, typename RightT>
		class Either {
		public:
			enum value_type {
				Left,
				Right
			};

			using left_type = LeftT;
			using right_type = RightT;

		protected:

			union {
				left_type   mLeft;
				right_type  mRight;
			};

			value_type      mType;

		public:
			Either()
			{ alloc(Left); }

			explicit Either(const LeftT &l)
			{
				alloc(Left);
				mLeft = l;
			}

			explicit Either(const RightT &r)
			{
				alloc(Right);
				mRight = r;
			}

			~Either() {
				dealloc();
			}

			Either(const Either &rhs) {
				alloc(Left);
				copy(rhs);
			}


			Either              &operator=(const Either &rhs) {
				dealloc();
				copy(rhs);
				return *this;
			}

			bool                operator<(const Either &rhs) const {
				switch (mType) {
					case Left:
						return mLeft < rhs.mLeft;
					case Right:
						return mRight < rhs.mRight;
					default:
						throw std::logic_error("Unknown Either part");
				}
			}

			bool                operator>(const Either &rhs) const {
				switch (mType) {
					case Left:
						return mLeft > rhs.mLeft;
					case Right:
						return mRight > rhs.mRight;
					default:
						throw std::logic_error("Unknown Either part");
				}
			}

			bool                operator<=(const Either &rhs) const {
				switch (mType) {
					case Left:
						return mLeft <= rhs.mLeft;
					case Right:
						return mRight <= rhs.mRight;
					default:
						throw std::logic_error("Unknown Either part");
				}
			}

			bool                operator>=(const Either &rhs) const {
				switch (mType) {
					case Left:
						return mLeft >= rhs.mLeft;
					case Right:
						return mRight >= rhs.mRight;
					default:
						throw std::logic_error("Unknown Either part");
				}
			}

			bool                operator==(const Either &rhs) const {
				if (mType != rhs.mType) {
					return false;
				}
				switch (mType) {
					case Left:
						return mLeft == rhs.mLeft;
					case Right:
						return mRight == rhs.mRight;
					default:
						throw std::logic_error("Unknown Either part");
				}
			}

			bool                operator!=(const Either &rhs) const {
				return !(*this == rhs);
			}



			Either              &setLeft(const left_type &l) {
				mType = Left;
				mLeft = l;
				return *this;
			}

			Either              &setRight(const right_type &r) {
				mType = Right;
				mRight = r;
				return *this;
			}

			Either              &set(const left_type &l) {
				return setLeft(l);
			}

			Either              &set(const right_type &r) {
				return setRight(r);
			}

			left_type           &left() noexcept(false) {
				if (mType != Left) {
					throw std::logic_error("Either is not of type " + std::string(typeid(left_type).name()) + ", but of type " + std::string(typeid(right_type).name()));
				}
				return mLeft;
			}

			left_type           left() const noexcept(false) {
				if (mType != Left) {
					throw std::logic_error("Either is not of type " + std::string(typeid(left_type).name()) + ", but of type " + std::string(typeid(right_type).name()));
				}
				return mLeft;
			}

			right_type          &right() noexcept(false) {
				if (mType != Right) {
					throw std::logic_error("Either is not of type " + std::string(typeid(right_type).name()) + ", but of type " + std::string(typeid(right_type).name()));
				}
				return mRight;
			}

			right_type          right() const noexcept(false) {
				if (mType != Right) {
					throw std::logic_error("Either is not of type " + std::string(typeid(right_type).name()) + ", but of type " + std::string(typeid(left_type).name()));
				}
				return mRight;
			}

			value_type          type() const noexcept {
				return mType;
			}

			bool                isRight() const noexcept {
				return mType == Right;
			}

			bool                isLeft() const noexcept {
				return mType == Left;
			}

			explicit operator   left_type() const {
				return left();
			}

			explicit operator   right_type() const {
				return right();
			}

		protected:
			void            alloc(value_type type) {
				mType = type;
				switch (mType) {
					case Left:
						new (&mLeft) left_type();
						break;
					case Right:
						new (&mRight) right_type();
						break;
					default:
						throw std::logic_error("Unknown Either type");
				}
			}
			void            dealloc() {
				switch (mType) {
					case Left:
						mLeft.~left_type();
						break;
					case Right:
						mRight.~right_type();
						break;
					default:
						throw std::logic_error("Unknown Either type");
				}
			}
			void            copy(const Either &rhs) {
				dealloc();
				mType = rhs.mType;
				switch (mType) {
					case Left:
						new (&mLeft) auto(rhs.mLeft);
						break;
					case Right:
						new (&mRight) auto(rhs.mRight);
						break;
					default:
						throw std::logic_error("Unknown Either type");
				}
			}
		};
	}
}

template<typename LeftT, typename RightT>
quasar::core::OStream       &operator<<(quasar::core::OStream &os, const quasar::core::Either<LeftT, RightT> &e) {
	if (os) {
		if (e.isLeft()) {
			os << e.left();
		} else {
			os << e.right();
		}
	}
	return os;
}


template<typename LeftT, typename RightT>
quasar::core::IStream       &operator>>(quasar::core::IStream &is, quasar::core::Either<LeftT, RightT> &e) {
	if (is) {
		LeftT l;
		RightT r;
		if (e.isLeft()) {
			is >> l;
			e.set(l);
		} else {
			is >> r;
			e.set(r);
		}
	}
	return is;
}


#endif //QUASARFX_EITHER_H
