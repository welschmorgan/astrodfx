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

		ConfigNode::ConfigNode(ConfigNode *parent, const String &name)
				: mParent(parent)
				, mChildren()
				, mProps()
				, mName(name)
				, mValue()
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
			ConfigNode              *child = getChild(name);
			if (!child) {
				mChildren.add(ConfigNode(this, name));
				child = &mChildren->back();
			}
			return child;
		}

		const ConfigNode::child_store_type &ConfigNode::getChildren() const noexcept { return mChildren; }

		ConfigNode::child_store_type &ConfigNode::getChildren() noexcept { return mChildren; }

		const ConfigNode *ConfigNode::getChild(const String &name) const noexcept {
			auto it = mChildren.find([&](const ConfigNode &n) {
				return n.getName() == name;
			});
			if (it != mChildren.end()) {
				return &*it;
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

		ConfigNode *ConfigNode::getChild(const String &name) noexcept {
			auto it = mChildren.find([&](const ConfigNode &n) {
				return n.getName() == name;
			});
			if (it != mChildren.end()) {
				return &*it;
			}
			return nullptr;
		}

		bool ConfigNode::hasChild(const String &name) noexcept {
			return getChild(name) != nullptr;
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

		ConfigNode &ConfigNode::setProperty(const String &name, const String &value) {
			mProps.put(name, value);
			return *this;
		}

		const ConfigNode::prop_store_type &ConfigNode::getProperties() const noexcept { return mProps; }

		ConfigNode::prop_store_type &ConfigNode::getProperties() noexcept { return mProps; }

		const String &ConfigNode::getProperty(const String &name) const {
			auto prop = mProps->find(name);
			if (prop == mProps.end()) {
				throw std::runtime_error("Unknown property '" + name + "' in config node '" + mName + "'");
			}
			return prop->second;
		}

		String &ConfigNode::getProperty(const String &name) {
			auto prop = mProps->find(name);
			if (prop == mProps.end()) {
				throw std::runtime_error("Unknown property '" + name + "' in config node '" + mName + "'");
			}
			return prop->second;
		}

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

		template<typename T>
		T ConfigNode::getValue() const noexcept { return mValue; }

		void
		ConfigNodeSerializer::dump(ConfigNodeSerializer::ostream_type &os, const ConfigNodeSerializer::value_type *node,
		                           int indent) {
			bool hasChildren = !node->getChildren().empty();
			bool hasProps = !node->getProperties().empty();
			bool hasValue = !node->getValue().empty();
			bool isSimple = !hasProps && !hasChildren;
			bool hasName = !node->getName().empty();
			String indentStr = String(indent, '\t');
			String nextIndentStr = String(indent + 1, '\t');

			os << indentStr << node->getName();
			if (hasValue) {
				os << (hasName ? ": " : "") << node->getValue();
			}
			if (!isSimple) {
				os << (hasName ? " " : "") << "{" << std::endl;
				if (hasProps) {
					for (auto &prop: node->getProperties()) {
						os << nextIndentStr << prop.first << " = " << prop.second << std::endl;
					}
					os << std::endl;
				}
				for (auto &child: node->getChildren()) {
					dump(os, &child, indent + 1);
					os << std::endl;
				}
				os << indent << "}";
			}
		}

		void ConfigNodeSerializer::write(ConfigNodeSerializer::ostream_type &os,
		                                 const ConfigNodeSerializer::value_type &from) {
			dump(os, &from);
		}

		ConfigFile::ConfigFile()
				: Resource(), ConfigNode() {}

		ConfigFile::ConfigFile(ResourceFactory *factory, const String &name, const String &path,
		                       const ResourceType &type)
				: Resource(factory, name, path, type == ResourceType::Unknown ? ResourceType::Config : type)
				, ConfigNode()
		{}

		void ConfigFile::setName(const String &name) {
			Resource::setName(name);
		}
	}
}