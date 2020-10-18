//
// Created by darkboss on 9/12/20.
//

#include "formats/wavefront/mtl/MtlGenerator.h"

namespace quasar::formats {
	void MtlGenerator::generate(const quasar::core::Material &item,
	                            MtlGenerator::stream_type &to) {
		to << "# Generated using " << mName << " v" << mVersion << std::endl;
		to << std::endl;
		to << "newmtl " << item.getName() << std::endl;
		to << std::endl;
		to << "Ka " << item.getAmbient().r << " " << item.getAmbient().g << " " << item.getAmbient().b << std::endl;
		to << "Kd " << item.getDiffuse().r << " " << item.getDiffuse().g << " " << item.getDiffuse().b << std::endl;
		to << "Ks " << item.getSpecular().r << " " << item.getSpecular().g << " " << item.getSpecular().b << std::endl;
		to << "Ns " << item.getShininess() << std::endl;
		to << "d "
		   << ((item.getDiffuse().a > 0.0f && item.getDiffuse().a < 1.0f) ? item.getDiffuse().a : item.getAmbient().a)
		   << std::endl;
		to << std::endl;
		to << "illum 2" << std::endl;
		to << std::endl;
	}

	MtlGenerator::MtlGenerator()
		: BasicGenerator("Wavefront MTL", "1.0") {}
}