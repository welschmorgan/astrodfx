//
// Created by darkboss on 9/12/20.
//

#ifndef QUASARFX_JSONGENERATOR_H
#define QUASARFX_JSONGENERATOR_H

#include <core/Generator.h>
#include <core/Config.h>

namespace quasar {
	namespace formats {
		class JsonGenerator: public core::BasicGenerator<Char, core::ConfigNode> {
		public:
			JsonGenerator() = default;
			JsonGenerator(const JsonGenerator &rhs) = delete;
			virtual ~JsonGenerator() = default;

			JsonGenerator       &operator=(const JsonGenerator &rhs) = delete;

			void                generate(const core::ConfigNode &item, stream_type &to) override {
				_generate(&item, to);
			}

		protected:
			void                _generate(const core::ConfigNode *node, stream_type &to, int indent = 0) {
				string_type     indentStr(indent, '\t');
				to << indentStr;
				if (!node->getName().empty()) {
					to << node->getName() << " ";
				}
				to << "{" << std::endl;
				for (auto const&prop: node->getProperties()) {
					to << indentStr + "\t" + prop.first << " = " << prop.second << std::endl;
				}
				for (auto const&child: node->getChildren()) {
					_generate(&child, to, indent + 1);
				}
				to << indentStr << "}" << std::endl;
			}
		};
	}
}


#endif //QUASARFX_JSONGENERATOR_H
