//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_VIEWPORT_H
#define QUASARFX_VIEWPORT_H

#include "String.h"
#include "Collection.h"
#include <memory>

namespace quasar {
	namespace core {
		class Viewport {
		protected:
			String          mName;
			bool            mInitialized;

		public:
			Viewport(const String &name = String());
			Viewport(const Viewport &rhs) = delete;
			virtual ~Viewport() noexcept;

			Viewport        &operator=(const Viewport &rhs) = delete;

			const String    &getName() const noexcept;
			void            setName(const String &n);

			bool            isInitialized() const noexcept;

			virtual void    initialize() = 0;
			virtual void    shutdown() = 0;
			virtual void    update(double dt);
		};

		using SharedViewport            = std::shared_ptr<Viewport>;
		using SharedViewportList        = Collection<SharedViewport>;
	}
}

#endif //QUASARFX_VIEWPORT_H