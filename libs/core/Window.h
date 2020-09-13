//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_WINDOW_H
#define QUASARFX_CORE_WINDOW_H

#include <memory>
#include <vector>
#include <math/Rect.h>
#include "String.h"
#include "Collection.h"

using quasar::math::Rect2f;
using quasar::math::Vec2f;

namespace quasar {
	namespace core {
		class Viewport;
		using SharedViewport = std::shared_ptr<Viewport>;
		using SharedViewportList = Collection<SharedViewport>;

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

			template<typename VPT = Viewport>
			SharedViewport      &createViewport(const String &name, const Rect2f &bounds = Rect2f(), bool activate = true) {
				addViewport(std::shared_ptr(new VPT(this, name, bounds)), activate);
				return mViewports->back();
			}
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
		};

		using SharedWindow = std::shared_ptr<Window>;
		using SharedWindowList = std::vector<SharedWindow>;
	}
}
#endif //QUASARFX_CORE_WINDOW_H
