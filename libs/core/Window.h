//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_WINDOW_H
#define QUASARFX_CORE_WINDOW_H

#include <memory>
#include <vector>
#include "String.h"
#include "Collection.h"
#include "Viewport.h"

namespace quasar {
	namespace core {
		class Window {
		protected:
			String              mName;
			bool                mInitialized;
			SharedViewportList  mViewports;

		public:
			Window(const String &name);
			Window(const Window &rhs) = delete;
			virtual         ~Window() = default;

			Window          &operator=(const Window &rhs) = delete;

			const String    &getName() const noexcept;
			void            setName(const String &name);

			SharedViewport      &addViewport(const SharedViewport &v);
			bool                hasViewport(const String &name) const;
			SharedViewport      getViewport(const String &name) const;
			SharedViewportList  getViewports() const;
			SharedViewport      removeViewport(const String &name);

			virtual bool    isInitialized();

			virtual void    initialize() = 0;
			virtual void    shutdown() = 0;

			virtual void    update(double dt);
		};

		using SharedWindow = std::shared_ptr<Window>;
		using SharedWindowList = std::vector<SharedWindow>;
	}
}
#endif //QUASARFX_CORE_WINDOW_H
