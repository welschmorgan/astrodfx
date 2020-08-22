//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_INIFILE_H
#define QUASARFX_INIFILE_H

#include <core/String.h>

namespace quasar {
	namespace formats {
		struct IniSection {
			using store_type = std::map<core::String, core::String>;

			IniSection(const core::String &name_ = core::String()): name(name_), values() {}
			IniSection(const IniSection &rhs) = default;
			~IniSection() = default;

			IniSection             &operator=(const IniSection &rhs) = default;

			core::String        name;
			store_type          values;
		};

		struct IniFile {
			using store_type = std::list<IniSection>;

			core::String        name;
			store_type          sections;
			IniSection          *defaultSection;

			IniFile(const core::String &name_ = core::String(), const core::String &defaultSectionName = core::String())
				: name(name_), sections(), defaultSection(nullptr)
			{
				sections.push_back(IniSection(defaultSectionName));
				defaultSection = &sections.back();
			}
			IniFile(const IniFile &rhs) = default;
			~IniFile() = default;

			IniFile             &operator=(const IniFile &rhs) = default;

			store_type::iterator                findSection(const core::String &name) {
				for (auto it = sections.begin(); it != sections.end(); it++) {
					if (it->name == name) {
						return it;
					}
				}
				return sections.end();
			}

			const store_type::const_iterator    findSection(const core::String &name) const {
				for (auto it = sections.cbegin(); it != sections.cend(); it++) {
					if (it->name == name) {
						return it;
					}
				}
				return sections.cend();
			}
		};

	}
}

#endif //QUASARFX_INIFILE_H
