//
// Created by darkboss on 10/4/20.
//

#ifndef QUASARFX_MATERIAL_H
#define QUASARFX_MATERIAL_H

#include "Resource.h"
#include "Pointers.h"
#include "Color.h"
#include "Lexer.h"
#include "Parser.h"

namespace quasar {
	namespace core {
		class MaterialPass;
		class TextureUnit {
			MaterialPass                    *mParent;
			ssize_t                         mId;
			String                          mName;
		public:
			TextureUnit(MaterialPass *parent = nullptr, const String &name = String());
			TextureUnit(const TextureUnit &rhs) = default;
			virtual ~TextureUnit() noexcept = default;

			TextureUnit                     &operator=(const TextureUnit &rhs) = default;

			const String                    &getName() const noexcept;
			void                            setName(const String &name) noexcept;

			MaterialPass                    *getParent() noexcept;
			const MaterialPass              *getParent() const noexcept;
			void                            setParent(MaterialPass *parent) noexcept;

			ssize_t                         getId() const noexcept;
			void                            setId(ssize_t id) noexcept;
		};

		using SharedTextureUnit = SharedPtr<TextureUnit>;
		using SharedTextureUnitList = Collection<SharedTextureUnit>;

		class Material;

		class MaterialPass {
		public:
			static const TextureUnit        DefaultTextureUnit;

		protected:
			Material                        *mParent;
			ssize_t                         mId;
			String                          mName;
			Color4f                         mAmbient;
			Color4f                         mDiffuse;
			Color4f                         mSpecular;
			float                           mShininess;
			SharedTextureUnitList           mTextureUnits;

		public:
			MaterialPass(Material *parent, const String &name = String(), const Color4f &amb = Color4f(), const Color4f &diff = Color4f(), const Color4f &spec = Color4f(), float shininess = 1.0f);
			MaterialPass(const MaterialPass &rhs) = default;
			virtual                         ~MaterialPass() noexcept = default;

			MaterialPass                    &operator=(const MaterialPass &rhs) = default;

			const String                    &getName() const noexcept { return mName; }
			void                            setName(const String &name) noexcept { mName = name; }

			String                          getParentName() const;
			Material                        *getParent();
			const Material                  *getParent() const;
			void                            setParent(Material *m);

			ssize_t                         getId() const noexcept { return mId; }
			void                            setId(ssize_t id) noexcept { mId = id; }

			const SharedTextureUnitList     &getTextureUnits() const;
			void                            setTextureUnits(const SharedTextureUnitList &units);
			SharedTextureUnit               getTextureUnit(const String &name) const;
			SharedTextureUnit               getTextureUnit(ssize_t id) const;
			bool                            hasTextureUnit(const String &name) const;
			bool                            hasTextureUnit(ssize_t id) const;
			void                            removeTextureUnit(const String &name);
			void                            removeTextureUnit(ssize_t id);
			void                            clearTextureUnits();

			const Color4f                   &getAmbient() const;
			void                            setAmbient(const Color4f &ambient);

			const Color4f                   &getDiffuse() const;
			void                            setDiffuse(const Color4f &diffuse);

			const Color4f                   &getSpecular() const;
			void                            setSpecular(const Color4f &specular);

			float                           getShininess() const;
			void                            setShininess(float shininess);

			float                           getTransparency() const;
			void                            setTransparency(float tr);

			float                           getDissolve() const;
			void                            setDissolve(float d);

		protected:
			void                            initTextureUnits();
		};

		using SharedMaterialPass            = SharedPtr<MaterialPass>;
		using SharedMaterialPassList        = Collection<SharedMaterialPass>;

		class Material: public Resource {
		public:
			static const MaterialPass       DefaultPass;

		protected:
			Material(const Material &rhs);
			Material                        &operator=(const Material &rhs);

		protected:
			SharedMaterialPassList          mPasses;

		public:
			Material();
			Material(ResourceFactory *factory, const String &name, const PropertyMap &properties = PropertyMap(), const SharedStream &stream = SharedStream());
			virtual ~Material() = default;

			const Color4f                   &getAmbient() const;
			void                            setAmbient(const Color4f &ambient);

			const Color4f                   &getDiffuse() const;
			void                            setDiffuse(const Color4f &diffuse);

			const Color4f                   &getSpecular() const;
			void                            setSpecular(const Color4f &specular);

			float                           getShininess() const;
			void                            setShininess(float shininess);

			float                           getTransparency() const;
			void                            setTransparency(float tr);

			float                           getDissolve() const;
			void                            setDissolve(float d);

			const SharedMaterialPassList    &getPasses() const;
			void                            setPasses(const SharedMaterialPassList &passes);
			const SharedMaterialPass        getFirstPass() const;
			const SharedMaterialPass        getLastPass() const;
			bool                            hasPasses() const;
			bool                            hasPass(const String &name) const;
			bool                            hasPass(ssize_t id) const;
			template<typename ...Args>
			SharedMaterialPass              createPass(Args ...args) {
				return addPass(std::make_shared(std::forward(args...)));
			}
			SharedMaterialPass              addPass(const SharedMaterialPass &pass);
			void                            removePass(const String &name);
			void                            removePass(ssize_t id);
			void                            clearPasses();

		protected:
			void                            initPasses();

		protected:
			friend class                    BasicParser<Char, Material, BasicLexer<Char, BasicToken<Char>>>;
		};

		using SharedMaterial        = SharedPtr<Material>;
		using SharedMaterialList    = Collection<SharedMaterial>;
	}
}

#endif //QUASARFX_MATERIAL_H
