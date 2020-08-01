//
// Created by darkboss on 8/1/20.
//

#include "ResourceType.h"

const std::vector<quasar::core::ResourceType>        quasar::core::ResourceType::All = std::initializer_list<ResourceType> {
	None, Text, Audio, Image, Config, Script, Shader, Material, Model, Scene, Unknown
};

const quasar::core::ResourceType        quasar::core::ResourceType::None = quasar::core::ResourceType(0, T("none"), quasar::core::StringVector());
const quasar::core::ResourceType        quasar::core::ResourceType::Text = quasar::core::ResourceType(1, T("text"), quasar::core::StringVector({".txt", ".md"}));
const quasar::core::ResourceType        quasar::core::ResourceType::Audio = quasar::core::ResourceType(2, T("audio"), quasar::core::StringVector({".ogg", ".mp3"}));
const quasar::core::ResourceType        quasar::core::ResourceType::Image = quasar::core::ResourceType(3, T("image"), quasar::core::StringVector({".bmp", ".png", ".gif", ".jpg", ".jpeg"}));
const quasar::core::ResourceType        quasar::core::ResourceType::Config = quasar::core::ResourceType(4, T("config"), quasar::core::StringVector({".cfg", ".ini", ".json", ".toml"}));
const quasar::core::ResourceType        quasar::core::ResourceType::Script = quasar::core::ResourceType(5, T("script"), quasar::core::StringVector());
const quasar::core::ResourceType        quasar::core::ResourceType::Shader = quasar::core::ResourceType(6, T("shader"), quasar::core::StringVector({".glsl", ".hlsl", ".vert", "frag", ".geom"}));
const quasar::core::ResourceType        quasar::core::ResourceType::Material = quasar::core::ResourceType(7, T("material"), quasar::core::StringVector({".material"}));
const quasar::core::ResourceType        quasar::core::ResourceType::Model = quasar::core::ResourceType(8, T("model"), quasar::core::StringVector({".md3", ".3ds", ".obj"}));
const quasar::core::ResourceType        quasar::core::ResourceType::Scene = quasar::core::ResourceType(9, T("scene"), quasar::core::StringVector({".scene"}));
const quasar::core::ResourceType        quasar::core::ResourceType::Unknown = quasar::core::ResourceType(10, T("unknown"), quasar::core::StringVector());

quasar::core::ResourceType::ResourceType(long v, const quasar::core::String &l,
                                         const std::vector<quasar::core::String> &exts)
	: mValue(v), mLabel(l), mExtensions(exts)
{}

bool quasar::core::ResourceType::operator==(const quasar::core::ResourceType &rhs) const noexcept {
	return mValue == rhs.mValue;
}

bool quasar::core::ResourceType::operator!=(const quasar::core::ResourceType &rhs) const noexcept {
	return !(*this == rhs);
}

quasar::core::OStream                 &operator<<(quasar::core::OStream &os, const quasar::core::ResourceType &rt) {
	return os << rt.getLabel();
}

quasar::core::IStream                 &operator>>(quasar::core::IStream &is, quasar::core::ResourceType &rt) {
	quasar::core::String                word;
	quasar::core::StringStream          ss2i;
	long                                s2i;

	is >> word;
	ss2i.clear();
	ss2i << word;
	ss2i >> s2i;

	for (auto t: quasar::core::ResourceType::All) {
		if (word == t.getLabel() || s2i == t.getCode()) {
			rt = quasar::core::ResourceType(t);
			break;
		}
	}

	return is;
}

