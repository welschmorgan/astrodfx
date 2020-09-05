//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_JSONVALUE_H
#define QUASARFX_JSONVALUE_H

#include <core/String.h>
#include <core/Config.h>
#include <cstring>
#include "JsonValueType.h"

namespace quasar {
	namespace formats {
		struct JsonValue {
		public:
			using null_type     = std::nullptr_t;
			using bool_type     = bool;
			using string_type   = core::String;
			using number_type   = core::String;
			using object_type   = std::map<core::String, JsonValue>;
			using array_type    = std::vector<JsonValue>;

			union {
				null_type       z;
				bool_type       b;
				string_type     s;
				string_type     n;
				object_type     o;
				array_type      a;
			};

		protected:
			JsonValueType       mType;
			JsonValue           *mParent;

			void                alloc(JsonValueType t) {
				mType = t;
				if (mType == JsonValueType::Number) {
					new(&n) number_type();
				} else if (mType == JsonValueType::String) {
					new(&s) string_type();
				} else if (mType == JsonValueType::Object) {
					new(&o) object_type();
				} else if (mType == JsonValueType::Array) {
					new(&a) array_type();
				}
			}

			void                copy(const JsonValue &rhs) {
				mParent = rhs.mParent;
				mType = rhs.mType;
				if (mType == JsonValueType::None) {
					z = nullptr;
				} else if (mType == JsonValueType::Bool) {
					b = rhs.b;
				} else if (mType == JsonValueType::Number) {
					new(&n) auto(rhs.n);
				} else if (mType == JsonValueType::String) {
					new(&s) auto(rhs.s);
				} else if (mType == JsonValueType::Object) {
					new(&o) auto(rhs.o);
				} else if (mType == JsonValueType::Array) {
					new(&a) auto(rhs.a);
				}
			}
			void                dealloc() {
				if (mType == JsonValueType::Number) {
					n.~basic_string();
				} else if (mType == JsonValueType::String) {
					s.~basic_string();
				} else if (mType == JsonValueType::Object) {
					o.~map();
				} else if (mType == JsonValueType::Array) {
					a.~vector();
				}
				mType = JsonValueType::None;
				z = nullptr;
			}
		public:
			JsonValue()
				: mParent(nullptr)
			{ alloc(JsonValueType::None); }

			template<typename T> JsonValue(T const *rhs);
			template<typename T> JsonValue(T const &rhs);

			template<typename V> JsonValue(std::vector<V> const &rhs): JsonValue()
			{
				mType = JsonValueType::Array;
				a = array_type();
				for (auto &val: rhs) {
					JsonValue newVal(val);
					newVal.setParent(mParent);
					a.push_back(newVal);
				}
			}

			template<typename K, typename V> JsonValue(std::map<K, V> const &rhs): JsonValue()
			{
				mType = JsonValueType::Array;
				o = object_type();
				core::StringStream ss;
				for (auto &val: rhs) {
					ss.clear();
					ss.str("");
					ss << val.first;
					JsonValue newVal(val.second);
					newVal.setParent(mParent);
					o.insert(std::make_pair(ss.str(), newVal));
				}
			}

			JsonValue(const JsonValue &rhs) {
				copy(rhs);
			}

			~JsonValue() {
				dealloc();
			}

			JsonValue               &operator=(const JsonValue &rhs) {
				dealloc();
				copy(rhs);
				return *this;
			}

			JsonValueType           type() const noexcept {
				return mType;
			}
			void                    setParent(JsonValue *obj) noexcept {
				mParent = obj;
			}
			JsonValue               *parent() noexcept {
				return mParent;
			}
			const JsonValue         *parent() const noexcept {
				return mParent;
			}
			void                    setNull() {
				dealloc();
				alloc(JsonValueType::None);
				z = nullptr;
			}
			void                    setString(const string_type &value) {
				dealloc();
				alloc(JsonValueType::String);
				s = value;
			}
			void                    setBool(bool_type value) {
				dealloc();
				alloc(JsonValueType::Bool);
				b = value;
			}
			template<typename T>
			void                    setNumber(T value) {
				dealloc();
				alloc(JsonValueType::Number);
				core::StringStream ss;
				ss << value;
				n = ss.str();
			}
			void                    setObject(const object_type &value) {
				dealloc();
				alloc(JsonValueType::Object);
				o = value;
			}
			void                    setArray(const array_type &value) {
				dealloc();
				alloc(JsonValueType::Array);
				a = value;
			}

			bool                    isNull() const noexcept { return mType == JsonValueType::None; }
			bool                    isBool() const noexcept { return mType == JsonValueType::Bool; }
			bool                    isObject() const noexcept { return mType == JsonValueType::Object; }
			bool                    isString() const noexcept { return mType == JsonValueType::String; }
			bool                    isNumber() const noexcept { return mType == JsonValueType::Number; }
			bool                    isArray() const noexcept { return mType == JsonValueType::Array; }

			string_type             getString() const {  return s; }

			template<typename N>
			N                       getNumber() const {
				core::StringStream ss;
				ss << n;
				N ret = N();
				if (!(ss >> ret)) {
					throw std::runtime_error("Failed to extract JsonNumber to " + core::String(typeid(N).name()));
				}
				return ret;
			}

			bool_type               getBool() const { return b; }

			object_type             &getObject() {  return o; }
			const object_type       &getObject() const {  return o; }

			array_type              &getArray() {  return a; }
			const array_type        &getArray() const {  return a; }

			core::ConfigNode        toNode() const {
				core::ConfigNode    node;
				core::StringStream  ss;

				if (mType == JsonValueType::None) {
					node.setValue(z);
				} else if (mType == JsonValueType::Bool) {
					node.setValue(b);
				} else if (mType == JsonValueType::Number) {
					node.setValue(n);
				} else if (mType == JsonValueType::String) {
					node.setValue(s);
				} else if (mType == JsonValueType::Object) {
					for (auto it = o.begin(); it != o.end(); it++) {
						auto &childNode = node.createChild(it->first);
						auto newNode = it->second.toNode();
						childNode = newNode;
						childNode.setName(it->first);
						childNode.setParent(&node);
					}
				} else if (mType == JsonValueType::Array) {
					size_t id = 0;
					core::StringStream ss;
					for (auto it = a.begin(); it != a.end(); it++) {
						ss.clear();
						ss.str("");
						auto &childNode = node.createChild(ss.str());
						auto newNode = it->toNode();
						childNode = newNode;
						childNode.setName(ss.str());
						childNode.setParent(&node);
						id++;
					}
				} else {
					throw std::runtime_error("unknown json node type: " + mType.name());
				}
				return node;
			}

			string_type             toString(bool pretty = false, int indent = 0) const {
				core::StringStream ss;
				core::String indentStr(indent, '\t');
				if (mType == JsonValueType::None) {
					ss << indentStr << "null";
				} else if (mType == JsonValueType::Bool) {
					ss << indentStr << std::boolalpha << b;
				} else if (mType == JsonValueType::Number) {
					ss << indentStr << n;
				} else if (mType == JsonValueType::String) {
					ss << indentStr << s;
				} else if (mType == JsonValueType::Object) {
					ss << indentStr << "{" << (pretty ? "\n" : "");
					for (auto it = o.begin(); it != o.end(); it++) {
						ss << (pretty ? "\t" : "") << it->first << ": " << it->second.toString(pretty, pretty ? (indent + 1) : 0);
						if (it != --o.end()) {
							ss << ",";
						}
						ss  << (pretty ? "\n" : " ");
					}
					ss << indentStr << "}";
				} else if (mType == JsonValueType::Array) {
					ss << indentStr << "[" << (pretty ? "\n" : "");
					for (auto it = a.begin(); it != a.end(); it++) {
						ss << (pretty ? "\t" : "") << it->toString(pretty, pretty ? (indent + 1) : 0);
						if (it != --a.end()) {
							ss << ",";
						}
						ss << (pretty ? "\n" : " ");
					}
					ss << indentStr << "]";
				}
				return ss.str();
			}
		};

		template<> JsonValue::JsonValue(string_type const &rhs): JsonValue()
		{ setString(rhs); }

		template<> JsonValue::JsonValue(object_type const &rhs): JsonValue()
		{ setObject(rhs); }

		template<> JsonValue::JsonValue(const string_type::value_type *rhs): JsonValue()
		{ setString(rhs); }

		template<> JsonValue::JsonValue(bool const &rhs): JsonValue()
		{ setBool(rhs); }

		template<> JsonValue::JsonValue(string_type::value_type const &rhs): JsonValue()
		{ setString(core::String(1, rhs)); }

		template<> JsonValue::JsonValue(short const &rhs): JsonValue()
		{ setNumber(rhs); }

		template<> JsonValue::JsonValue(int const &rhs): JsonValue()
		{ setNumber(rhs); }

		template<> JsonValue::JsonValue(long const &rhs): JsonValue()
		{ setNumber(rhs); }

		template<> JsonValue::JsonValue(unsigned char const &rhs): JsonValue()
		{ setString(core::String(1, rhs)); }

		template<> JsonValue::JsonValue(unsigned short const &rhs): JsonValue()
		{ setNumber(rhs); }

		template<> JsonValue::JsonValue(unsigned int const &rhs): JsonValue()
		{ setNumber(rhs); }

		template<> JsonValue::JsonValue(unsigned long const &rhs): JsonValue()
		{ setNumber(rhs); }

		template<> JsonValue::JsonValue(float const &rhs): JsonValue()
		{ setNumber(rhs); }

		template<> JsonValue::JsonValue(double const &rhs): JsonValue()
		{ setNumber(rhs); }
	}
}


#endif //QUASARFX_JSONVALUE_H
