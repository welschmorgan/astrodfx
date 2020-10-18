//
// Created by darkboss on 9/12/20.
//

#include "formats/wavefront/mtl/MtlGenerator.h"
#include "MtlGenerator.h"

#include <iomanip>

namespace quasar::formats {
	MtlGenerator::MtlGenerator()
		: BasicGenerator("Wavefront MTL", "1.0")
		, mTextureTypesToStatements({
            {TT_NONE, ""},
            {TT_AMBIENT, "map_Ka"},
            {TT_DIFFUSE, "map_Kd"},
            {TT_SPECULAR, "map_Ks"},
            {TT_SHININESS, "map_Ns"},
            {TT_ALPHA, "map_d"},
            {TT_BUMP, "bump"},
            {TT_DISPLACEMENT, "disp"},
            {TT_DECAL, "decal"},
            {TT_REFLECTION, "refl"}
		})
		, mTextureNameToTypes()
	{}

	void MtlGenerator::generate(const quasar::core::Material &item,
	                            MtlGenerator::stream_type &to) {
		to << "# Generated using " << mName << " v" << mVersion << std::endl;
		generatePass(&item, nullptr, to);
		for (auto const& pass: item.getPasses()) {
			to << std::endl;
			generatePass(&item, pass.get(), to);
		}
	}

	void MtlGenerator::generatePass(const core::Material *mat, const core::MaterialPass *pass, stream_type &to) {
		to << "# material " << mat->getName() << std::endl;
		to << "newmtl " << mat->getName();
		if (pass == nullptr) {
			pass = mat->getFirstPass().get();
		} else {
			to << ":" << pass->getName();
		}
		to << std::endl;
		if (pass == nullptr) {
			throw std::runtime_error("cannnot generate invalid material pass from material '" + mat->getName() + "'");
		}
		to << std::endl;
		to << "Ka " << pass->getAmbient().r << " " << pass->getAmbient().g << " " << pass->getAmbient().b << std::endl;
		to << "Kd " << pass->getDiffuse().r << " " << pass->getDiffuse().g << " " << pass->getDiffuse().b << std::endl;
		to << "Ks " << pass->getSpecular().r << " " << pass->getSpecular().g << " " << pass->getSpecular().b
		   << std::endl;
		to << "Ns " << pass->getShininess() << std::endl;
		to << "d " << pass->getDiffuse().a << std::endl;
		to << std::endl;
		to << "illum 2" << std::endl;
		if (!pass->getTextureUnits().empty()) {
			to << std::endl;
			for (auto const &texUnit: pass->getTextureUnits()) {
				if (texUnit->getTexture()) {
					auto texType = getTextureType(texUnit->getTexture()->getName());
					if (texType != TT_NONE) {
						auto statement = mTextureTypesToStatements.at(texType);
						to << "# texture unit " << texUnit->getId() << ": " << texUnit->getName() << std::endl;
						to << statement << " " << texUnit->getTexture()->getName() << std::endl;
					}
				}
			}
		}
	}

	MtlGenerator::TextureTypeToStatementMap MtlGenerator::getTextureTypesToStatements() const {
		return mTextureTypesToStatements;
	}

	MtlGenerator::TextureNameToTypeMap MtlGenerator::getTextureNameToTypes() const {
		return mTextureNameToTypes;
	}

	void MtlGenerator::setTextureNameToType(const core::String &name, MtlGenerator::TextureType type) {
		mTextureNameToTypes.put(name, type);
	}

	MtlGenerator::TextureType MtlGenerator::getTextureType(const core::String &name) {
		auto texType = mTextureNameToTypes->find(name);
		if (texType != mTextureNameToTypes.end()) {
			return texType->second;
		}
		return TT_NONE;
	}

}