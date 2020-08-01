//
// Created by darkboss on 8/1/20.
//
#include <render/GLRenderer.h>
#include <render/GLWindow.h>

int main() {
	using namespace quasar::render;
	using namespace quasar::core;
	auto renderer   = std::static_pointer_cast<Renderer>(std::make_shared<GLRenderer>());
	auto window     = renderer->createWindow("hello");
	return 0;
}