//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_VIEWPORT_H
#define QUASARFX_VIEWPORT_H

#include "String.h"
#include "Collection.h"
#include "Window.h"
#include <memory>
#include <math/Vector.h>
#include <math/Rect.h>

using quasar::math::Rect2f;
using quasar::math::Vec2f;

namespace quasar {
	namespace core {

		class Window;

		class Viewport {
		protected:
			String          mName;
			bool            mInitialized;
			Rect2f          mBounds;
			Window          *mWindow;

		public:
			Viewport(Window *win, const String &name = String(), const Rect2f &bounds = Rect2f(Vec2f::Zero, Vec2f::UnitScale));
			Viewport(const Viewport &rhs) = delete;
			virtual ~Viewport() noexcept;

			Viewport        &operator=(const Viewport &rhs) = delete;

			const String    &getName() const noexcept;
			void            setName(const String &n);

			const Rect2f    getBounds() const noexcept;
			void            setBounds(const Rect2f &bounds) noexcept;

			Window          *getWindow() noexcept;
			const Window    *getWindow() const noexcept;
			void            setWindow(Window *win) noexcept;

			bool            isInitialized() const noexcept;

			virtual void    initialize() = 0;
			virtual void    shutdown() = 0;
			virtual void    activate();
			virtual void    update(double dt);
		};

		using SharedViewport            = std::shared_ptr<Viewport>;
		using SharedViewportList        = Collection<SharedViewport>;
	}
}

#endif //QUASARFX_VIEWPORT_H