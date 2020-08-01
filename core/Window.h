//
// Created by darkboss on 8/1/20.
//

#ifndef QUASARFX_CORE_WINDOW_H
#define QUASARFX_CORE_WINDOW_H

#include <memory>
#include "String.h"

namespace quasar {
	namespace core {
		class Window {
		protected:
			String          mName;

		public:
			Window(const String &name);
			Window(const Window &rhs) = delete;
			virtual         ~Window() = default;

			Window          &operator=(const Window &rhs) = delete;

			const String    &getName() const noexcept;
			void            setName(const String &name);

			virtual void    initialize() = 0;
			virtual void    update() = 0;
		};

		using SharedWindow = std::shared_ptr<Window>;
	}
}
#endif //QUASARFX_CORE_WINDOW_H
