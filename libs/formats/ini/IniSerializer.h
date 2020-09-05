//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_INISERIALIZER_H
# define QUASARFX_INISERIALIZER_H

# include <core/Serializer.h>
# include <core/Config.h>
# include <core/String.h>
# include "IniFile.h"
# include <iostream>

namespace quasar {
	namespace formats {
		template<typename IStreamT = core::IStream, typename OStreamT = core::OStream>
		class IniSerializer : public core::Serializer<core::Config, IStreamT, OStreamT> {
		public:
			using base_type     = core::Serializer<core::Config, IStreamT, OStreamT>;
			using self_type     = IniSerializer<IStreamT, OStreamT>;

			using value_type    = typename base_type::value_type;
			using istream_type  = typename base_type::istream_type;
			using ostream_type  = typename base_type::ostream_type;

			static constexpr core::String::value_type   DefaultSectionName[] = "";
			static const core::String::value_type       Dot = '.';
			static constexpr core::String::value_type   CommentDelims[] = "#;";
			static const size_t                         NCommentDelims = 2;
			static const core::String::value_type       SectionDelimL = '[';
			static const core::String::value_type       SectionDelimR = ']';
			static constexpr core::String::value_type   StoreSectionDelim[] = "::";
			static const core::String::value_type       PropertyDelim = '=';

			IniSerializer() = default;
			IniSerializer(const IniSerializer &) = default;
			virtual ~IniSerializer() noexcept = default;

			IniSerializer &operator=(const IniSerializer &) = default;

			void    read(istream_type &is, value_type &into) override {
				core::String line;
				IniFile     ini;
				ini.sections.push_back(IniSection(DefaultSectionName));
				if (!is) {
					return;
				}
				while (std::getline(is, line)) {
					// for each lines in input stream
					line = core::trim(line);
					removeComments(line);
					if (!line.empty()) {
						// process line
						if (*line.begin() == SectionDelimL && *(--line.end()) == SectionDelimR) {
							// found section
							readSectionName(line, ini);
						} else {
							// found property
							readProperty(line, ini);
						}
					}
				}

				core::String path;
				core::ConfigNode *section;
				for (auto &sec: ini.sections) {
					for (auto &prop: sec.values) {
						path = prop.first;
						if (!sec.name.empty()) {
							section = &into.createChild(sec.name);
						} else {
							section = &into;
						}
						section->setProperty(prop.first, prop.second);
					}
				}
			}

			void    write(ostream_type &os, const value_type &from) override {
				auto store = from.getProperties();
				if (!os) {
					return;
				}
				IniFile ini;
				IniFile::store_type::iterator sectionIt;
				size_t sectionPos;
				core::String sectionName;
				core::String key, val;
				size_t valPos;
				for (auto it = store.begin(); it != store.end(); it++) {
					if ((sectionPos = it->first.find(StoreSectionDelim)) != core::String::npos) {
						// extract section / key
						sectionName = it->first.substr(0, sectionPos);
						key = it->first.substr(sectionPos + strlen(StoreSectionDelim));
					} else {
						// key is whole line
						key = it->first;
					}
					val = it->second;
					if (sectionName.empty()) {
						sectionName = ini.defaultSection->name;
					}
					if ((sectionIt = ini.findSection(sectionName)) == ini.sections.end()) {
						ini.sections.push_back(IniSection(sectionName));
						sectionIt = --ini.sections.end();
					}
					sectionIt->values[key] = val;
				}

				for (auto &sec: ini.sections) {
					sectionName = sec.name;
					if (sec.name.empty()) {
						sectionName = ini.defaultSection->name;
					}
					if (!sectionName.empty()) {
						os << SectionDelimL << sec.name << SectionDelimR << std::endl;
					}
					for (auto &prop: sec.values) {
						os << prop.first << PropertyDelim << prop.second << std::endl;
					}
				}
			}

			void readSectionName(core::String &line, IniFile &ini) {
				line.erase(line.begin());
				line.erase(--line.end());
				ini.sections.push_back(IniSection(core::trim(line)));
			}

			void readProperty(core::String &line, IniFile &ini) {
				core::String key, val;
				size_t pos;
				if ((pos = line.find(PropertyDelim)) != core::String::npos) {
					// assignment
					key = line.substr(0, pos);
					val = line.substr(pos + 1);
				} else {
					// no value ??
					key = line;
				}
				key = core::trim(key);
				val = core::trim(val);
				ini.sections.back().values[key] = val;
			}

			void removeComments(core::String &line) {
				size_t comPos;
				const core::String::value_type *comCh;
				for (comCh = &CommentDelims[0]; comCh < &CommentDelims[NCommentDelims]; comCh++) {
					if ((comPos = line.rfind(*comCh)) != core::String::npos) {
						line = line.substr(0, comPos);
					}
				}
			}
		};
	}
}


#endif //QUASARFX_INISERIALIZER_H
