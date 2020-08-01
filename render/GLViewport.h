//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_RENDER_GLVIEWPORT_H
#define QUASARFX_RENDER_GLVIEWPORT_H

#include <core/Viewport.h>

namespace quasar {
	namespace render {
		class GLViewport: public core::Viewport {
		public:
			GLViewport(const core::String &name);
			GLViewport(const GLViewport &rhs) = delete;
			virtual ~GLViewport() noexcept;

			GLViewport  &operator=(const core::String &name) = delete;

			void        initialize();
			void        shutdown();
		};
	}
}

#endif //QUASARFX_RENDER_GLVIEWPORT_H
