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
			SharedViewport      mActiveViewport;

		public:
			Window(const String &name);
			Window(const Window &rhs) = delete;
			virtual             ~Window() = default;

			Window              &operator=(const Window &rhs) = delete;

			const String        &getName() const noexcept;
			void                setName(const String &name);

			SharedViewport      &addViewport(const SharedViewport &v, bool activate = true) noexcept(false);
			bool                hasViewport(const String &name) const;
			SharedViewport      getViewport(const String &name) const;
			SharedViewport      getViewport(size_t id) const;
			SharedViewportList  getViewports() const;
			SharedViewport      removeViewport(size_t id);
			SharedViewport      removeViewport(const String &name);

			SharedViewport      getActiveViewport() const noexcept;
			void                setActiveViewport(const SharedViewport &vp) noexcept;
			void                setActiveViewport(const String &name);
			void                setActiveViewport(size_t id);

			virtual bool        isInitialized();

			virtual void        initialize() = 0;
			virtual void        shutdown() = 0;

			virtual void        update(double dt);

		protected:
			virtual void        activateViewport(const SharedViewport &vp);
		};

		using SharedWindow = std::shared_ptr<Window>;
		using SharedWindowList = std::vector<SharedWindow>;
	}
}
#endif //QUASARFX_CORE_WINDOW_H
