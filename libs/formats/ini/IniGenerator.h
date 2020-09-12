//
// Created by darkboss on 9/6/20.
//

#ifndef QUASARFX_INIGENERATOR_H
#define QUASARFX_INIGENERATOR_H

# include <core/Generator.h>
# include <core/Config.h>

namespace quasar {
	namespace formats {
		class IniGenerator: public core::BasicGenerator<Char, core::ConfigNode> {
		public:
			using char_type = Char;
			using value_type = core::ConfigNode;
			using base_type = core::BasicGenerator<Char, core::ConfigNode>;
			using string_type = typename base_type::string_type;
			using stream_type = typename base_type::stream_type;

			IniGenerator() = default;
			IniGenerator(const IniGenerator &rhs) = default;
			virtual                 ~IniGenerator() = default;

			IniGenerator                &operator=(const IniGenerator &rhs) = default;

			string_type                 generate(const value_type &from) override {
				return base_type::generate(from);
			}
			void                        generate(const value_type &from, stream_type &to) override {
				_generate(&from, &from, to);
			}

		protected:
			void                        _generate(const value_type *root, const value_type *node, stream_type &to) {
				if (node != root && node != root->getFirstChild()) {
					to << std::endl;
				}
				if (!node->getName().empty()) {
					to << "[" << node->getName() << "]" << std::endl;
				}
				for (auto prop = node->getProperties().begin(); prop != node->getProperties().end(); prop++) {
					if (prop != node->getProperties().begin()) {
						to << std::endl;
					}
					to << prop->first << " = " << prop->second;
				}
				for (auto child = node->getChildren().begin(); child != node->getChildren().end(); child++) {
					_generate(root, &*child, to);
				}
			}
		};
	}
}

#endif //QUASARFX_INIGENERATOR_H
