//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_RENDER_RENDERER_H
# define QUASARFX_RENDER_RENDERER_H

# include <memory>
# include "String.h"
# include "Window.h"

namespace quasar {
	namespace core {
		class Renderer {
		protected:
			String                      mName;
			bool                        mInitialized = false;
			SharedWindowList            mWindows;

		public:
			Renderer() = default;
			Renderer(const Renderer &rhs) = delete;
			virtual ~Renderer() = default;

			Renderer                    &operator=(const Renderer &rhs) = delete;

			virtual void                initialize() = 0;
			virtual void                shutdown() = 0;

			virtual void                update(double dt);

			const String                &getName() const noexcept;
			bool                        isInitialized() const noexcept;

			virtual bool                destroyWindow(SharedWindow &w);
			virtual SharedWindow        &addWindow(const SharedWindow &w);
			virtual SharedWindow        getWindow(const String &name) const;
			virtual SharedWindowList    getWindows() const;
			virtual bool                removeWindow(const String &name);

		};

		using SharedRenderer = std::shared_ptr<Renderer>;
	}
}

#endif //QUASARFX_RENDER_RENDERER_H
