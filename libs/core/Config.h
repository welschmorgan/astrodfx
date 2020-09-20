//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_CORE_CONFIG_H
#define QUASARFX_CORE_CONFIG_H

#include "Resource.h"
#include "Serializer.h"

namespace quasar {
	namespace core {
		class ConfigNode;
		enum DotAccessFlags {
			DAF_CREATE_NODES,
			DAF_NEED_PROPERTY
		};

		struct DotAccess {
			unsigned int    flags;
			String          path;
			Vector<String>  parts;
			ConfigNode      *root;
			ConfigNode      *iter;

			ConfigNode      *child;
			String          propertyName;
			String          *property;

			DotAccess(ConfigNode *root_, const String &path_, unsigned int flags_ = 0);

			DotAccess       &walk();
		};

		struct ConstDotAccess {
			unsigned int        flags;
			String              path;
			Vector<String>      parts;
			const ConfigNode    *root;
			const ConfigNode    *iter;

			const ConfigNode    *child;
			String              propertyName;
			const String        *property;

			ConstDotAccess(const ConfigNode *root_, const String &path_, unsigned int flags_ = 0);

			ConstDotAccess  &walk();
		};

		class ConfigNode {
		public:
			using child_store_type = Vector<ConfigNode>;
			using child_iter_type       = typename child_store_type::iter_type;
			using child_citer_type      = typename child_store_type::citer_type;
			using child_riter_type      = typename child_store_type::riter_type;
			using child_criter_type     = typename child_store_type::criter_type;

			using prop_store_type = Map<String, String>;
			using prop_iter_type        = typename prop_store_type::iter_type;
			using prop_citer_type       = typename prop_store_type::citer_type;
			using prop_riter_type       = typename prop_store_type::riter_type;
			using prop_criter_type      = typename prop_store_type::criter_type;

		protected:
			ConfigNode                  *mParent;
			child_store_type            mChildren;
			prop_store_type             mProps;
			String                      mName;
			String                      mValue;

		public:
			ConfigNode(ConfigNode *parent = nullptr,
					   const String &name = String(),
					   const child_store_type &children = child_store_type(),
					   const prop_store_type &props = prop_store_type(),
					   const String &value = String());
			ConfigNode(const ConfigNode &rhs);
			virtual ~ConfigNode() noexcept = default;

			ConfigNode                  &operator=(const ConfigNode &rhs);

			const String                &getName() const noexcept;
			void                        setName(const String &name) noexcept;

			template<typename T = String>
			T                           getValue() const noexcept(false);
			String                      getPath() const;

			template<typename T = String>
			void                        setValue(const T &value) noexcept;

			const ConfigNode            *getParent() const noexcept;
			ConfigNode                  *getParent() noexcept;
			void                        setParent(ConfigNode *parent);

			ConfigNode                  *createChild(const String &name);
			ConfigNode                  *addChild(const ConfigNode &n);
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
			ConfigNode                  *setChild(const String &name, const ConfigNode &n) noexcept(false);
			const ConfigNode            *getChild(const String &name, bool except = true) const  noexcept(false);
			ConfigNode                  *getChild(const String &name, bool except = true)  noexcept(false);
			bool                        hasChild(const String &name) const noexcept;
			bool                        removeChild(const String &name, ConfigNode *out = nullptr);

			ConfigNode                  *addDirectChild(const ConfigNode &n);
			child_iter_type             findDirectChild(const String &name);
			child_citer_type            findDirectChild(const String &name) const;
			child_riter_type            rfindDirectChild(const String &name);
			child_criter_type           rfindDirectChild(const String &name) const;
			ConfigNode                  *setDirectChild(const String &name, const ConfigNode &n) noexcept(false);
			const ConfigNode            *getDirectChild(const String &name, bool except = true) const  noexcept(false);
			ConfigNode                  *getDirectChild(const String &name, bool except = true)  noexcept(false);
			bool                        hasDirectChild(const String &name) const noexcept;
			bool                        removeDirectChild(const String &name, ConfigNode *out = nullptr);

			template<typename Type = String>
			ConfigNode                  &setProperty(const String &name, const Type value);
			bool                        hasProperties() const;
			const prop_store_type       &getProperties() const noexcept;
			prop_store_type             &getProperties() noexcept;
			prop_iter_type              findProperty(const String &name);
			prop_citer_type             findProperty(const String &name) const;
			template<typename Type = String>
			Type                        getProperty(const String &name, bool except = true, const Type defVal = Type()) const;
			bool                        hasProperty(const String &name) const noexcept;
			bool                        removeProperty(const String &name, String *out = nullptr);
			template<typename Type = String>
			ConfigNode                  &setDirectProperty(const String &name, const Type value);

			template<typename Type = String>
			Type                        getDirectProperty(const String &name, bool except = true, const Type defVal = Type()) const;
			bool                        hasDirectProperty(const String &name) const noexcept;
			bool                        removeDirectProperty(const String &name, String *out = nullptr);

			ConfigNode                  merged(const ConfigNode &with) const;
			ConfigNode                  &merge(const ConfigNode &with);


		protected:
			void                        acquireChild(ConfigNode &child);

			friend DotAccess;
			friend ConstDotAccess;
		};

		template<typename Type>
		ConfigNode &ConfigNode::setProperty(const String &name, const Type value) {
			DotAccess access(this, name, DAF_CREATE_NODES | DAF_NEED_PROPERTY);
			access.walk();
			StringStream buf;
			buf << value;
			*access.property = buf.str();
			return *this;
		}

		template<typename Type>
		ConfigNode &ConfigNode::setDirectProperty(const String &name, const Type value) {
			StringStream buf;
			buf << value;
			mProps.put(name, buf.str());
			return *this;
		}

		template<typename Type>
		Type                        ConfigNode::getProperty(const String &name, bool except, const Type defVal) const {
			String prop;
			ConstDotAccess access(this, name, DAF_NEED_PROPERTY);
			access.walk();
			if (access.property == nullptr) {
				if (except) {
					throw std::runtime_error("unknown property '" + name + "' in config node '" + getPath() + "'");
				}
				return defVal;
			}
			auto value = *access.property;
			StringStream buf;
			buf.str(value);
			Type ret = Type();
			buf >> ret;
			return ret;
		}

		template<typename Type>
		Type                        ConfigNode::getDirectProperty(const String &name, bool except, const Type defVal) const {
			auto found = mProps->find(name);
			if (found == mProps.end()) {
				if (except) {
					throw std::runtime_error("unknown property '" + name + "' in config node '" + mName + "'");
				}
				return defVal;
			}
			StringStream buf;
			buf.str(found->second);
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
