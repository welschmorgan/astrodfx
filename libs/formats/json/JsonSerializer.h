//
// Created by darkboss on 8/22/20.
//

#ifndef QUASARFX_JSONSERIALIZER_H
# define QUASARFX_JSONSERIALIZER_H

# include <core/Serializer.h>
# include <core/Config.h>
# include <core/String.h>
# include "JsonFile.h"
# include <iostream>

namespace quasar {
	namespace formats {
		template<typename IStreamT = core::IStream, typename OStreamT = core::OStream>
		class JsonSerializer : public core::Serializer<core::Config, IStreamT, OStreamT> {
		protected:
			JsonValue::string_type              mAccu;
			JsonValue::string_type              mNextLabel;
			JsonValue                           *mCurrentNode;
			bool                                mRootObject;
			bool                                mInQuote;

		public:
			using base_type     = core::Serializer<core::Config, IStreamT, OStreamT>;
			using self_type     = JsonSerializer<IStreamT, OStreamT>;

			using value_type    = typename base_type::value_type;
			using istream_type  = typename base_type::istream_type;
			using ostream_type  = typename base_type::ostream_type;

			JsonSerializer()
				: mAccu()
				, mNextLabel()
				, mCurrentNode(nullptr)
				, mRootObject(true)
				, mInQuote(false)
			{}
			JsonSerializer(const JsonSerializer &) = default;
			virtual         ~JsonSerializer() noexcept = default;

			JsonSerializer  &operator=(const JsonSerializer &) = default;

			void            read(istream_type &is, value_type &into) override {
				char buf[1024] = {0};
				size_t numRead = 0;
				if (!is) {
					return;
				}
				JsonFile json;
				mAccu = "";
				mNextLabel = "";
				mInQuote = false;
				mCurrentNode = &json.root;
				mRootObject = true;
				while ((numRead = is.readsome(buf, 1024))) {
					buf[numRead] = 0;
					parse(buf);
				}
				std::cout << json.root.toString(true) << std::endl;
				validate(&json.root, &into);
			}

			void    write(ostream_type &os, const value_type &from) override {
			}

		private:
			void            validate(const JsonValue *node, core::ConfigNode *into) {
				if (!core::trim(mAccu).empty()) {
					throw std::runtime_error("Unprocessed data in accumulator at json parsing exit: " + mAccu);
				}
				if (node->type() != JsonValueType::Array && node->type() != JsonValueType::Object) {
					throw std::runtime_error("validation failed: node is neither an array or an object");
				}

				*into = node->toNode();
			}

			void            parse(const char *buf) {
				const char *pCur = buf;
				std::cout << "parse: " << core::trimmed(buf) << std::endl;
				while (pCur && *pCur) {
					switch (*pCur) {
						case ':':
							createLabel();
							break;
						case ',':
							addPropertyOrValue();
							break;
						case '{': {
							openObject();
							break;
						}
						case '}':
							closeObject();
							break;
						case '[':
							openArray();
							break;
						case ']':
							closeArray();
							break;
						case '"':
							if (!mInQuote) {
								openQuote();
							} else {
								closeQuote();
							}
							mInQuote = !mInQuote;
						default:
							mAccu.push_back(*pCur);
							break;
					}
					pCur++;
				}
			}

			void    openObject() {
				if (!mRootObject) {
					std::cout << "+ open object: " << mNextLabel << std::endl;
					if (mCurrentNode->type() == JsonValueType::Object) {
						JsonValue::object_type *obj = &mCurrentNode->getObject();
						JsonValue new_obj;
						new_obj.setParent(mCurrentNode);
						new_obj.setObject(JsonValue::object_type());
						(*obj)[mNextLabel] = new_obj;
						mCurrentNode = &mCurrentNode->getObject().at(mNextLabel);
					} else if (mCurrentNode->type() == JsonValueType::Object) {
						JsonValue::array_type *arr = &mCurrentNode->getArray();
						JsonValue             new_obj;
						new_obj.setParent(mCurrentNode);
						new_obj.setObject(JsonValue::object_type());
						arr->push_back(new_obj);
						mCurrentNode = &arr->back();
					} else {
						throw std::runtime_error("unsupported json node type for object creation: " + mCurrentNode->type().name());
					}
				} else {
					std::cout << "+ open root object: " << mNextLabel << std::endl;
					mCurrentNode->setObject(JsonValue::object_type());
				}
				mRootObject = false;
				mNextLabel = "";
			}

			void    closeObject() {
				if (!core::trimmed(mAccu).empty()) {
					addPropertyOrValue();
				}
				if (!mCurrentNode->parent()) {
					std::cout << "+ close root object" << std::endl;
				} else {
					std::cout << "+ close object: " << mNextLabel << std::endl;
				}
				mCurrentNode = mCurrentNode->parent();
			}

			void    openArray() {
				if (!mRootObject) {
					std::cout << "+ open array: " << mNextLabel << std::endl;
					if (mCurrentNode->type() == JsonValueType::Object) {
						JsonValue::object_type *obj = &mCurrentNode->getObject();
						JsonValue new_obj;
						new_obj.setParent(mCurrentNode);
						new_obj.setArray(JsonValue::array_type());
						(*obj)[mNextLabel] = new_obj;
						mCurrentNode = &obj->at(mNextLabel);
					} else if (mCurrentNode->type() == JsonValueType::Array) {
						JsonValue::array_type *arr = &mCurrentNode->getArray();
						JsonValue new_obj;
						new_obj.setParent(mCurrentNode);
						new_obj.setArray(JsonValue::array_type());
						(*arr).push_back(new_obj);
						mCurrentNode = &arr->back();
					}
				} else {
					std::cout << "+ open root array" << std::endl;
					mCurrentNode->setArray(JsonValue::array_type());
				}
				mNextLabel = "";
			}

			void    closeArray() {
				if (!core::trimmed(mAccu).empty()) {
					addPropertyOrValue();
				}
				if (!mCurrentNode->parent()) {
					std::cout << "+ close root array" << std::endl;
				} else {
					std::cout << "+ close array: " << mNextLabel << std::endl;
				}
				mCurrentNode = mCurrentNode->parent();
			}

			void    addPropertyOrValue() {
				if (mCurrentNode->type() != JsonValueType::Object && mCurrentNode->type() != JsonValueType::Array) {
					throw std::runtime_error("unsupported json node type for property or value creation: " + mCurrentNode->type().name());
				}
				if (!core::trimmed(mAccu).empty()) {
					if (mCurrentNode->type() == JsonValueType::Object) {
						std::cout << "\tadd property: " << mNextLabel << " = " << mAccu << std::endl;
						JsonValue new_val;
						new_val.setParent(mCurrentNode);
						new_val.setString(mAccu);
						mCurrentNode->getObject()[mNextLabel] = new_val;
					} else {
						std::cout << "\tadd value: " << mAccu << std::endl;
						JsonValue new_val;
						new_val.setParent(mCurrentNode);
						new_val.setString(mAccu);
						mCurrentNode->getArray().push_back(new_val);
					}
					mAccu = "";
					mNextLabel = "";
				}
			}

			void    createLabel() {
				if (mCurrentNode->type() != JsonValueType::Object) {
					throw std::runtime_error("unsupported json node type for label creation: " + mCurrentNode->type().name());
				}
				std::cout << "\tadd label: " << mAccu<< std::endl;
				mNextLabel = mAccu;
				mAccu = "";
			}

			void    openQuote() {}
			void    closeQuote() {}
		};
	}
}


#endif //QUASARFX_JSONSERIALIZER_H
