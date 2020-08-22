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
				for (auto &sec: ini.sections) {
					for (auto &prop: sec.values) {
						path = prop.first;
						if (!sec.name.empty()) {
							path = sec.name + Dot + path;
						}
						into.getStore().put(path, prop.second);
					}
				}
			}

			void    write(ostream_type &os, const value_type &from) override {

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
