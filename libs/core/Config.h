//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_CORE_CONFIG_H
#define QUASARFX_CORE_CONFIG_H

#include "Resource.h"
#include "Serializer.h"
#include "ConfigValidatorFlags.h"

namespace quasar {
	namespace core {
		class ConfigNode;

		/**
		 * Represent the flags used to walk a config tree using dot notation.
		 */
		enum DotAccessFlags {
			/** Create nodes while walking the tree */
			DAF_CREATE_NODES = 1 << 1,

			/** If set access a property, otherwise a child */
			DAF_NEED_PROPERTY = 1 << 2
		};

		/**
		 * Allow dot notation on ConfigNode.
		 */
		struct DotAccess {
			unsigned int    flags;
			String          path;
			Vector<String>  parts;
			ConfigNode      *root;
			ConfigNode      *iter;

			ConfigNode      *child;
			String          propertyName;
			String          *property;

			/**
			 * Construct the object
			 *
			 * @param root_ 	The root node from which we started walking
			 * @param path_ 	The full path of the accessed property / child
			 * @param flags_ 	Walking flags (@See DotAccessFlags)
			 */
			DotAccess(ConfigNode *root_, const String &path_, unsigned int flags_ = 0);

			/**
			 * Walk the dotted path, accessing child and properties.
			 *
			 * @return	This instance
			 */
			DotAccess       &walk();
		};

		/**
		 * Allow dot notation on const ConfigNode.
		 */
		struct ConstDotAccess {
			unsigned int        flags;
			String              path;
			Vector<String>      parts;
			const ConfigNode    *root;
			const ConfigNode    *iter;

			const ConfigNode    *child;
			String              propertyName;
			const String        *property;

			/**
			 * Construct the object
			 *
			 * @param root_ 	The root node from which we started walking
			 * @param path_ 	The full path of the accessed property / child
			 * @param flags_ 	Walking flags (@See DotAccessFlags)
			 */
			ConstDotAccess(const ConfigNode *root_, const String &path_, unsigned int flags_ = 0);

			/**
			 * Walk the dotted path, accessing child and properties.
			 *
			 * @return	This instance
			 */
			ConstDotAccess  &walk();
		};

		/**
		 * Represent a configuration node. It holds name, value, children, and properties.
		 */
		class ConfigNode {
		public:
			/** Children storage */
			using child_store_type = Vector<ConfigNode>;
			using child_iter_type       = typename child_store_type::iter_type;
			using child_citer_type      = typename child_store_type::citer_type;
			using child_riter_type      = typename child_store_type::riter_type;
			using child_criter_type     = typename child_store_type::criter_type;

			/** Property storage */
			using prop_store_type = Map<String, String>;
			using prop_iter_type        = typename prop_store_type::iter_type;
			using prop_citer_type       = typename prop_store_type::citer_type;
			using prop_riter_type       = typename prop_store_type::riter_type;
			using prop_criter_type      = typename prop_store_type::criter_type;

		protected:
			const ConfigNode            *mSchema;
			ConfigNode                  *mParent;
			child_store_type            mChildren;
			prop_store_type             mProps;
			String                      mName;
			String                      mValue;

		public:
			/**
			 * Construct the object
			 *
			 * @param parent		Parent node
			 * @param name 			Name of this node
			 * @param children 		Children of this node
			 * @param props 		Properties of this node
			 * @param value 		Value of this node
			 */
			ConfigNode(ConfigNode *parent = nullptr,
					   const String &name = String(),
					   const child_store_type &children = child_store_type(),
					   const prop_store_type &props = prop_store_type(),
					   const String &value = String());
			/** Construct the object by copying another */
			ConfigNode(const ConfigNode &rhs);
			/** Destruct the object */
			virtual ~ConfigNode() noexcept = default;

			/** Assign a new value to the object */
			ConfigNode                  &operator=(const ConfigNode &rhs);

			/** Return the name of this node */
			const String                &getName() const noexcept;
			/** Define the name of this node */
			void                        setName(const String &name) noexcept;

			/** Return the optional schema for validation */
			const ConfigNode            *getSchema() const noexcept;
			/** Define the optional schema for validation */
			void                        setSchema(const ConfigNode *v) noexcept;

			/** Validate this node against the stored schema if any. @see ConfigValidator::validate */
			void                        validate(unsigned int flags = CVF_VALIDATE_ALL_STRICT) noexcept(false);

			/** Return true this node has no children, no properties and no values. */
			bool                        empty() const noexcept;

			/** Return the direct children names as an array */
			Vector<String>              getDirectChildrenNames() const noexcept;

			/** Return the direct property names as an array */
			Vector<String>              getDirectPropertyNames() const noexcept;

			/** Return the children names as an array */
			Vector<String>              getChildrenNames() const noexcept;

			/** Return the property names as an array */
			Vector<String>              getPropertyNames() const noexcept;

			/** Return the property name/value pairs as a map */
			Map<String, String>         getPropertyNameValuePairs() const noexcept;

			/** Return the stored value converted to the given type
			 *
			 * @tparam T	The type to convert the stored value to
			 *
			 * @return		The converted value
			 *
			 * @throws std::runtime_error 	If conversion failed
			 */
			template<typename T = String>
			T                           getValue() const noexcept(false);

			/**
			 * Define the stored value
			 *
			 * @note Converted to string internally
			 *
			 * @tparam T				Type of the value to be converted
			 * @param value				Value to be stored
			 *
			 */
			template<typename T = String>
			void                        setValue(const T &value) noexcept;

			/**
			 * Compute the full path of this node, aggregating all ancestors name joined by '.'.
			 *
			 * @see						getAncestors()
			 *
			 * @return					The dot-path of this object.
			 */
			String                      getPath() const;

			/**
			 * Return the ancestry chain starting by the oldest ancestor.
			 *
			 * @return					The ancestors.
			 */
			Vector<ConfigNode*>         getAncestors();

			/**
			 * Return the const ancestry chain starting by the oldest ancestor.
			 *
			 * @return					The ancestors.
			 */
			Vector<const ConfigNode*>   getAncestors() const;

			/** Return the direct parent **/
			ConfigNode                  *getParent() noexcept;
			/** Define the direct parent **/
			void                        setParent(ConfigNode *parent);
			/** Return the direct parent **/
			const ConfigNode            *getParent() const noexcept;

			/**
			 * Create a direct child in this node
			 *
			 * @param name				Name of the new child
			 *
			 * @return					The newly created child
			 */
			ConfigNode                  *createChild(const String &name);

			/**
			 * Register a node as new child
			 *
			 * @throws std::runtime_error If a node already exist with the given name.
			 *
			 * @param n					New node to be added to this node
			 *
			 * @return					The new child node.
			 */
			ConfigNode                  *addChild(const ConfigNode &n);

			/** Return true if the number of child is greater than zero */
			bool                        hasChildren() const;
			/** Return the first child node if any */
			const ConfigNode            *getFirstChild() const;
			/** Return the first child node if any */
			ConfigNode                  *getFirstChild();
			/** Return the last child node if any */
			const ConfigNode            *getLastChild() const;
			/** Return the last child node if any */
			ConfigNode                  *getLastChild();

			/** Return all children stored in this node */
			const child_store_type      &getChildren() const noexcept;
			/** Return all children stored in this node */
			child_store_type            &getChildren() noexcept;

			/**
			 * Find a child by it's name
			 *
			 * @param name				Name of the child to be found
			 *
			 * @return					An iterator different than getChildren().end()
			 */
			child_iter_type             findChild(const String &name);

			/**
			 * Find a child by it's name
			 *
			 * @param name				Name of the child to be found
			 *
			 * @return					An iterator different than getChildren().end()
			 */
			child_citer_type            findChild(const String &name) const;

			/**
			 * Find a child by it's name in reverse order
			 *
			 * @param name				Name of the child to be found
			 *
			 * @return					An iterator different than getChildren().end()
			 */
			child_riter_type            rfindChild(const String &name);

			/**
			 * Find a child by it's name in reverse order
			 *
			 * @param name				Name of the child to be found
			 *
			 * @return					An iterator different than getChildren().end()
			 */
			child_criter_type           rfindChild(const String &name) const;

			/**
			 * Update or create a child.
			 *
			 * @param name				Name of the child to be found / created
			 *
			 * @return					The newly created / updated child
			 */
			ConfigNode                  *setChild(const String &name, const ConfigNode &n) noexcept(false);

			/** Return a stored child by it's name */
			const ConfigNode            *getChild(const String &name, bool except = true) const  noexcept(false);
			/** Return a stored child by it's name */
			ConfigNode                  *getChild(const String &name, bool except = true)  noexcept(false);
			/** Check if a child has already been stored by name */
			bool                        hasChild(const String &name) const noexcept;

			/**
			 * Remove a child by name
			 *
			 * @param name				Name of the child to be removed
			 * @param out				If supplied, will old the removed child value
			 *
			 * @return 					True if successfully removed, false otherwise
			 */
			bool                        removeChild(const String &name, ConfigNode *out = nullptr);

			/**
			 * Add a direct new child in this node
			 *
			 * @throws std::runtime_error If a node already exists with this name
			 *
			 * @param n					The new node to be added
			 *
			 * @return 					The new node's instance
			 */
			ConfigNode                  *addDirectChild(const ConfigNode &n);

			/**
			 * Find a direct child by it's name
			 *
			 * @param name				Name of the child to be found
			 *
			 * @return					An iterator different than getChildren().end()
			 */
			child_iter_type             findDirectChild(const String &name);

			/**
			 * Find a direct child by it's name
			 *
			 * @param name				Name of the child to be found
			 *
			 * @return					An iterator different than getChildren().end()
			 */
			child_citer_type            findDirectChild(const String &name) const;

			/**
			 * Find a direct child by it's name in reverse order
			 *
			 * @param name				Name of the child to be found
			 *
			 * @return					An iterator different than getChildren().end()
			 */
			child_riter_type            rfindDirectChild(const String &name);

			/**
			 * Find a direct child by it's name in reverse order
			 *
			 * @param name				Name of the child to be found
			 *
			 * @return					An iterator different than getChildren().end()
			 */
			child_criter_type           rfindDirectChild(const String &name) const;

			/**
			 * Create or update a direct child
			 *
			 * @param name				Name of the child to be created / updated
			 * @param n					New value for the config node to be created / updated
			 *
			 * @return					The direct child's value
			 */
			ConfigNode                  *setDirectChild(const String &name, const ConfigNode &n) noexcept(false);

			/**
			 * Return a direct child by it's name
			 *
			 * @param name 		Name of the direct child to be found
			 * @param except	Throw an exception if not found ?
			 *
			 * @throws std::runtime_error	If no child with this name exist and except = true
			 *
			 * @return			The found direct child that was found or nullptr
			 */
			const ConfigNode            *getDirectChild(const String &name, bool except = true) const  noexcept(false);

			/**
			 * Return a direct child by it's name
			 *
			 * @param name 		Name of the direct child to be found
			 * @param except	Throw an exception if not found ?
			 *
			 * @throws std::runtime_error	If no child with this name exists and except = true
			 *
			 * @return			The found direct child that was found or nullptr
			 */
			ConfigNode                  *getDirectChild(const String &name, bool except = true)  noexcept(false);

			/** Check if a direct child exists in this node */
			bool                        hasDirectChild(const String &name) const noexcept;
			/** Remove an existing direct child by it's name */
			bool                        removeDirectChild(const String &name, ConfigNode *out = nullptr);

			/**
			 * Create or update a property in this node
			 *
			 * @tparam Type		Type of the value (converted to string for storage)
			 *
			 * @param name		Name of the property to be created / updated
			 * @param value 	The property's new value
			 *
			 * @return 			This instance
			 */
			template<typename Type = String>
			ConfigNode                  &setProperty(const String &name, const Type value);

			/** Check if this node has any property at all */
			bool                        hasProperties() const;
			/** Return all properties held in this node */
			const prop_store_type       &getProperties() const noexcept;
			/** Return all properties held in this node */
			prop_store_type             &getProperties() noexcept;

			/**
			 * Find a property by it's name
			 *
			 * @note Dot notation is allowed
			 *
			 * @param name	Name of the property to be found
			 *
			 * @return		An iterator to this property.
			 */
			prop_iter_type              findProperty(const String &name);

			/**
			 * Find a const property by it's name
			 *
			 * @note 		Dot notation is allowed
			 *
			 * @param name	Name of the property to be found
			 *
			 * @return		An iterator to this property.
			 */
			prop_citer_type             findProperty(const String &name) const;

			/**
			 * Return an existing property by it's name
			 *
			 * @note 							Dot notation is allowed
			 * @throws std::runtime_error		If the property wasn't found and except is true
			 *
			 * @param name						Name of the property to be found
			 * @param except					Throws an exception if the property wasn't found
			 * @param defVal					The default value returned if except is false
			 *
			 * @return							If found the property value converted to the desired type, otherwise the supplied default value if except is false
			 */
			template<typename Type = String>
			Type                        getProperty(const String &name, bool except = true, const Type defVal = Type()) const;

			/** Check if a property exist by name */
			bool                        hasProperty(const String &name) const noexcept;

			/**
			 * Remove a property by name
			 *
			 * @param name				Name of the property to be found
			 * @param out 				If found and non-null, store the property value before removing it
			 *
			 * @return 					True if found, false otherwise
			 */
			bool                        removeProperty(const String &name, String *out = nullptr);

			/**
			 * Create or update a direct property of this node
			 *
			 * @tparam Type				Type of the new value to be converted to string before storage
			 *
			 * @param name 				Name of the property to be found
			 * @param value				Value to be updated or created
			 *
			 * @return					This instance
			 */
			template<typename Type = String>
			ConfigNode                  &setDirectProperty(const String &name, const Type value);

			/**
			 * Retrieve a direct property of this node
			 *
			 * @tparam Type				Type of the value to be converted to before returning it
			 *
			 * @param name 				Name of the property to be found
			 * @param except			Throws an exception if the property wasn't found
			 * @param defVal			Default value to return when not found
			 *
			 * @return					The found property's value
			 */
			template<typename Type = String>
			Type                        getDirectProperty(const String &name, bool except = true, const Type defVal = Type()) const;

			/** Check if a direct property exists with this name */
			bool                        hasDirectProperty(const String &name) const noexcept;

			/**
			 * Remove a direct property by it's name
			 *
			 * @param name				Name of the property to be found
			 * @param out 				If non-null and property is found, store the property's value before removing it
			 *
			 * @return 					True if successfully removed, false otherwise
			 */
			bool                        removeDirectProperty(const String &name, String *out = nullptr);

			/**
			 * Merge this node with another one without modifying the current instance.
			 *
			 * @param with				The object to merge it with
			 *
			 * @return					The object resulting from the merge operation.
			 */
			ConfigNode                  merged(const ConfigNode &with) const;

			/**
			 * Merge this node with another one without creating copies (modifies this instance).
			 *
			 * @param with				The object to merge it with
			 *
			 * @return					The object resulting from the merge operation.
			 */
			ConfigNode                  &merge(const ConfigNode &with);


		protected:
			/** Update parent when adding nodes */
			void                        acquireChild(ConfigNode &child);

			/** DotAccessor is friendly */
			friend DotAccess;

			/** ConstDotAccessor is friendly */
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

		/**
		 * Represent the resource counterpart of a config node.
		 * It allows all config files to have the same internal representation.
		 *
		 * This is the class the end-user will manipulate.
		 */
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
