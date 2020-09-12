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
			const ConfigNode            *getChild(const String &name) const noexcept;
			ConfigNode                  *getChild(const String &name) noexcept;
			bool                        hasChild(const String &name) noexcept;
			bool                        removeChild(const String &name, ConfigNode *out = nullptr);

			ConfigNode                  &setProperty(const String &name, const String &value);
			const prop_store_type       &getProperties() const noexcept;
			prop_store_type             &getProperties() noexcept;
			const String                &getProperty(const String &name) const;
			String                      &getProperty(const String &name);
			bool                        hasProperty(const String &name) noexcept;
			bool                        removeProperty(const String &name, String *out = nullptr);

		protected:
			void                        acquireChild(ConfigNode &child);
		};

		class ConfigNodeSerializer: public OSerializer<ConfigNode> {
		public:
			using base_type             = OSerializer<ConfigNode>;
			using value_type            = typename base_type::value_type;
			using ostream_type          = typename base_type::ostream_type;

		public:
			ConfigNodeSerializer() = default;
			ConfigNodeSerializer(const ConfigNodeSerializer &rhs) = default;
			~ConfigNodeSerializer() noexcept = default;

			ConfigNodeSerializer            &operator=(const ConfigNodeSerializer &rhs) = default;

			void                            dump(ostream_type &os, const value_type *node, int indent = 0);

			void                            write(ostream_type &os, const value_type &from) override;
		};

		class ConfigFile
			: public Resource
			, public ConfigNode
		{
		public:
			using store_type    = Map<String, String>;

		public:
			ConfigFile();
			ConfigFile(ResourceFactory *factory, const String &name, const String &path, const ResourceType &type = ResourceType::Unknown);
			ConfigFile(const Resource &rhs) = delete;
			virtual ~ConfigFile() noexcept = default;

			ConfigFile          &operator=(const ConfigFile &rhs) = delete;

			void                setName(const String &name);
		};
	}
}


#endif //QUASARFX_CORE_CONFIG_H
