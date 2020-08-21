//
// Created by darkboss on 8/1/20.
//

#include "ResourceType.h"

const std::vector<quasar::core::ResourceType>        quasar::core::ResourceType::All = std::initializer_list<ResourceType> {
	None, Text, Audio, Image, Config, Script, Shader, Material, Model, Scene, Unknown
};

const quasar::core::ResourceType        quasar::core::ResourceType::None = quasar::core::ResourceType(0, T("none"), Collection<PathExt>());
const quasar::core::ResourceType        quasar::core::ResourceType::Text = quasar::core::ResourceType(1, T("text"), Collection<PathExt>({PathExt(".txt"), PathExt(".md")}));
const quasar::core::ResourceType        quasar::core::ResourceType::Audio = quasar::core::ResourceType(2, T("audio"), Collection<PathExt>({PathExt(".ogg"), PathExt(".mp3")}));
const quasar::core::ResourceType        quasar::core::ResourceType::Image = quasar::core::ResourceType(3, T("image"), Collection<PathExt>({PathExt(".bmp"), PathExt(".png"), PathExt(".gif"), PathExt(".jpg"), PathExt(".jpeg")}));
const quasar::core::ResourceType        quasar::core::ResourceType::Config = quasar::core::ResourceType(4, T("config"), Collection<PathExt>({PathExt(".cfg"), PathExt(".ini"), PathExt(".json"), PathExt(".toml")}));
const quasar::core::ResourceType        quasar::core::ResourceType::Script = quasar::core::ResourceType(5, T("script"), Collection<PathExt>());
const quasar::core::ResourceType        quasar::core::ResourceType::Shader = quasar::core::ResourceType(6, T("shader"), Collection<PathExt>({PathExt(".glsl"), PathExt(".hlsl"), PathExt(".vert"), PathExt(".frag"), PathExt(".geom")}));
const quasar::core::ResourceType        quasar::core::ResourceType::Material = quasar::core::ResourceType(7, T("material"), Collection<PathExt>({PathExt(".material")}));
const quasar::core::ResourceType        quasar::core::ResourceType::Model = quasar::core::ResourceType(8, T("model"), Collection<PathExt>({PathExt(".md3"), PathExt(".3ds"), PathExt(".obj")}));
const quasar::core::ResourceType        quasar::core::ResourceType::Scene = quasar::core::ResourceType(9, T("scene"), Collection<PathExt>({PathExt(".scene")}));
const quasar::core::ResourceType        quasar::core::ResourceType::Unknown = quasar::core::ResourceType(10, T("unknown"), Collection<PathExt>());

quasar::core::ResourceType::ResourceType(long v, const quasar::core::String &l,
                                         const Collection<PathExt> &exts)
	: mValue(v), mLabel(l), mExtensions(exts)
{}

bool quasar::core::ResourceType::operator==(const quasar::core::ResourceType &rhs) const noexcept {
	return mValue == rhs.mValue;
}

bool quasar::core::ResourceType::operator!=(const quasar::core::ResourceType &rhs) const noexcept {
	return !(*this == rhs);
}

quasar::core::ResourceType quasar::core::ResourceType::Custom(long value, const quasar::core::String &label,
                                                              const quasar::core::Collection<quasar::core::PathExt> &exts) {
	return quasar::core::ResourceType(value, label, exts);
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

