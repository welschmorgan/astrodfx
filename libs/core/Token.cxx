//
// Created by darkboss on 9/5/20.
//

#include "Token.h"
#include "TokenList.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		BasicTokenList<CharT>   BasicToken<CharT>::takeNextUntil(const list_type &stoppers, bool including) {
			list_type           ret;
			if (mParent == nullptr) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' is an orphan, no parent list defined");
			}
			auto it = mParent->iter(*this);
			if (it == mParent->end()) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' has a parent list, but is not in it");
			}
			typename list_type::citer_type stopperFound;
			while (it != mParent->end()) {
				stopperFound = stoppers.find([=](const self_type &stopper) {
					return stopper.getType() == it->getType() && stopper.getTrigger() == it->getTrigger();
				});
				if (stopperFound != stoppers.end()) {
					if (including) {
						ret.add(*it);
						it = (*mParent)->erase(it);
					}
					break;
				} else {
					ret.add(*it);
					it = (*mParent)->erase(it);
				}
			}
			return ret;
		}

		template<typename CharT>
		BasicTokenList<CharT>   BasicToken<CharT>::takePreviousUntil(const list_type &stoppers, bool including) {
			list_type           ret;
			if (mParent == nullptr) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' is an orphan, no parent list defined");
			}
			auto it = mParent->riter(*this);
			if (it == mParent->rend()) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' has a parent list, but is not in it");
			}
			typename list_type::citer_type stopperFound;
			while (it != mParent->rend()) {
				stopperFound = stoppers.find([=](const self_type &stopper) {
					return stopper.getType() == it->getType() && stopper.getTrigger() == it->getTrigger();
				});
				if (stopperFound != stoppers.end()) {
					if (including) {
						ret.add(*it);
						it = decltype(it)((*mParent)->erase(std::next(it).base()));
					}
					break;
				} else {
					ret.add(*it);
					it = decltype(it)((*mParent)->erase(std::next(it).base()));
				}
			}
			return ret;
		}

		template<typename CharT>
		const BasicToken<CharT> *BasicToken<CharT>::getPreviousSibling(const self_type &type) const {
			list_type           ret;
			if (mParent == nullptr) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' is an orphan, no parent list defined");
			}
			auto it = mParent->riter(*this);
			if (it == mParent->rend()) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' has a parent list, but is not in it");
			}
			typename list_type::citer_type stopperFound;
			while (it != mParent->rend()) {
				if (type.getType() == it->getType() && type.getTrigger() == it->getTrigger()) {
					return &*it;
				}
				it++;
			}
			return nullptr;
		}


		template<typename CharT>
		BasicToken<CharT> *BasicToken<CharT>::getPreviousSibling(const self_type &type) {
			list_type           ret;
			if (mParent == nullptr) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' is an orphan, no parent list defined");
			}
			auto it = mParent->riter(*this);
			if (it == mParent->rend()) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' has a parent list, but is not in it");
			}
			typename list_type::citer_type stopperFound;
			while (it != mParent->rend()) {
				if (type.getType() == it->getType() && type.getTrigger() == it->getTrigger()) {
					return &*it;
				}
				it++;
			}
			return nullptr;
		}

		template<typename CharT>
		const BasicToken<CharT> *BasicToken<CharT>::getNextSibling(const self_type &type) const {
			list_type           ret;
			if (mParent == nullptr) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' is an orphan, no parent list defined");
			}
			auto it = mParent->iter(*this);
			if (it == mParent->end()) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' has a parent list, but is not in it");
			}
			typename list_type::citer_type stopperFound;
			while (it != mParent->end()) {
				if (type.getType() == it->getType() && type.getTrigger() == it->getTrigger()) {
					return &*it;
				}
				it++;
			}
			return nullptr;
		}


		template<typename CharT>
		BasicToken<CharT> *BasicToken<CharT>::getNextSibling(const self_type &type) {
			list_type           ret;
			if (mParent == nullptr) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' is an orphan, no parent list defined");
			}
			auto it = mParent->iter(*this);
			if (it == mParent->end()) {
				throw std::runtime_error("Token '" + std::string(mTrigger.begin(), mTrigger.end()) + "' has a parent list, but is not in it");
			}
			typename list_type::citer_type stopperFound;
			while (it != mParent->end()) {
				if (type.getType() == it->getType() && type.getTrigger() == it->getTrigger()) {
					return &*it;
				}
				it++;
			}
			return nullptr;
		}

		template class BasicToken<char>;
		template class BasicToken<wchar_t>;
	}
}