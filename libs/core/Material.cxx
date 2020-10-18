//
// Created by darkboss on 10/4/20.
//

#include "Material.h"

namespace quasar {
	namespace core {
		TextureUnit::TextureUnit(MaterialPass *parent, const String &name)
			: mParent(parent)
			, mId(-1)
			, mName(name)
		{}

		MaterialPass                    *TextureUnit::getParent() noexcept {
			return mParent;
		}
		const MaterialPass              *TextureUnit::getParent() const noexcept {
			return mParent;
		}
		void                            TextureUnit::setParent(MaterialPass *parent) noexcept {
			mParent = parent;
		}

		const String &TextureUnit::getName() const noexcept {
			return mName;
		}

		void TextureUnit::setName(const String &name) noexcept {
			mName = name;
		}

		ssize_t TextureUnit::getId() const noexcept {
			return mId;
		}

		void TextureUnit::setId(ssize_t id) noexcept {
			mId = id;
		}

		const TextureUnit   MaterialPass::DefaultTextureUnit(nullptr, "default");

		MaterialPass::MaterialPass(Material *parent,
								   const String &name,
								   const Color4f &amb, const Color4f &diff, const Color4f &spec,
		                           float shininess)
			: mParent(parent)
			, mId(-1)
			, mName(name)
			, mAmbient(amb)
			, mDiffuse(diff)
			, mSpecular(spec)
			, mShininess(shininess)
			, mTextureUnits()
		{
			initTextureUnits();
		}

		const Color4f &MaterialPass::getAmbient() const {
			return mAmbient;
		}

		void MaterialPass::setAmbient(const Color4f &ambient) {
			mAmbient = ambient;
		}

		const Color4f &MaterialPass::getDiffuse() const {
			return mDiffuse;
		}

		void MaterialPass::setDiffuse(const Color4f &diffuse) {
			mDiffuse = diffuse;
		}

		const Color4f &MaterialPass::getSpecular() const {
			return mSpecular;
		}

		void MaterialPass::setSpecular(const Color4f &specular) {
			mSpecular = specular;
		}

		float MaterialPass::getShininess() const {
			return mShininess;
		}

		void MaterialPass::setShininess(float shininess) {
			mShininess = shininess;
		}

		float MaterialPass::getTransparency() const {
			return 1.0f - getDissolve();
		}

		void MaterialPass::setTransparency(float tr) {
			setDissolve(1.0f - tr);
		}

		float MaterialPass::getDissolve() const {
			return mDiffuse.a;
		}

		void MaterialPass::setDissolve(float d) {
			mDiffuse.a = d;
		}

		Material *MaterialPass::getParent() {
			return mParent;
		}

		const Material *MaterialPass::getParent() const {
			return mParent;
		}

		void MaterialPass::setParent(Material *m) {
			mParent = m;
		}

		String MaterialPass::getParentName() const {
			return mParent ? mParent->getName() : String();
		}

		const SharedTextureUnitList &MaterialPass::getTextureUnits() const {
			return mTextureUnits;
		}

		void MaterialPass::setTextureUnits(const SharedTextureUnitList &units) {
			mTextureUnits = units;
			initTextureUnits();
		}

		SharedTextureUnit MaterialPass::getTextureUnit(const String &name) const {
			auto found = mTextureUnits.find([&](const SharedTextureUnit &u) {
				return u && u->getName() == name;
			});
			if (found == mTextureUnits.end()) {
				throw std::runtime_error("Unknown texture unit '" + name + "' in MaterialPass '" + mName + "' from Material '" + getParentName() + "'");
			}
			return *found;
		}

		SharedTextureUnit MaterialPass::getTextureUnit(ssize_t id) const {
			auto found = mTextureUnits.find([&](const SharedTextureUnit &u) {
				return u && u->getId() == id;
			});
			if (found == mTextureUnits.end()) {
				throw std::runtime_error("Unknown texture unit " + std::to_string(id) + " in MaterialPass '" + mName + "' from Material '" + getParentName() + "'");
			}
			return *found;
		}

		bool MaterialPass::hasTextureUnit(const String &name) const {
			return mTextureUnits.includes([&](const SharedTextureUnit &u) {
				return u && u->getName() == name;
			});
		}

		bool MaterialPass::hasTextureUnit(ssize_t id) const {
			return mTextureUnits.includes([&](const SharedTextureUnit &u) {
				return u && u->getId() == id;
			});
		}

		void MaterialPass::removeTextureUnit(const String &name) {
			mTextureUnits.remove([&](const SharedTextureUnit &u) {
				return u && u->getName() == name;
			});
			initTextureUnits();
		}

		void MaterialPass::removeTextureUnit(ssize_t id) {
			mTextureUnits.remove([&](const SharedTextureUnit &u) {
				return u && u->getId() == id;
			});
			initTextureUnits();
		}

		void MaterialPass::clearTextureUnits() {
			mTextureUnits.clear();
			initTextureUnits();
		}

		void MaterialPass::initTextureUnits() {
			if (mTextureUnits.empty()) {
				mTextureUnits.add(std::make_shared<TextureUnit>(DefaultTextureUnit));
				mTextureUnits->back()->setParent(this);
			}
		}

		const MaterialPass       Material::DefaultPass(
			nullptr,
			"default",
			Color4f(0.0f, 0.0f, 0.0f, 1.0f),
			Color4f(0.8f, 0.8f, 0.8f, 1.0f),
			Color4f(1.0f, 1.0f, 1.0f, 1.0f),
			0.1f
		);

		Material::Material(const Material &rhs)
				: Resource()
				, mPasses()
		{ *this = rhs; }

		Material &Material::operator=(const Material &rhs) {
			Resource::operator=(rhs);
			mPasses = rhs.mPasses;
			initPasses();
			return *this;
		}
		Material::Material()
			: Resource()
			, mPasses()
		{ initPasses(); }

		Material::Material(quasar::core::ResourceFactory *factory, const quasar::core::String &name,
		                   const quasar::core::PropertyMap &properties,
		                   const quasar::core::SharedStream &stream)
			: Resource(factory, name, ResourceType::Material, properties, stream)
			, mPasses()
		{ initPasses(); }

		void                            Material::initPasses() {
			if (mPasses.empty()) {
				mPasses.add(std::make_shared<MaterialPass>(DefaultPass));
				mPasses->back()->setParent(this);
			}
		}

		const SharedMaterialPassList &Material::getPasses() const {
			return mPasses;
		}

		void Material::setPasses(const SharedMaterialPassList &passes) {
			mPasses = passes;
			initPasses();
		}

		bool Material::hasPasses() const {
			return !mPasses.empty();
		}
		bool Material::hasPass(const String &name) const {
			auto found = mPasses.find([&](const SharedMaterialPass &p) {
				return p && p->getName() == name;
			});
			return found != mPasses.end();
		}

		bool Material::hasPass(ssize_t id) const {
			auto found = mPasses.find([&](const SharedMaterialPass &p) {
				return p && p->getId() == id;
			});
			return found != mPasses.end();
		}

		SharedMaterialPass Material::addPass(const SharedMaterialPass &pass) {
			if (!pass) {
				throw std::runtime_error("Cannot add invalid pass to material '" + mName + "'");
			}
			if (hasPass(pass->getName())) {
				throw std::runtime_error("Material '" + mName + "' already contains pass '" + pass->getName() + "' (id = " + std::to_string(pass->getId()) + ")");
			}
			pass->setId(mPasses.size() - 1);
			mPasses.add(pass);
			return mPasses->back();
		}

		void Material::removePass(const String &name) {
			mPasses.remove([&](const SharedMaterialPass &pass) {
				return pass && pass->getName() == name;
			});
			initPasses();
		}

		void Material::removePass(ssize_t id) {
			mPasses.remove([&](const SharedMaterialPass &pass) {
				return pass && pass->getId() == id;
			});
			initPasses();
		}

		const SharedMaterialPass Material::getFirstPass() const {
			return mPasses->front();
		}
		const SharedMaterialPass Material::getLastPass() const {
			return mPasses->back();
		}

		const Color4f                   &Material::getAmbient() const {
			return getFirstPass()->getAmbient();
		}
		void                            Material::setAmbient(const Color4f &ambient) {
			return getFirstPass()->setAmbient(ambient);
		}

		const Color4f                   &Material::getDiffuse() const {
			return getFirstPass()->getDiffuse();
		}
		void                            Material::setDiffuse(const Color4f &diffuse) {
			getFirstPass()->setDiffuse(diffuse);
		}

		const Color4f                   &Material::getSpecular() const {
			return getFirstPass()->getSpecular();
		}
		void                            Material::setSpecular(const Color4f &specular) {
			return getFirstPass()->setSpecular(specular);
		}

		float                           Material::getShininess() const {
			return getFirstPass()->getShininess();
		}
		void                            Material::setShininess(float shininess) {
			getFirstPass()->setShininess(shininess);
		}

		float                           Material::getTransparency() const {
			return getFirstPass()->getTransparency();
		}
		void                            Material::setTransparency(float tr) {
			return getFirstPass()->setTransparency(tr);
		}

		float                           Material::getDissolve() const {
			return getFirstPass()->getDissolve();
		}
		void                            Material::setDissolve(float d) {
			return getFirstPass()->setDissolve(d);
		}

		void Material::clearPasses() {
			mPasses.clear();
			initPasses();
		}
	}
}