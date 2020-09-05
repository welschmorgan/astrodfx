//
// Created by darkboss on 9/5/20.
//

#ifndef QUASARFX_TOKEN_H
#define QUASARFX_TOKEN_H

# include "String.h"

namespace quasar {
	namespace core {

		enum TokenFlags {
			TF_NONE        = 0,                 // Simple trigger, no flags
			TF_REGEX       = 1 << 1,            // Trigger is a regex
			TF_AGGREGATE   = 1 << 2             // Multiple consecutive triggers should
			// be aggregated into 1 token
		};

		template<typename CharT>
		class BasicTokenList;

		/**
		 * @brief Represent a token (separator/symbol) in a text
		 * @tparam CharT		Type of characters to handle
		 */
		template<typename CharT>
		class BasicToken {
		public:
			using char_type         = CharT;
			using stream_type       = std::basic_istream<CharT>;
			using string_type       = std::basic_string<char_type>;
			using self_type         = BasicToken<CharT>;
			using list_type         = BasicTokenList<CharT>;
			using id_type           = long;

		protected:
			stream_type             *mStream;
			id_type                 mType;
			id_type                 mId;
			unsigned int            mFlags;
			string_type             mTrigger;
			string_type             mText;
			std::streamoff          mOffset;
			BasicTokenList<CharT>   *mParent;

		public:
			BasicToken()
				: mStream(nullptr)
				, mType(0)
				, mId(-1)
				, mFlags(TF_NONE)
				, mTrigger()
				, mText()
				, mOffset(0)
				, mParent(nullptr)
			{}

			BasicToken(stream_type *stream, id_type type, const string_type &trigger, const string_type &text, std::streamoff offset, unsigned int flags = TF_NONE)
				: mStream(stream)
				, mType(type)
				, mId(-1)
				, mFlags(flags)
				, mTrigger()
				, mText(text)
				, mOffset(offset)
				, mParent(nullptr)
			{
				setTrigger(trigger);
			}

			BasicToken(id_type type, const string_type &trigger, unsigned int flags = TF_NONE)
				: mStream(nullptr)
				, mType(type)
				, mId(-1)
				, mFlags(flags)
				, mTrigger()
				, mText()
				, mOffset()
				, mParent(nullptr)
			{
				setTrigger(trigger);
			}

			BasicToken(const BasicToken &rhs)
				: mStream(rhs.mStream)
				, mType(rhs.mType)
				, mId(-1)
				, mFlags(rhs.mFlags)
				, mTrigger(rhs.mTrigger)
				, mText(rhs.mText)
				, mOffset(rhs.mOffset)
				, mParent(rhs.mParent)
			{}

			virtual ~BasicToken() noexcept = default;

			BasicToken              &operator=(const BasicToken &rhs) {
				mStream = rhs.mStream;
				mType = rhs.mType;
				mId = rhs.mId;
				mFlags = rhs.mFlags;
				mTrigger = rhs.mTrigger;
				mText = rhs.mText;
				mOffset = rhs.mOffset;
				mParent = rhs.mParent;
				return *this;
			}

			bool                    operator==(const BasicToken &rhs) const noexcept {
				return mId == rhs.mId && mStream == rhs.mStream && mTrigger == rhs.mTrigger && mText == rhs.mText && mOffset == rhs.mOffset && mType == rhs.mType;
			}

			bool                    operator!=(const BasicToken &rhs) const noexcept {
				return !(*this == rhs);
			}

			unsigned int            getFlags() const noexcept { return mFlags; }
			bool                    isRegex() const noexcept { return getFlags() & TF_REGEX; }
			bool                    shouldAggregate() const noexcept { return getFlags() & TF_AGGREGATE; }

			id_type                 getId() const noexcept { return mId; }
			self_type               setId(const id_type id) noexcept { mId = id; return *this; }

			const string_type       &getTrigger() const noexcept { return mTrigger; }
			BasicToken              &setTrigger(const string_type &t) noexcept {
				mTrigger = t;
				if ((mFlags & TF_REGEX) && mTrigger.front() != '^') {
					mTrigger.insert(0, 1, '^');
				}
				return *this;
			}

			const string_type       &getText() const noexcept { return mText; }
			BasicToken              &setText(const string_type &t) noexcept { mText = t; return *this; }

			id_type                 getType() const noexcept { return mType; }
			BasicToken              &setType(id_type t) noexcept { mType = t; return *this; }

			std::streamoff          getOffset() const noexcept { return mOffset; }
			BasicToken              &setOffset(std::streamoff t) noexcept { mOffset = t; return *this; }

			stream_type             *getStream() noexcept { return mStream; }
			const stream_type       *getStream() const noexcept { return mStream; }
			BasicToken              &setStream(stream_type *t) noexcept { mStream = t; return *this; }

			list_type               *getParent() noexcept { return mParent; }
			const list_type         *getParent() const noexcept { return mParent; }
			BasicToken              &setParent(list_type *p) noexcept { mParent = p; return *this; }

			list_type               takePreviousUntil(const list_type &stoppers, bool including = false);
			list_type               takeNextUntil(const list_type &stoppers, bool including = false);

			const self_type         *getPreviousSibling(const self_type &type) const;
			self_type               *getPreviousSibling(const self_type &type);

			const self_type         *getNextSibling(const self_type &type) const;
			self_type               *getNextSibling(const self_type &type);

		};

		extern template class BasicToken<char>;
		extern template class BasicToken<wchar_t>;

		using Token                 = BasicToken<Char>;
	}
}

#endif //QUASARFX_TOKEN_H
