//
// Created by darkboss on 8/22/20.
//

#include "Config.h"

namespace quasar {
	namespace core {

		template<> String                   ConfigNode::getValue() const noexcept { return mValue; }
		template<> void                     ConfigNode::setValue(const String &value) noexcept { mValue = value; }

		template<> bool                     ConfigNode::getValue() const noexcept {
			StringStream ss;
			ss << std::boolalpha << mValue;
			bool ret = false;
			ss >> ret;
			return ret;
		}
		template<> void                     ConfigNode::setValue(const bool &value) noexcept {
			StringStream ss;
			ss << std::boolalpha << value;
			mValue = ss.str();
		}

		template<> std::nullptr_t           ConfigNode::getValue() const noexcept { return nullptr; }
		template<> void                     ConfigNode::setValue(const std::nullptr_t &value) noexcept { mValue = "null"; }

		ConfigNode::ConfigNode(ConfigNode *parent,
							   const String &name,
							   const child_store_type &children,
							   const prop_store_type &props,
							   const String &value)
			: mParent(parent)
			, mChildren(children)
			, mProps(props)
			, mName(name)
			, mValue(value)
		{}

		ConfigNode::ConfigNode(const ConfigNode &rhs) {
			*this = rhs;
		}

		ConfigNode &ConfigNode::operator=(const ConfigNode &rhs) {
			mParent = rhs.mParent;
			mChildren = rhs.mChildren;
			mProps = rhs.mProps;
			mName = rhs.mName;
			mValue = rhs.mValue;
			for (auto &child: mChildren) {
				acquireChild(child);
			}
			return *this;
		}

		void        ConfigNode::acquireChild(ConfigNode &child) {
			child.setParent(this);
			for (auto &child2: child.getChildren()) {
				acquireChild(child2);
			}
		}

		const String &ConfigNode::getName() const noexcept { return mName; }

		void ConfigNode::setName(const String &name) noexcept { mName = name; }

		template<typename T>
		void ConfigNode::setValue(const T &value) noexcept {
			StringStream ss;
			ss << value;
			mValue = ss.str();
		}

		const ConfigNode *ConfigNode::getParent() const noexcept { return mParent; }

		ConfigNode *ConfigNode::getParent() noexcept { return mParent; }

		void ConfigNode::setParent(ConfigNode *parent) { mParent = parent; }

		bool                    ConfigNode::hasChildren() const {
			return !mChildren.empty();
		}
		ConfigNode *ConfigNode::createChild(const String &name) {
			child_iter_type child = findChild(name);
			if (child == mChildren.end()) {
				mChildren.add(ConfigNode(this, name));
				child = mChildren.end() - 1;
			}
			return &*child;
		}

		const ConfigNode::child_store_type &ConfigNode::getChildren() const noexcept { return mChildren; }

		ConfigNode::child_store_type &ConfigNode::getChildren() noexcept { return mChildren; }

		const ConfigNode *ConfigNode::getChild(const String &name, bool except) const noexcept(false) {
			auto it = mChildren.find([&](const ConfigNode &n) {
				return n.getName() == name;
			});
			if (it != mChildren.end()) {
				return &*it;
			}
			if (except) {
				throw std::runtime_error("missing child '" + std::string(name.begin(), name.end()) + "' in ConfigNode '" + std::string(mName.begin(), mName.end()) + "'");
			}
			return nullptr;
		}

		const ConfigNode            *ConfigNode::getFirstChild() const {
			if (!mChildren.empty()) {
				return &mChildren->front();
			}
			return nullptr;
		}
		ConfigNode                  *ConfigNode::getFirstChild() {
			if (!mChildren.empty()) {
				return &mChildren->front();
			}
			return nullptr;
		}
		const ConfigNode            *ConfigNode::getLastChild() const {
			if (!mChildren.empty()) {
				return &mChildren->back();
			}
			return nullptr;
		}
		ConfigNode                  *ConfigNode::getLastChild() {
			if (!mChildren.empty()) {
				return &mChildren->back();
			}
			return nullptr;
		}

		ConfigNode *ConfigNode::setChild(const String &name, const ConfigNode &n) noexcept(false) {
			auto it = findChild(name);
			if (it == mChildren.end()) {
				createChild(name);
				it = findChild(name);
			}
			*it = n;
			return &*it;
		}

		ConfigNode *ConfigNode::getChild(const String &name, bool except) noexcept(false) {
			auto it = mChildren.find([&](const ConfigNode &n) {
				return n.getName() == name;
			});
			if (it != mChildren.end()) {
				return &*it;
			}
			if (except) {
				throw std::runtime_error("missing child '" + std::string(name.begin(), name.end()) + "' in ConfigNode '" + std::string(mName.begin(), mName.end()) + "'");
			}
			return nullptr;
		}

		bool ConfigNode::hasChild(const String &name) noexcept {
			return getChild(name, false) != nullptr;
		}

		bool ConfigNode::removeChild(const String &name, ConfigNode *out) {
			for (auto it = mChildren.begin(); it != mChildren.end(); it++) {
				if (it->getName() == name) {
					if (out) {
						*out = *it;
					}
					mChildren->erase(it);
					return true;
				}
			}
			return false;
		}

		const ConfigNode::prop_store_type &ConfigNode::getProperties() const noexcept { return mProps; }

		ConfigNode::prop_store_type &ConfigNode::getProperties() noexcept { return mProps; }

		bool ConfigNode::hasProperty(const String &name) noexcept {
			auto prop = mProps->find(name);
			return prop != mProps.end();
		}

		bool ConfigNode::removeProperty(const String &name, String *out) {
			auto prop = mProps->find(name);
			if (prop == mProps.end()) {
				return false;
			}
			if (out) {
				*out = prop->second;
			}
			return true;
		}

		ConfigNode::child_iter_type ConfigNode::findChild(const String &name) {
			for (auto it = mChildren.begin(); it != mChildren.end(); it++) {
				if (it->getName() == name) {
					return it;
				}
			}
			return mChildren.end();
		}

		ConfigNode::child_citer_type ConfigNode::findChild(const String &name) const {
			for (auto it = mChildren.begin(); it != mChildren.end(); it++) {
				if (it->getName() == name) {
					return it;
				}
			}
			return mChildren.end();
		}


		ConfigNode::child_riter_type ConfigNode::rfindChild(const String &name) {
			for (auto it = mChildren.rbegin(); it != mChildren.rend(); it++) {
				if (it->getName() == name) {
					return it;
				}
			}
			return mChildren.rend();
		}

		ConfigNode::child_criter_type ConfigNode::rfindChild(const String &name) const {
			for (auto it = mChildren.crbegin(); it != mChildren.crend(); it++) {
				if (it->getName() == name) {
					return it;
				}
			}
			return mChildren.crend();
		}

		ConfigNode *ConfigNode::addChild(const ConfigNode &n) {
			if (hasChild(n.getName())) {
				throw std::runtime_error("Child '" + std::string(n.getName().begin(), n.getName().end()) + "' already exists in ConfigNode '" + std::string(mName.begin(), mName.end()) + "'");
			}
			mChildren.add(n);
			mChildren->back().setParent(this);
			return &mChildren->back();
		}

		ConfigNode ConfigNode::merged(const ConfigNode &with) const {
			ConfigNode ret(*this);
			ret.merge(with);
			return ret;
		}

		ConfigNode  &ConfigNode::merge(const ConfigNode &with) {
			if (!with.mName.empty()) {
				mName = with.mName;
			}
			if (!with.mValue.empty()) {
				mValue = with.mValue;
			}
			for (auto const& child: with.mChildren) {
				addChild(child);
			}
			for (auto const& prop: with.mProps) {
				setProperty(prop.first, prop.second);
			}
			return *this;
		}

		template<typename T>
		T ConfigNode::getValue() const noexcept { return mValue; }

		ConfigFile::ConfigFile()
				: Resource(), ConfigNode() {}

		ConfigFile::ConfigFile(ResourceFactory *factory, const String &name, const String &path,
		                       const ResourceType &type, const PropertyMap &props, const SharedIOStream &stream)
				: Resource(factory, name, path, type == ResourceType::Unknown ? ResourceType::Config : type, props, stream)
				, ConfigNode()
		{}

		void ConfigFile::setName(const String &name) noexcept {
			Resource::setName(name);
		}

		const String &ConfigFile::getName() const noexcept {
			return Resource::getName();
		}
	}
}