//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_INIFILE_H
#define QUASARFX_INIFILE_H

#include <core/String.h>

namespace quasar {
	namespace formats {
		template<typename CharT>
		struct BasicIniSection {
			using string_type = core::BasicString<CharT>;
			using store_type = std::map<string_type, string_type>;

			BasicIniSection(const string_type &name_ = string_type(), const store_type &values_ = store_type()): name(name_), values(values_) {}
			BasicIniSection(const BasicIniSection &rhs) = default;
			~BasicIniSection() = default;

			BasicIniSection     &operator=(const BasicIniSection &rhs) = default;

			string_type         name;
			store_type          values;
		};

		extern template class BasicIniSection<char>;
		extern template class BasicIniSection<wchar_t>;

		using IniSection = BasicIniSection<Char>;

		template<typename CharT>
		struct BasicIniFile {
			using section_type  = BasicIniSection<CharT>;
			using store_type    = std::list<section_type>;
			using string_type   = core::BasicString<CharT>;

			string_type         name;
			store_type          sections;
			section_type        *defaultSection;

			BasicIniFile(const string_type &name_ = string_type(), const string_type &defaultSectionName = string_type(), const store_type &sections_ = store_type())
				: name(name_), sections(sections_), defaultSection(nullptr)
			{
				if (findSection(defaultSectionName) == sections.end()) {
					sections.push_back(section_type(defaultSectionName));
				}
				defaultSection = &*findSection(defaultSectionName);
			}
			BasicIniFile(const BasicIniFile &rhs) = default;
			~BasicIniFile() = default;

			BasicIniFile                                &operator=(const BasicIniFile &rhs) = default;

			typename store_type::iterator               findSection(const string_type &name) {
				for (auto it = sections.begin(); it != sections.end(); it++) {
					if (it->name == name) {
						return it;
					}
				}
				return sections.end();
			}

			const typename store_type::const_iterator    findSection(const string_type &name) const {
				for (auto it = sections.cbegin(); it != sections.cend(); it++) {
					if (it->name == name) {
						return it;
					}
				}
				return sections.cend();
			}
		};

		extern template class BasicIniFile<char>;
		extern template class BasicIniFile<wchar_t>;

		using IniFile = BasicIniFile<Char>;
	}
}

#endif //QUASARFX_INIFILE_H
