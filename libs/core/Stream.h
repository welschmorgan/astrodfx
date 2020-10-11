//
// Created by darkboss on 10/11/20.
//

#ifndef QUASARFX_STREAM_H
#define QUASARFX_STREAM_H


#include <iostream>
#include "Path.h"
#include "Pointers.h"

namespace quasar {
	namespace core {
		template<typename CharT>
		class BasicStream: public std::basic_iostream<CharT> {
		public:
			using char_type             = CharT;
			using istream_type          = std::basic_istream<char_type>;
			using ostream_type          = std::basic_ostream<char_type>;
			using stream_type           = std::basic_iostream<char_type>;
			using streambuf_type        = std::basic_streambuf<char_type>;
			using self_type             = BasicStream<char_type>;
			using access_mode_type      = std::ios_base::openmode;

		protected:
			Path                        mPath;
			String                      mType;
			access_mode_type            mOpenMode;

		public:
			BasicStream(const String &type, access_mode_type openMode = std::ios::in | std::ios::out, const Path &path = Path())
				: stream_type()
				, mPath(path)
				, mType(type)
				, mOpenMode(openMode)
			{}
			BasicStream(const BasicStream &rhs) = delete;
			virtual ~BasicStream() = default;

			BasicStream                 &operator=(const BasicStream &rhs) = delete;

			explicit operator           stream_type() { return *this; }
			explicit operator           istream_type() { assert_is_istream(); return *this; }
			explicit operator           ostream_type() { assert_is_ostream(); return *this; }

			virtual void                open(const Path &path, access_mode_type access = std::ios::in | std::ios::out) {
				if (isOpen()) {
					close();
				}
				setPath(path);
				setAccessMode(access);
				open();
			}
			virtual bool                isOpen() = 0;
			virtual void                open() = 0;
			virtual void                close() = 0;

			access_mode_type            getAccessMode() { return mOpenMode; }
			bool                        hasAccessMode(access_mode_type openMode) const { return (mOpenMode & openMode) != 0;}
			self_type                   &setAccessMode(access_mode_type mode) { mOpenMode = mode; return *this; }

			virtual std::streamsize     getSize() const {
				assert_is_istream();
				auto self = const_cast<self_type *>(this);
				std::streampos  pos  = self->tellg();
				self->seekg(0, std::ios::end);
				std::streamsize size = self->tellg();
				self->seekg(pos, std::ios::beg);
				return size;
			}

			const Path                  &getPath() const { return mPath; }

			self_type                   &setPath(const Path &p) { mPath = p; return *this; }

			const String                &getType() const { return mType; }

			std::streamsize             readwhole(String &data) {
				assert_is_istream();
				char_type               chunk[4096] = {0};
				std::streamsize         fullSize = 0, chunkSize;
				while ((chunkSize = self_type::readsome(chunk, 4096)) > 0) {
					data.append(chunk, chunkSize);
					fullSize += chunkSize;
				}
				return fullSize;
			}

			std::streamsize             readwhole(std::vector<Char> &data) {
				String vdata;
				std::streamsize sz = readwhole(vdata);
				std::copy(vdata.begin(), vdata.end(), std::back_inserter(data));
				return sz;
			}

		protected:
			void                        assert_is_ostream() const noexcept(false) {
				if ((mOpenMode & std::ios::out) == 0) {
					throw std::runtime_error(mType + " stream '" + mPath.base() + "' is not an output stream");
				}
			}

			void                        assert_is_istream() const noexcept(false) {
				if ((mOpenMode & std::ios::in) == 0) {
					throw std::runtime_error(mType + " stream '" + mPath.base() + "' is not an input stream");
				}
			}

			void                        assert_is_binary() const noexcept(false) {
				if ((mOpenMode & std::ios::binary) == 0) {
					throw std::runtime_error(mType + " stream '" + mPath.base() + "' is not binary");
				}
			}

			void                        assert_is_text() const noexcept(false) {
				if ((mOpenMode & std::ios::binary) == 0) {
					throw std::runtime_error(mType + " stream '" + mPath.base() + "' is not text");
				}
			}

			void                        assert_is_open() const noexcept(false) {
				if (!isOpen()) {
					throw std::runtime_error(mType + " stream '" + mPath.base() + "' is closed");
				}
			}
		};

		using Stream                    = BasicStream<Char>;
		using SharedStream              = SharedPtr<BasicStream<Char>>;

		template<typename CharT>
		class BasicMemoryStream
			: public BasicStream<CharT>
		{
		public:
			using base_type             = BasicStream<CharT>;
			using self_type             = BasicMemoryStream<CharT>;
			using access_mode_type      = typename base_type::access_mode_type ;

		protected:
			std::basic_stringstream<CharT>  mMemStream;

		public:
			BasicMemoryStream(const Path &path = Path(), access_mode_type openMode = std::ios::in | std::ios::out)
				: base_type("memory", openMode, path)
			{ base_type::rdbuf(mMemStream.rdbuf()); }
			BasicMemoryStream(const BasicMemoryStream &rhs) = delete;
			virtual ~BasicMemoryStream() noexcept {
				try {
					if (isOpen()) {
						close();
					}
				} catch (std::exception &ex) {
					std::string asciiPath(base_type::mPath.begin(), base_type::mPath.end());
					std::cerr << asciiPath << ": couldn't destroy memory stream, " << ex.what() << std::endl;
				}
			}

			BasicMemoryStream           &operator=(const BasicMemoryStream &rhs) = delete;

			bool                        isOpen() { return true; }
			void                        open() {}
			void                        close() {}

			core::String                str() const {
				return mMemStream.str();
			}

			self_type                   &str(const core::String &s) const {
				return mMemStream.str(s);
			}
		};

		using MemoryStream              = BasicMemoryStream<Char>;
		using SharedMemoryStream        = SharedPtr<BasicMemoryStream<Char>>;

		template<typename CharT>
		class BasicFileStream
			: public BasicStream<CharT>
		{
		public:
			using base_type             = BasicStream<CharT>;
			using self_type             = BasicFileStream<CharT>;
			using access_mode_type      = typename base_type::access_mode_type ;

		protected:
			std::basic_fstream<CharT>   mFileStream;

		public:
			BasicFileStream(const Path &path, access_mode_type openMode = std::ios::in | std::ios::out)
				: base_type("file", openMode, path)
				, mFileStream()
			{
				base_type::rdbuf(mFileStream.rdbuf());
				open();
			}
			BasicFileStream()
				: base_type("file")
				, mFileStream()
			{
				base_type::rdbuf(mFileStream.rdbuf());
			}
			BasicFileStream(const BasicFileStream &rhs) = delete;
			virtual ~BasicFileStream() noexcept {
				try {
					if (isOpen()) {
						close();
					}
				} catch (std::exception &ex) {
					std::string asciiPath(base_type::mPath.begin(), base_type::mPath.end());
					std::cerr << asciiPath << ": couldn't destroy file stream, " << ex.what() << std::endl;
				}
			}

			BasicFileStream             &operator=(const BasicFileStream &rhs) = delete;

			bool                        isOpen() { return mFileStream.is_open(); }
			void                        open(const Path &path, access_mode_type access = std::ios::in | std::ios::out) {
				base_type::open(path, access);
			}
			void                        open() {
				if (isOpen()) {
					close();
				}
				mFileStream.open(base_type::mPath.absolute(), base_type::mOpenMode);
			}
			void                        close() {
				if (isOpen()) {
					mFileStream.close();
				}
			}
		};

		using FileStream                = BasicFileStream<Char>;
		using SharedMemoryStream        = SharedPtr<BasicMemoryStream<Char>>;
	}
}

#endif //QUASARFX_STREAM_H
