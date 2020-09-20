//
// Created by darkboss on 9/20/20.
//

#ifndef QUASARFX_CONFIGVALIDATOR_H
#define QUASARFX_CONFIGVALIDATOR_H

#include "Config.h"
#include "ConfigValidatorFlags.h"

namespace quasar {
	namespace core {
		/**
		 * Validate a ConfigNode using another ConfigNode that serves as schema.
		 * It checks:
		 *  - properties
		 *  - children
		 *  - name
		 *  - value
		 *
		 *  It works both ways:
		 *   - When in loose mode, it reports keys defined in schema but not in supplied values.
		 *   - And when in strict mode, it also reports keys defined in supplied values but not in schema.
		 */
		class ConfigValidator {
		public:
			/**
			 * Default validation flags
			 *
			 * @see ConfigValidatorFlags
			 */
			static const unsigned   DefaultFlags = CVF_VALIDATE_ALL_STRICT;

		protected:
			ConfigNode              mSchema;

		public:
			/**
			 * Construct the validator object.
			 *
			 * @param schema		An optional schema (@see ConfigValidator::setSchema)
			 */
			explicit ConfigValidator(const ConfigNode &schema = ConfigNode());

			/**
			 * Copy constructor
			 *
			 * @param rhs 		Object to copy
			 */
			ConfigValidator(const ConfigValidator &rhs);

			/**
			 * Destructor
			 */
			virtual ~ConfigValidator() noexcept;

			/**
			 * Assignment operator
			 *
			 * @param rhs			Object to copy
			 *
			 * @return				Clone of the object to be copied
			 */
			ConfigValidator         &operator=(const ConfigValidator &rhs);

			/**
			 * Return the stored schema
			 */
			const ConfigNode        &getSchema() const noexcept { return mSchema; }

			/**
			 * Store the given schema
			 *
			 * @param schema 		ConfigNode to be stored as schema
			 */
			void                    setSchema(const ConfigNode &schema) noexcept { mSchema = schema; }

			/**
			 * Validate the supplied ConfigNode using the stored schema
			 *
			 * @param values		ConfigNode to validate
			 * @param flags 		Validation options (@see ConfigValidatorFlags)
			 *
			 * @throws std::runtime_error 	If validation failed.
			 */
			virtual void            validate(const ConfigNode *values, unsigned int flags = DefaultFlags) noexcept(false);

		protected:
			/**
			 * Actual validator implementation, recursively validate config nodes
			 *
			 * @param values		ConfigNode to validate
			 * @param schema		Schema to validate it against
			 * @param flags			Validation options
			 *
			 * @throws	std::runtime_error	If validation failed
			 */
			static void             validateNode(const ConfigNode *values, const ConfigNode *schema, unsigned int flags) noexcept(false);

			/**
			 * Throw an error relating to a property defined in the schema but missing in the current node
			 *
			 * @param nodeName 		Name of the node
			 * @param propName 		Name of the missing property
			 *
			 * @throws std::runtime_error
			 */
			static void             throwMissingPropertyException(const String &nodeName, const String &propName) noexcept(false);

			/**
			 * Throw an error relating to a property defined in the current node but missing in the schema
			 *
			 * @param nodeName 		Name of the node
			 * @param propName 		Name of the missing property
			 *
			 * @throws std::runtime_error
			 */
			static void             throwUnknownPropertyException(const String &nodeName, const String &propName) noexcept(false);

			/**
			 * Throw an error relating to current node and schema having different values
			 *
			 * @param nodeName 		Name of the node
			 * @param userValue		Value stored in current node
			 * @param schemaValue	Value stored in schema
			 *
			 * @throws std::runtime_error
			 */
			static void             throwDifferentValuesException(const String &nodeName, const String &userValue,
			                                                      const String &schemaValue) noexcept(false);

			/**
			 * Throw an error relating to current node and schema having different names
			 *
			 * @param actualNodeName	Name of the node that's incorrect
			 * @param expectedNodeName	Name of the node that's expected
			 *
			 * @throws std::runtime_error
			 */
			static void             throwInvalidNameException(const String &actualNodeName, const String &expectedNodeName) noexcept(false);

			/**
			 * Throw an error relating to a child in the current node that's not in the schema
			 *
			 * @param parentNodeName	Name of the current node's parent
			 * @param childNodeName		Name of the current node's child
			 * @param allowedNodeNames	List of names that's allowed in the current node's parent
			 *
			 * @throws std::runtime_error
			 */
			static void             throwUnknownChildException(const String &parentNodeName, const String &childNodeName, const Vector<String> &allowedNodeNames) noexcept(false);

			/**
			 * Throw an error relating to a child in the schema that's not in the current node
			 *
			 * @param parentNodeName	Name of the current node's parent
			 * @param childNodeName		Name of the current node's child
			 * @param allowedNodeNames	List of names that's allowed in the current node's parent
			 *
			 * @throws std::runtime_error
			 */
			static void             throwMissingChildException(const String &parentNodeName, const String &childNodeName, const Vector<String> &allowedNodeNames) noexcept(false);
		};
	}
}

#endif //QUASARFX_CONFIGVALIDATOR_H
