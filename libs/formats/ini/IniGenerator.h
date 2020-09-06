//
// Created by darkboss on 9/6/20.
//

#ifndef QUASARFX_INIGENERATOR_H
#define QUASARFX_INIGENERATOR_H

# include <core/Generator.h>
#include "IniFile.h"

namespace quasar {
	namespace formats {
		template<typename CharT>
		class BasicIniGenerator: public core::BasicGenerator<CharT, BasicIniFile<CharT>> {
		public:
			using base_type = core::BasicGenerator<CharT, BasicIniFile<CharT>>;
			using char_type = CharT;
			using value_type = BasicIniFile<CharT>;
			using string_type = typename base_type::string_type;
			using stream_type = typename base_type::stream_type;

			BasicIniGenerator() = default;
			BasicIniGenerator(const BasicIniGenerator &rhs) = default;
			virtual                 ~BasicIniGenerator() = default;

			BasicIniGenerator            &operator=(const BasicIniGenerator &rhs) = default;

			string_type                 generate(const value_type &from) override {
				return base_type::generate(from);
			}
			void                        generate(const value_type &from, stream_type &to) override {
				value_type dup(from);
				bool prelude = false;
				if (dup.defaultSection && !dup.defaultSection->values.empty()) {
					prelude = true;
					if (!dup.defaultSection->name.empty()) {
						to << "[" << dup.defaultSection->name << "]" << std::endl;
					}
					for (auto prop = dup.defaultSection->values.begin(); prop != dup.defaultSection->values.end(); prop++) {
						to << prop->first << " = " << prop->second << std::endl;
					}
				}
				if (dup.defaultSection) {
					auto foundDefault = dup.findSection(dup.defaultSection->name);
					dup.sections.erase(foundDefault);
				}
				for (auto section = dup.sections.cbegin(); section != dup.sections.cend(); section++) {
					if (prelude) {
						to << std::endl;
					}
					if (!section->name.empty()) {
						to << "[" << section->name << "]" << std::endl;
					}
					for (auto prop = section->values.begin(); prop != section->values.end(); prop++) {
						to << prop->first << " = " << prop->second;
						if (section == --dup.sections.end()) {
							if (prop != --section->values.end()) {
								to << std::endl;
							}
						} else {
							to << std::endl;
						}
					}
				}
			}
		};

		extern template class BasicIniGenerator<char>;
		extern template class BasicIniGenerator<wchar_t>;

		using IniGenerator = BasicIniGenerator<Char>;
	}
}

#endif //QUASARFX_INIGENERATOR_H
