//
// Created by darkboss on 8/1/20.
//
#include <render/GLRenderer.h>
#include <render/GLWindow.h>
#include <iostream>

int main() {
	using namespace quasar::render;
	using namespace quasar::core;
	try {
		auto renderer = std::static_pointer_cast<Renderer>(std::make_shared<GLRenderer>());
		auto window = renderer->createWindow("hello");
	} catch (std::exception &ex) {
		std::cerr << "fatal error: " << ex.what() << std::endl;
	}
	return 0;
}