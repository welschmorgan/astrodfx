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

			using child_iter_type       = typename child_store_type::iter_type;
			using child_citer_type      = typename child_store_type::citer_type;
			using child_riter_type      = typename child_store_type::riter_type;
			using child_criter_type     = typename child_store_type::criter_type;

		protected:
			ConfigNode                  *mParent;
			child_store_type            mChildren;
			prop_store_type             mProps;
			String                      mName;
			String                      mValue;

		public:
			ConfigNode(ConfigNode *parent = nullptr, const String &name = String());
			ConfigNode(const ConfigNode &rhs);
			virtual ~ConfigNode() noexcept = default;

			ConfigNode                  &operator=(const ConfigNode &rhs);

			const String                &getName() const noexcept;
			void                        setName(const String &name) noexcept;

			template<typename T = String>
			T                           getValue() const noexcept;

			template<typename T = String>
			void                        setValue(const T &value) noexcept;

			const ConfigNode            *getParent() const noexcept;
			ConfigNode                  *getParent() noexcept;
			void                        setParent(ConfigNode *parent);

			ConfigNode                  *createChild(const String &name);
			bool                        hasChildren() const;
			const ConfigNode            *getFirstChild() const;
			ConfigNode                  *getFirstChild();
			const ConfigNode            *getLastChild() const;
			ConfigNode                  *getLastChild();
			const child_store_type      &getChildren() const noexcept;
			child_store_type            &getChildren() noexcept;
			child_iter_type             findChild(const String &name);
			child_citer_type            findChild(const String &name) const;
			child_riter_type            rfindChild(const String &name);
			child_criter_type           rfindChild(const String &name) const;
			const ConfigNode            *getChild(const String &name, bool except = true) const  noexcept(false);
			ConfigNode                  *getChild(const String &name, bool except = true)  noexcept(false);
			bool                        hasChild(const String &name) noexcept;
			bool                        removeChild(const String &name, ConfigNode *out = nullptr);

			template<typename Type = String>
			ConfigNode                  &setProperty(const String &name, const Type value);
			const prop_store_type       &getProperties() const noexcept;
			prop_store_type             &getProperties() noexcept;
			template<typename Type = String>
			Type                        getProperty(const String &name, bool except = true, const Type defVal = Type()) const;
			bool                        hasProperty(const String &name) noexcept;
			bool                        removeProperty(const String &name, String *out = nullptr);

		protected:
			void                        acquireChild(ConfigNode &child);
		};

		template<typename Type>
		ConfigNode &ConfigNode::setProperty(const String &name, const Type value) {
			StringStream buf;
			buf << value;
			mProps.put(name, buf.str());
			return *this;
		}

		template<typename Type>
		Type                        ConfigNode::getProperty(const String &name, bool except, const Type defVal) const {
			auto prop = mProps->find(name);
			if (prop == mProps.end()) {
				if (except) {
					throw std::runtime_error("Unknown property '" + name + "' in config node '" + mName + "'");
				}
				return defVal;
			}
			StringStream buf;
			buf.str(prop->second);
			Type ret = Type();
			buf >> ret;
			return ret;
		}

		class ConfigFile
			: public Resource
			, public ConfigNode
		{
		public:
			using store_type    = Map<String, String>;

		public:
			ConfigFile();
			ConfigFile(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type = ResourceType::Unknown, const PropertyMap &props = PropertyMap(), const SharedIOStream &stream = SharedIOStream());
			ConfigFile(const Resource &rhs) = delete;
			virtual ~ConfigFile() noexcept = default;

			ConfigFile          &operator=(const ConfigFile &rhs) = delete;
			ConfigFile          &operator=(const ConfigNode &rhs) {
				ConfigNode::operator=(rhs);
				return *this;
			}

			void                setName(const String &name) noexcept;
			const String        &getName() const noexcept;
		};
	}
}


#endif //QUASARFX_CORE_CONFIG_H
