//
// Created by darkboss on 8/1/20.
//
#include <render/GLRenderer.h>
#include <render/GLWindow.h>
#include <iostream>
#include <core/ResourceManager.h>
#include <formats/text/Text.h>
#include <formats/text/TextFactory.h>

// Define a custome "any resource" type
static ResourceType AnyResourceType = ResourceType::Custom(424242, "AnyResource", quasar::core::Collection<PathExt>(std::initializer_list<PathExt>({PathExt("*")})));

// Factory that creates any resource
class AnyResourceFactory : public ResourceFactory {
public:
	AnyResourceFactory(): ResourceFactory("Any", AnyResourceType, ResourcePriority::First) {}
	AnyResourceFactory(const AnyResourceFactory &rhs) = delete;
	virtual ~AnyResourceFactory() noexcept = default;

	AnyResourceFactory                 &operator=(const AnyResourceFactory &rhs) = delete;

	virtual SharedResource              create(const String &name, const String &path, const StringMap<String> &properties) {
		return SharedResource(new quasar::formats::Text(this, name, path, AnyResourceType));
	}
	virtual void                        destroy(Resource &res) {
	}
};

int main() {
	using namespace quasar::core;
	using namespace quasar::formats;

	ResourceManager resMgr;

	try {
		// add discoverable location
		resMgr.addLocation(Path("."));

		// add factory to load resources
		resMgr.addFactory(std::make_shared<AnyResourceFactory>());

		// discover all resources
		resMgr.discoverResources();
	} catch (std::exception &ex) {
		std::cerr << "fatal error: " << ex.what() << std::endl;
	}

	for (auto &res: resMgr.getResources()) {
		std::cout << "+ Found '" << res->getName() << "'" << std::endl;
	}
	return 0;
}