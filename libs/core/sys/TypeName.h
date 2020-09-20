//
// Created by darkboss on 9/20/20.
//

#ifndef QUASARFX_TYPENAME_H
#define QUASARFX_TYPENAME_H
// demangling
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>
#include <map>

namespace quasar {
	namespace core {
		template<class T> std::basic_string<char> type_name() {
			typedef typename std::remove_reference<T>::type TR;
			static const std::string constLabel = " const";
			static const std::string volatileLabel = " volatile";
			static const std::string lvalueLabel = " &";
			static const std::string rvalueLabel = " &&";
			static const std::map<std::string, std::string> aliases({
                {"quasar::core::BasicString<char>", "String"},
                {"quasar::core::BasicString<wchar_t>", "WString"},
			});
			std::unique_ptr<char, void(*)(void*)> own (
# ifndef _MSC_VER
				abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
# else
				nullptr,
# endif
				std::free
	        );
			std::basic_string<char> r = own != nullptr ? own.get() : typeid(TR).name();

			if (std::is_const<TR>::value) r += std::basic_string<char>(constLabel.begin(), constLabel.end());
			if (std::is_volatile<TR>::value) r += std::basic_string<char>(volatileLabel.begin(), volatileLabel.end());

			if (std::is_lvalue_reference<T>::value) r += std::basic_string<char>(lvalueLabel.begin(), lvalueLabel.end());
			else if (std::is_rvalue_reference<T>::value) r += std::basic_string<char>(rvalueLabel.begin(), rvalueLabel.end());

			size_t pos;
			for (auto const& alias: aliases) {
				while ((pos = r.find(alias.first)) != std::string::npos) {
					r.replace(pos, alias.first.size(), alias.second);
				}
			}
			return r;
		}

		template<class T> std::basic_string<wchar_t> wtype_name() {
			auto ret = type_name<T>();
			return std::basic_string<wchar_t>(ret.begin(), ret.end());
		}
	}
}
class TypeName {

};


#endif //QUASARFX_TYPENAME_H
