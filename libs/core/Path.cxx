//
// Created by darkboss on 8/2/20.
//

#include "Path.h"
#include <filesystem>

namespace quasar {
	namespace core {
		PathExt::PathExt(const String::value_type *v)
			: mValue(v)
		{
			sanitize();
		}

		PathExt::PathExt(const String &v)
			: mValue(v)
		{
			sanitize();
		}


		PathExt &PathExt::operator=(const PathExt &rhs) {
			mValue = rhs.mValue;
			sanitize();
			return *this;
		}

		PathExt &PathExt::operator=(const String &rhs) {
			mValue = rhs;
			sanitize();
			return *this;
		}

		bool PathExt::operator==(const PathExt &rhs) const noexcept {
			return false;
		}

		bool PathExt::operator!=(const PathExt &rhs) const noexcept {
			return false;
		}

		bool PathExt::operator<=(const PathExt &rhs) const noexcept {
			return false;
		}

		bool PathExt::operator<(const PathExt &rhs) const noexcept {
			return false;
		}

		bool PathExt::operator>=(const PathExt &rhs) const noexcept {
			return false;
		}

		bool PathExt::operator>(const PathExt &rhs) const noexcept {
			return false;
		}

		const String &PathExt::str() const noexcept {
			return mValue;
		}

		void PathExt::sanitize() {
			while (mValue.front() == '.') {
				mValue.erase(mValue.begin());
			}
		}

		bool PathExt::operator==(const String &rhs) const noexcept {
			return mValue == rhs;
		}

		bool PathExt::operator!=(const String &rhs) const noexcept {
			return !(*this == rhs);
		}

		bool PathExt::operator==(const String::value_type *rhs) const noexcept {
			return strcmp(mValue.c_str(), rhs) == 0;
		}

		bool PathExt::operator!=(const String::value_type *rhs) const noexcept {
			return !(*this == rhs);
		}

# ifdef _WIN32
		const String Path::Separator = "\\";
# else
		const String Path::Separator = "/";
# endif

		Path::Path(const quasar::core::String &data)
			: mData(data)
		{}

		Path::Path(const String::value_type *data)
			: mData(data)
		{}

		Path::~Path() noexcept {

		}

		Path &Path::operator=(const String &rhs) {
			mData = rhs;
			return *this;
		}

		Path &Path::operator=(const String::value_type *rhs) {
			mData = String(rhs);
			return *this;
		}

		const String::value_type *Path::c_str() const noexcept {
			return mData.c_str();
		}

		const String &Path::absolute() const noexcept {
			return mData;
		}

		String Path::base() const noexcept {
			size_t pos;
			String ret = mData;
			if ((pos = mData.rfind(Separator)) != String::npos) {
				ret = mData.substr(pos + 1);
			}
			return ret;
		}

		PathExt Path::ext() const noexcept {
			String name = base();
			size_t pos;
			if ((pos = name.rfind(".")) != String::npos) {
				name = name.substr(pos + 1);
			}
			return PathExt(name);
		}

		Path Path::parent() const noexcept {
			size_t pos;
			String ret = mData;
			if ((pos = mData.rfind(Separator)) != String::npos) {
				ret = mData.substr(0, pos);
			}
			return Path(ret);
		}

		bool Path::isDir() const noexcept {
			return std::filesystem::is_directory(mData);
		}

		bool Path::isFile() const noexcept {
			return !isDir();
		}

		bool Path::isEmpty() const noexcept {
			return std::filesystem::is_empty(mData);
		}

		static void _readDir(String data, bool recurs, std::vector<Path> &res, bool (*filter)(const String &)) noexcept(false) {
			if (!std::filesystem::is_directory(data)) {
				throw std::runtime_error(data + ": cannot read dir, not a directory!");
			}
			for (auto &p: std::filesystem::directory_iterator(data)) {
				if (filter == nullptr || filter(p.path())) {
					res.emplace_back(p.path());
				}
				if (p.is_directory()) {
					_readDir(p.path(), recurs, res, filter);
				}
			}
		}

		std::vector<Path> Path::readDir(bool recurs, bool (*filter)(const String &)) const noexcept(false) {
			if (!isDir()) {
				throw std::runtime_error(mData + ": cannot read dir, not a directory!");
			}
			std::vector<Path> paths;
			_readDir(mData, recurs, paths, filter);
			return paths;
		}

		String Path::readFile() const noexcept(false) {
			if (!isFile()) {
				throw std::runtime_error(mData + ": cannot read file, this is a directory!");
			}
			return quasar::core::String();
		}

		bool Path::removeAll() {
			return std::filesystem::remove_all(mData);
		}

		bool Path::remove() {
			return std::filesystem::remove(mData);
		}

		bool Path::makeDirs() {
			return std::filesystem::create_directories(mData);
		}

		bool Path::makeDir() {
			return std::filesystem::create_directory(mData);
		}

		bool Path::operator==(const Path &rhs) const noexcept {
			return mData == rhs.mData;
		}

		bool Path::operator!=(const Path &rhs) const noexcept {
			return !(*this == rhs);
		}

		bool Path::operator<(const Path &rhs) const noexcept {
			return mData < rhs.mData;
		}

		bool Path::operator>(const Path &rhs) const noexcept {
			return mData > rhs.mData;
		}

		bool Path::operator<=(const Path &rhs) const noexcept {
			return mData <= rhs.mData;
		}

		bool Path::operator>=(const Path &rhs) const noexcept {
			return mData >= rhs.mData;
		}

		bool Path::exists() const noexcept {
			return std::filesystem::exists(mData);
		}

		Path Path::operator+(const Path &rhs) const {
			return join(rhs.mData);
		}

		String Path::operator+(const String &rhs) const {
			return mData + rhs;
		}

		String Path::operator+(const String::value_type *rhs) const {
			return mData + rhs;
		}

		Path            &Path::operator+=(const Path &rhs) {
			return *this = Path(*this) + rhs;
		}
		Path            &Path::operator+=(const String &rhs) {
			return *this = Path(*this) + rhs;
		}
		Path            &Path::operator+=(const String::value_type *rhs) {
			return *this = Path(*this) + rhs;
		}

		Path Path::join(const String &p) const noexcept {
			String ret = mData;
			size_t pos;
			if ((pos = ret.rfind(Separator)) != (ret.size() - 1)) {
				ret += Separator;
			}
			return Path(ret + p);
		}

		Path Path::join(const String::value_type *p) const noexcept {
			String ret = mData;
			size_t pos;
			if ((pos = ret.rfind(Separator)) != (ret.size() - 1)) {
				ret += Separator;
			}
			return Path(ret + p);
		}

		Path Path::join(const Path &p) const noexcept {
			String ret = mData;
			size_t pos;
			if ((pos = ret.rfind(Separator)) != (ret.size() - 1)) {
				ret += Separator;
			}
			return Path(ret + p.mData);
		}
	}
}

quasar::core::OStream &operator<<(quasar::core::OStream &os, const quasar::core::Path &p) {
	os << p.absolute();
	return os;
}

quasar::core::IStream &operator>>(quasar::core::IStream &is, quasar::core::Path &p) {
	quasar::core::String s;
	is >> s;
	p = quasar::core::Path(s);
	return is;
}

quasar::core::OStream &operator<<(quasar::core::OStream &os, const quasar::core::PathExt &p) {
	if (os) {
		os << p.str();
	}
	return os;
}

quasar::core::IStream &operator>>(quasar::core::IStream &is, quasar::core::PathExt &p) {
	quasar::core::String str;
	if (is && is >> str) {
		p = quasar::core::PathExt(str);
	}
	return is;
}

bool operator==(const quasar::core::String &lhs, const quasar::core::PathExt &rhs) {
	return lhs == rhs.str();
}

bool operator!=(const quasar::core::String &lhs, const quasar::core::PathExt &rhs) {
	return !(lhs == rhs);
}

bool operator==(const quasar::core::String::value_type *lhs, const quasar::core::PathExt &rhs) {
	return strcmp(lhs, rhs.str().c_str()) == 0;
}

bool operator!=(const quasar::core::String::value_type *lhs, const quasar::core::PathExt &rhs) {
	return !(lhs == rhs);
}
