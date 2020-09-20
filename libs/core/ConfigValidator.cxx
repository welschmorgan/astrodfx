//
// Created by darkboss on 9/20/20.
//

#include "ConfigValidator.h"

namespace quasar {
	namespace core {
		ConfigValidator::ConfigValidator(const ConfigNode &schema)
			: mSchema(schema) {}

		ConfigValidator::ConfigValidator(const ConfigValidator &rhs)
				: mSchema() { *this = rhs; }

		ConfigValidator::~ConfigValidator() noexcept {}

		ConfigValidator &ConfigValidator::operator=(const ConfigValidator &rhs) {
			mSchema = rhs.mSchema;
			return *this;
		}

		void ConfigValidator::validate(const ConfigNode *values, unsigned int flags) noexcept(false) {
			validateNode(values, &mSchema, flags);
		}

		void ConfigValidator::validateNode(const ConfigNode *values, const ConfigNode *schema, unsigned int flags) noexcept(false) {
			if (flags & CVF_VALIDATE_NAME) {
				// invalid node name ?
				if (values->getName() != schema->getName()) {
					throwInvalidNameException(values->getName(), schema->getName());
				}
			}
			if (flags & CVF_VALIDATE_PROPS) {
				// property found in schema but not in user node ?
				for (auto const &schemaValue: schema->getProperties()) {
					if (!values->hasDirectProperty(schemaValue.first)) {
						throwMissingPropertyException(values->getName(), schemaValue.first);
					}
				}
				if (flags & CVF_VALIDATE_STRICT) {
					// property not found in schema but in user node ?
					for (auto const &userValue: values->getProperties()) {
						if (!schema->hasDirectProperty(userValue.first)) {
							throwUnknownPropertyException(values->getName(), userValue.first);
						}
					}
				}
			}

			if (flags & CVF_VALIDATE_VALUE) {
				// values differ ?
				if (schema->getValue() != values->getValue()) {
					throwDifferentValuesException(values->getName(), values->getValue(), schema->getValue());
				}
			}

			if (flags & CVF_VALIDATE_CHILDREN) {
				// child found in schema but not in user node ?
				for (auto const &schemaChild: schema->getChildren()) {
					auto child = values->getDirectChild(schemaChild.getName(), false);
					if (!child) {
						throwMissingChildException(values->getName(), schemaChild.getName(), schemaChild.getChildrenNames());
					}
					validateNode(child, &schemaChild, flags);
				}
				if (flags & CVF_VALIDATE_STRICT) {
					// child found in user node but not in schema ?
					for (auto const &child: values->getChildren()) {
						auto schemaChild = schema->getDirectChild(child.getName(), false);
						if (!schemaChild) {
							throwUnknownChildException(values->getName(), schemaChild->getName(),
							                           schemaChild->getChildrenNames());
						}
						validateNode(&child, schemaChild, flags);
					}
				}
			}
		}

		void ConfigValidator::throwMissingPropertyException(const String &nodeName, const String &propName) noexcept(false) {
			throw std::runtime_error("missing property '" + propName + "' for ConfigNode '" + nodeName + "'");
		}

		void ConfigValidator::throwUnknownPropertyException(const String &nodeName, const String &propName) noexcept(false) {
			throw std::runtime_error("unknown property '" + propName + "' for ConfigNode '" + nodeName + "'");
		}

		void ConfigValidator::throwDifferentValuesException(const String &nodeName, const String &userValue,
		                                                    const String &schemaValue) noexcept(false) {
			throw std::runtime_error("value (" + userValue + ") differs from schema one (" + schemaValue + ") for ConfigNode '" + nodeName + "'");
		}

		void ConfigValidator::throwInvalidNameException(const String &actualNodeName, const String &expectedNodeName) noexcept(false) {
			throw std::runtime_error("invalid name '" + actualNodeName + " for ConfigNode '" + expectedNodeName + "'");
		}

		void ConfigValidator::throwUnknownChildException(const String &parentNodeName, const String &childNodeName, const Vector<String> &allowedNodeNames) {
			String allowedNodeNamesStr = allowedNodeNames.fold<String>([](String carry, const String &name) noexcept(false) {
				if (!carry.empty()) {
					carry += ", ";
				}
				return carry += name;
			}, String());
			throw std::runtime_error("unknown child '" + childNodeName + "' for ConfigNode '" + parentNodeName + "', allowed values are: " + allowedNodeNamesStr);
		}


		void ConfigValidator::throwMissingChildException(const String &parentNodeName, const String &childNodeName, const Vector<String> &allowedNodeNames) noexcept(false) {
			String allowedNodeNamesStr = allowedNodeNames.fold<String>([](String carry, const String &name) {
				if (!carry.empty()) {
					carry += ", ";
				}
				return carry += name;
			}, String());
			throw std::runtime_error("missing child '" + childNodeName + "' for ConfigNode '" + parentNodeName + "', allowed values are: " + allowedNodeNamesStr);
		}

	}
}