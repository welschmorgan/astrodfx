//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_CORE_CONFIG_H
#define QUASARFX_CORE_CONFIG_H

#include "Resource.h"
#include "Serializer.h"

namespace quasar {
	namespace core {
		class ConfigNode {
		public:
			using child_store_type = Vector<ConfigNode>;
			using prop_store_type = Map<String, String>;

		protected:
			ConfigNode          *mParent;
			child_store_type    mChildren;
			prop_store_type     mProps;
			String              mName;
			String              mValue;

		public:
			ConfigNode(ConfigNode *parent = nullptr, const String &name = String())
				: mParent(parent)
				, mChildren()
				, mProps()
				, mName(name)
				, mValue()
			{}
			ConfigNode(const ConfigNode &rhs) {
				*this = rhs;
			}
			virtual ~ConfigNode() noexcept = default;

			ConfigNode                  &operator=(const ConfigNode &rhs) {
				mParent = rhs.mParent;
				mChildren = rhs.mChildren;
				mProps = rhs.mProps;
				mName = rhs.mName;
				mValue = rhs.mValue;
				return *this;
			}

			const String                &getName() const noexcept { return mName; }
			void                        setName(const String &name) noexcept { mName = name; }

			template<typename T = String>
			T                           getValue() const noexcept { return mValue; }

			template<typename T = String>
			void                        setValue(const T &value) noexcept {
				StringStream ss;
				ss << value;
				mValue = ss.str();
			}

			const ConfigNode            *getParent() const noexcept { return mParent; }
			ConfigNode                  *getParent() noexcept { return mParent; }
			void                        setParent(ConfigNode *parent) { mParent = parent; }

			ConfigNode                  &createChild(const String &name) {
				ConfigNode              *child = getChild(name);
				if (!child) {
					mChildren.add(ConfigNode(this, name));
					child = &mChildren->back();
				}
				return *child;
			}
			const child_store_type      &getChildren() const noexcept { return mChildren; }
			child_store_type            &getChildren() noexcept { return mChildren; }
			const ConfigNode            *getChild(const String &name) const noexcept {
				auto it = mChildren.find([&](const ConfigNode &n) {
					return n.getName() == name;
				});
				if (it != mChildren.end()) {
					return &*it;
				}
				return nullptr;
			}
			ConfigNode                  *getChild(const String &name) noexcept {
				auto it = mChildren.find([&](const ConfigNode &n) {
					return n.getName() == name;
				});
				if (it != mChildren.end()) {
					return &*it;
				}
				return nullptr;
			}
			bool                        hasChild(const String &name) noexcept {
				return getChild(name) != nullptr;
			}
			bool                        removeChild(const String &name, ConfigNode *out = nullptr) {
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

			ConfigNode                  &setProperty(const String &name, const String &value) {
				mProps.put(name, value);
				return *this;
			}
			const prop_store_type       &getProperties() const noexcept { return mProps; }
			prop_store_type             &getProperties() noexcept { return mProps; }
			const String                &getProperty(const String &name) const {
				auto prop = mProps->find(name);
				if (prop == mProps.end()) {
					throw std::runtime_error("Unknown property '" + name + "' in config node '" + mName + "'");
				}
				return prop->second;
			}
			String                      &getProperty(const String &name) {
				auto prop = mProps->find(name);
				if (prop == mProps.end()) {
					throw std::runtime_error("Unknown property '" + name + "' in config node '" + mName + "'");
				}
				return prop->second;
			}
			bool                        hasProperty(const String &name) noexcept {
				auto prop = mProps->find(name);
				return prop != mProps.end();
			}
			bool                        removeProperty(const String &name, String *out = nullptr) {
				auto prop = mProps->find(name);
				if (prop == mProps.end()) {
					return false;
				}
				if (out) {
					*out = prop->second;
				}
				return true;
			}
		};

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

		class ConfigNodeSerializer: public OSerializer<ConfigNode> {
		public:
			using base_type                 = OSerializer<ConfigNode>;
			using value_type                = typename base_type::value_type;
			using ostream_type              = typename base_type::ostream_type;

		public:
			ConfigNodeSerializer() = default;
			ConfigNodeSerializer(const ConfigNodeSerializer &rhs) = default;
			~ConfigNodeSerializer() noexcept = default;

			ConfigNodeSerializer            &operator=(const ConfigNodeSerializer &rhs) = default;

			void                            dump(ostream_type &os, const value_type *node, int indent = 0) {
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

			void                            write(ostream_type &os, const value_type &from) override {
				dump(os, &from);
			}
		};

		class Config
			: public Resource
			, public ConfigNode
		{
		public:
			using store_type    = Map<String, String>;

		public:
			Config(): Resource(), ConfigNode() {}
			Config(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type = ResourceType::Unknown)
				: Resource(factory, name, path, type == ResourceType::Unknown ? ResourceType::Config : type)
				, ConfigNode()
			{}
			Config(const Resource &rhs) = delete;
			virtual ~Config() noexcept = default;

			Config              &operator=(const Config &rhs) = delete;
		};
	}
}


#endif //QUASARFX_CORE_CONFIG_H
