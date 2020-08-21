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
			GLViewport(core::Window *window, const core::String &name, const Rect2f &bounds = Rect2f(Vec2f::Zero, Vec2f::UnitScale));
			GLViewport(const GLViewport &rhs) = delete;
			virtual ~GLViewport() noexcept;

			GLViewport  &operator=(const core::String &name) = delete;

			void        initialize();
			void        activate();
			void        shutdown();
		};
	}
}

#endif //QUASARFX_RENDER_GLVIEWPORT_H
