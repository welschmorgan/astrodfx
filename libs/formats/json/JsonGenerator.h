//
// Created by darkboss on 9/12/20.
//

#ifndef QUASARFX_JSONGENERATOR_H
#define QUASARFX_JSONGENERATOR_H

#include <core/Generator.h>
#include <core/Config.h>
#include <locale>

namespace quasar {
	namespace formats {
		class JsonGenerator: public core::BasicGenerator<Char, core::ConfigNode> {
		public:
			JsonGenerator(): BasicGenerator("JSON", "1.0") {}
			JsonGenerator(const JsonGenerator &rhs) = delete;
			virtual ~JsonGenerator() = default;

			JsonGenerator       &operator=(const JsonGenerator &rhs) = delete;

			void                generate(const core::ConfigNode &item, stream_type &to) override {
				_generate(&item, &item, to);
			}

		protected:
			void                _generate(const core::ConfigNode *root, const core::ConfigNode *node, stream_type &to, int indent = 0) {
				string_type     indentStr(indent, '\t');
				std::locale     locale;
				auto isnumber = [&](const string_type &str) -> bool {
					for (auto const& ch: str) {
						if (!std::isdigit(ch, locale)) {
							return false;
						}
					}
					return true;
				};
				to << indentStr;
				if (node != root && !node->getName().empty()) {
					to << "\"" << node->getName() << "\": ";
				}
				to << "{";
				for (auto prop = node->getProperties().begin(); prop != node->getProperties().end(); prop++) {
					if (prop != node->getProperties().begin()) {
						to << ",";
					}
					to << std::endl;
					to << indentStr + "\t\"" + prop->first << "\": ";
					if (isnumber(prop->second)) {
						to << prop->second;
					} else {
						to << "\"" << prop->second << "\"";
					}
				}
				for (auto child = node->getChildren().begin(); child != node->getChildren().end(); child++) {
					if (child != node->getChildren().begin() || !node->getProperties().empty()) {
						to << ",";
					}
					to << std::endl;
					_generate(root, &*child, to, indent + 1);
				}
				to << std::endl;
				to << indentStr << "}";
			}
		};
	}
}


#endif //QUASARFX_JSONGENERATOR_H
