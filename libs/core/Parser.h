 //
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_PARSER_H
#define QUASARFX_PARSER_H

#include "Lexer.h"
#include "Location.h"
#include "Exception.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		class BasicSyntaxError: public BasicException<CharT> {
		public:
			using script_location_type  = BasicScriptLocation<CharT>;
			using source_location_type  = BasicSourceLocation<CharT>;
			using base_type             = BasicException<CharT>;
			using string_type           = typename base_type::string_type;
			using builder_type          = typename base_type::builder_type;

		protected:
			script_location_type        mScriptLoc;

			static std::string          build(const string_type &msg, const script_location_type &script_loc, const source_location_type &source_loc = source_location_type()) {
				builder_type builder;
				builder << "[Syntax Error] " << std::string(msg.begin(), msg.end());
				if (script_loc.hasFile()) {
					builder << " in file " << std::string(script_loc.getFile().begin(), script_loc.getFile().end());
				}
				if (script_loc.hasLine()) {
					builder << " at line " << script_loc.getLine();
				}
				if (script_loc.hasColumn()) {
					builder << ", column " << script_loc.getColumn();
				}
				if (script_loc.hasOffset()) {
					builder << " (offset: " << script_loc.getOffset() << ")";
				}
				return builder.str();
			}

		public:
			BasicSyntaxError(const std::basic_string<char> &msg, const script_location_type &script_loc, const source_location_type &source_loc = source_location_type())
				: base_type()
				, mScriptLoc(script_loc)
			{
				base_type::mMessage = string_type(msg.begin(), msg.end());
				base_type::mFullMessage = build(string_type(msg.begin(), msg.end()), script_loc, source_loc);
				base_type::mLocation = source_loc;
			}
			BasicSyntaxError(const std::basic_string<wchar_t> &msg, const script_location_type &script_loc, const source_location_type &source_loc = source_location_type())
				: base_type()
				, mScriptLoc(script_loc)
			{
				base_type::mMessage = string_type(msg.begin(), msg.end());
				base_type::mFullMessage = build(string_type(msg.begin(), msg.end()), script_loc, source_loc);
				base_type::mLocation = source_loc;
			}
			BasicSyntaxError(const BasicSyntaxError &rhs) = default;
			virtual ~BasicSyntaxError() = default;

			BasicSyntaxError                 &operator=(const BasicSyntaxError &rhs) = default;

			const script_location_type  &getScriptLocation() const noexcept {
				return mScriptLoc;
			}
		};

		extern template class BasicSyntaxError<char>;
		extern template class BasicSyntaxError<wchar_t>;

		using SyntaxError = BasicSyntaxError<Char>;

		template<typename CharT, typename ResultT, typename LexerT = BasicLexer<CharT, BasicToken<CharT>>>
		class BasicParser {
		public:
			using lexer_type        = LexerT;

			using token_type        = typename lexer_type::token_type;
			using token_list        = typename lexer_type::result_type;

			using result_type       = ResultT;

			using parse_fn_type     = std::function<void(const token_list *, typename token_list::citer_type &)>;
			using parse_fn_map      = std::map<typename token_type::id_type, parse_fn_type>;

		protected:
			result_type             mResult;
			parse_fn_map            mFuncs;
			parse_fn_type           mDefaultFunc;
			parse_fn_type           mAnyTokenFunc;

		public:
			BasicParser() = default;
			explicit BasicParser(const std::initializer_list<typename parse_fn_map::value_type> &parse_fns)
				: mResult()
				, mFuncs(parse_fns)
				, mDefaultFunc()
				, mAnyTokenFunc()
			{ resetDefaultFunc(); }
			explicit BasicParser(const parse_fn_map &parse_fns)
				: mResult()
				, mFuncs(parse_fns)
				, mDefaultFunc()
				, mAnyTokenFunc()
			{ resetDefaultFunc(); }
			BasicParser(const BasicParser &rhs) = default;
			virtual                 ~BasicParser() = default;

			BasicParser             &operator=(const BasicParser &rhs) = default;

			virtual result_type     parse(const token_list &tokens) {
				result_type         res;

				parse(tokens, res);
				return res;
			}

			virtual void            reset() {
				mResult = result_type();
			}

			virtual void            parse(const token_list &tokens, result_type &into) {
				auto it = tokens.begin();
				reset();
				while (it != tokens.end()) {
#ifndef NDEBUG
					std::cout << "Parser::parse | " << *it << std::endl;
#endif
					auto parse_fn = mFuncs.find(it->getType());
					if (mAnyTokenFunc) {
						mAnyTokenFunc(&tokens, it);
					}
					if (parse_fn != mFuncs.end()) {
						parse_fn->second(&tokens, it);
					} else {
						if (mDefaultFunc) {
							mDefaultFunc(&tokens, it);
						}
					}
					it++;
				}
				into = mResult;
			}

			const parse_fn_type     &getDefaultFunc() const {
				return mDefaultFunc;
			}

			void                    resetDefaultFunc() {
				setDefaultFunc(std::bind(&BasicParser::defaultParseFunc, this, std::placeholders::_1, std::placeholders::_2));
			}

			void                    setDefaultFunc(const parse_fn_type &defaultFunc) {
				mDefaultFunc = defaultFunc;
			}

			const parse_fn_type     &getAnyTokenFunc() const {
				return mAnyTokenFunc;
			}

			void                    setAnyTokenFunc(const parse_fn_type &anyFunc) {
				mAnyTokenFunc = anyFunc;
			}

		protected:
			virtual void            defaultParseFunc(const token_list *tokens, const typename token_list::citer_type &it) {
				throw std::runtime_error("missing parser_fn for token '" + it->getTrigger() + "'");
			}
		};

		template<typename ResultT, typename LexerT = BasicLexer<Char, BasicToken<Char>>>
		using Parser                = BasicParser<Char, ResultT, LexerT>;
	}
}

#endif //QUASARFX_PARSER_H
