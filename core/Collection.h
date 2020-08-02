//
// Created by darkboss on 8/2/20.
//

#ifndef QUASARFX_COLLECTION_H
#define QUASARFX_COLLECTION_H

#include <vector>
#include <functional>

namespace quasar {
	namespace core {
		template<typename Value, typename Container = std::vector<Value>>
		class Collection {
		public:
			using value_type = Value;
			using container_type = Container;
			using self_type = Collection<Value, Container>;

			using iter_type = typename container_type::iterator;
			using riter_type = typename container_type::reverse_iterator;

			using citer_type = typename container_type::const_iterator;
			using criter_type = typename container_type::const_reverse_iterator;

			using cfilter_predicate = std::function<bool(const value_type&)>;
			using cfilter_predicate_with_id = std::function<bool(size_t i, const value_type&)>;

			using filter_predicate = std::function<bool(value_type&)>;
			using filter_predicate_with_id = std::function<bool(size_t i, value_type&)>;

			using map_fn = std::function<value_type(const value_type&)>;
			using map_fn_with_id = std::function<value_type(size_t, const value_type&)>;

			template<typename Carry = value_type>
			using fold_fn = std::function<Carry(Carry, const Value &)>;

			template<typename Carry = value_type>
			using fold_fn_with_id = std::function<Carry(size_t id, const Carry &, const Value &)>;

		protected:
			container_type      mData;

		public:
			Collection() = default;
			explicit Collection(const container_type &data): mData(data) {}
			Collection(const std::initializer_list<Value> &data): mData(data) {}
			Collection(const Collection &rhs) = default;
			virtual ~Collection() = default;

			Collection          &operator=(const Collection &rhs) = default;
			Collection          &operator=(const std::initializer_list<Value> &rhs) {
				mData = rhs.mData;
				return *this;
			}

			container_type      &&operator*() noexcept { return mData; }
			const container_type&&operator*() const noexcept { return mData; }

			container_type      *operator->() noexcept { return &mData; }
			const container_type*operator->() const noexcept { return &mData; }

			const container_type&&data() const noexcept { return mData; }
			container_type      &&data() noexcept { return mData; }

			void                clear() noexcept { mData.clear(); }
			bool                empty() const noexcept { return mData.empty(); }
			size_t              size() const noexcept { return mData.size(); }
			void                add(Value &&v) { mData.push_back(v); }

			bool                includes(const Value &wanted) const noexcept {
				return find([&](const Value &it) {
					return it == wanted;
				}) != nullptr;
			}

			/**
			 * Iterate over each element. If true is returned from the predicate, stop the iteration.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			Value returned from predicate
			 */
			bool                forEach(filter_predicate p) noexcept {
				for (iter_type it = mData.begin(); it != mData.end(); ++it) {
					if (p(*it)) {
						return true;
					}
				}
				return false;
			}

			/**
			 * Iterate over each const element. If true is returned from the predicate, stop the iteration.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			Value returned from predicate
			 */
			bool                forEach(cfilter_predicate p) const noexcept {
				for (citer_type it = mData.begin(); it != mData.end(); ++it) {
					if (p(*it)) {
						return true;
					}
				}
				return false;
			}

			/**
			 * Find a specific element by iterating over all elements and calling the predicate.
			 * If the predicate returns true, the element at the corresponding position is returned.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			The element found or null
			 */
			const Value         *find(cfilter_predicate p) const noexcept {
				for (citer_type it = mData.begin(); it != mData.end(); ++it) {
					if (p(*it)) {
						return &*it;
					}
				}
				return nullptr;
			}


			/**
			 * Find a specific element by iterating over all elements and calling the predicate.
			 * If the predicate returns true, the element at the corresponding position is returned.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			The element found or null
			 */
			const Value         *find(cfilter_predicate_with_id p) const noexcept {
				size_t id = 0;
				for (citer_type it = mData.begin(); it != mData.end(); ++it, ++id) {
					if (p(id, *it)) {
						return &*it;
					}
				}
				return nullptr;
			}


			/**
			 * Find a specific element by iterating over all elements and calling the predicate.
			 * If the predicate returns true, the element at the corresponding position is returned.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			The element found or null
			 */
			Value               *find(cfilter_predicate p) noexcept {
				for (iter_type it = mData.begin(); it != mData.end(); ++it) {
					if (p(*it)) {
						return &*it;
					}
				}
				return nullptr;
			}


			/**
			 * Find a specific element by iterating over all elements and calling the predicate.
			 * If the predicate returns true, the element at the corresponding position is returned.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			The element found or null
			 */
			Value               *find(cfilter_predicate_with_id p) noexcept {
				size_t id = 0;
				for (iter_type it = mData.begin(); it != mData.end(); ++it, ++id) {
					if (p(id, *it)) {
						return &*it;
					}
				}
				return nullptr;
			}

			/**
			 * Reverse-find a specific element by iterating over all elements (starting from the end)
			 * and calling the predicate. If the predicate returns true, the element at the corresponding
			 * position is returned.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			The element found or null
			 */
			const Value         *rfind(cfilter_predicate p) const noexcept {
				for (criter_type it = mData.rbegin(); it != mData.rend(); ++it) {
					if (p(*it)) {
						return &*it;
					}
				}
				return nullptr;
			}

			/**
			 * Reverse-find a specific element by iterating over all elements (starting from the end)
			 * and calling the predicate. If the predicate returns true, the element at the corresponding
			 * position is returned.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			The element found or null
			 */
			const Value         *rfind(cfilter_predicate_with_id p) const noexcept {
				size_t id = 0;
				for (criter_type it = mData.rbegin(); it != mData.rend(); ++it, ++id) {
					if (p(id, *it)) {
						return &*it;
					}
				}
				return nullptr;
			}

			/**
			 * Reverse-find a specific element by iterating over all elements (starting from the end)
			 * and calling the predicate. If the predicate returns true, the element at the corresponding
			 * position is returned.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			The element found or null
			 */
			Value               *rfind(cfilter_predicate p) noexcept {
				for (riter_type it = mData.rbegin(); it != mData.rend(); ++it) {
					if (p(*it)) {
						return &*it;
					}
				}
				return nullptr;
			}

			/**
			 * Reverse-find a specific element by iterating over all elements (starting from the end)
			 * and calling the predicate. If the predicate returns true, the element at the corresponding
			 * position is returned.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			The element found or null
			 */
			Value               *rfind(cfilter_predicate_with_id p) noexcept {
				size_t id = 0;
				for (riter_type it = mData.rbegin(); it != mData.rend(); ++it, ++id) {
					if (p(id, *it)) {
						return *it;
					}
				}
				return nullptr;
			}

			/**
			 * Aggregate all elements matching the predicate by.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			A new collection representing this aggregation
			 */
			Collection          filter(cfilter_predicate p) const noexcept {
				Collection ret;
				for (citer_type it = mData.begin(); it != mData.end(); ++it) {
					if (p(*it)) {
						ret.mData.push_back(*it);
					}
				}
				return ret;
			}

			/**
			 * Aggregate all elements matching the predicate by.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			A new collection representing this aggregation
			 */
			Collection          filter(cfilter_predicate_with_id p) const noexcept {
				Collection      ret;
				size_t          id = 0;
				for (citer_type it = mData.begin(); it != mData.end(); ++it, ++id) {
					if (p(id, *it)) {
						ret.mData.push_back(*it);
					}
				}
				return ret;
			}


			/**
			 * Aggregate all elements matching the predicate by, starting  at the end.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			A new collection representing this aggregation
			 */
			Collection          rfilter(cfilter_predicate p) const noexcept {
				Collection ret;
				for (criter_type it = mData.rbegin(); it != mData.rend(); ++it) {
					if (p(*it)) {
						ret.mData.push_back(*it);
					}
				}
				return ret;
			}

			/**
			 * Aggregate all elements matching the predicate by, starting at the end.
			 *
			 * @param p			Predicate called on each element.
			 *
			 * @return			A new collection representing this aggregation
			 */
			Collection          rfilter(cfilter_predicate_with_id p) const noexcept {
				Collection      ret;
				size_t          id = mData.size() - 1;
				for (criter_type it = mData.rbegin(); it != mData.rend(); ++it, --id) {
					if (p(id, *it)) {
						ret.mData.push_back(*it);
					}
				}
				return ret;
			}

			/**
			 * Apply a transformation to each element.
			 *
			 * @param mapper	Transformation function called on each element.
			 *
			 * @return			A new collection representing this transformation
			 */
			Collection          map(map_fn mapper) const noexcept {
				Collection      ret;
				for (citer_type it = mData.begin(); it != mData.end(); ++it) {
					ret.mData.push_back(mapper(*it));
				}
				return ret;
			}

			/**
			 * Apply a transformation to each element.
			 *
			 * @param mapper	Transformation function called on each element.
			 *
			 * @return			A new collection representing this transformation
			 */
			Collection          map(map_fn_with_id mapper) const noexcept {
				Collection      ret;
				size_t          id = 0;
				for (citer_type it = mData.begin(); it != mData.end(); ++it, ++id) {
					ret.mData.push_back(mapper(id, *it));
				}
				return ret;
			}

			/**
			 * Apply a transformation to each element starting from the end.
			 *
			 * @param mapper	Transformation function called on each element.
			 *
			 * @return			A new collection representing this transformation
			 */
			Collection          rmap(map_fn mapper) const noexcept {
				Collection      ret;
				for (criter_type it = mData.rbegin(); it != mData.rend(); ++it) {
					ret.mData.push_back(mapper(*it));
				}
				return ret;
			}

			/**
			 * Apply a transformation to each element starting from the end.
			 *
			 * @param mapper	Transformation function called on each element.
			 *
			 * @return			A new collection representing this transformation
			 */
			Collection          rmap(map_fn_with_id mapper) const noexcept {
				Collection      ret;
				size_t id = mData.size() - 1;
				for (criter_type it = mData.rbegin(); it != mData.rend(); ++it, --id) {
					ret.mData.push_back(mapper(id, *it));
				}
				return ret;
			}

			/**
			 * Reduce this collection to a simple value.
			 *
			 * @param r			Transformation function called on each element.
			 *
			 * @return			A value representing this transformation
			 */
			template<typename Carry = value_type>
			Carry               fold(fold_fn<Carry> r, Carry c = Carry()) {
				for (citer_type it = mData.begin(); it != mData.end(); ++it) {
					c = r(c, *it);
				}
				return c;
			}

			/**
			 * Reduce this collection to a simple value.
			 *
			 * @param r			Transformation function called on each element.
			 *
			 * @return			A value representing this transformation
			 */
			template<typename Carry = value_type>
			Carry               fold(fold_fn_with_id<Carry> r, Carry c = Carry()) {
				size_t id = 0;
				for (citer_type it = mData.begin(); it != mData.end(); ++it, ++id) {
					c = r(id, c, *it);
				}
				return c;
			}

			/**
			 * Reduce this collection to a simple value starting at the end.
			 *
			 * @param r			Transformation function called on each element.
			 *
			 * @return			A value representing this transformation
			 */
			template<typename Carry = value_type>
			Carry               rfold(fold_fn<Carry> r, Carry c = Carry()) {
				for (criter_type it = mData.rbegin(); it != mData.rend(); ++it) {
					c = r(c, *it);
				}
				return c;
			}

			/**
			 * Reduce this collection to a simple value starting at the end.
			 *
			 * @param r			Transformation function called on each element.
			 *
			 * @return			A value representing this transformation
			 */
			template<typename Carry = value_type>
			Carry               rfold(fold_fn_with_id<Carry> r, Carry c = Carry()) {
				size_t id = mData.size() - 1;
				for (criter_type it = mData.rbegin(); it != mData.rend(); ++it, --id) {
					c = r(id, c, *it);
				}
				return c;
			}
		};
	}
}

#endif //QUASARFX_COLLECTION_H
