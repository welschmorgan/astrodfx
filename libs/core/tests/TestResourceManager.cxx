//
// Created by darkboss on 8/1/20.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <core/Resource.h>
#include <core/ResourceFactory.h>
#include <core/ResourceType.h>
#include <core/String.h>
#include <core/ResourceManager.h>
#include "doctest.h"

using quasar::core::SharedResource;
using quasar::core::Resource;
using quasar::core::ResourcePriority;
using quasar::core::ResourceFactory;
using quasar::core::SharedResourceFactoryList;
using quasar::core::ResourceType;
using quasar::core::ResourceStage;
using quasar::core::ResourceManager;
using quasar::core::String;
using quasar::core::Path;
using quasar::core::IStream;
using quasar::core::SharedIOStream;
using quasar::core::OStream;
using quasar::core::StringMap;

class MockResourceFactory: public ResourceFactory {
public:
	MockResourceFactory(const String &name = "Mock", ResourcePriority prio = ResourcePriority::None): ResourceFactory(name, ResourceType::Text, prio) {}
	virtual ~MockResourceFactory() {}

	virtual SharedResource  create(const String &name, const String &path, const StringMap<String> &props, const SharedIOStream &stream) override {
		return std::make_shared<Resource>(this, "test", "tmp:///test", mType, props, stream);
	}
	virtual void            load(Resource &res, IStream &from) override {
	}
	virtual void            save(Resource &res, OStream &to) override {
	}
	virtual void            destroy(Resource &res) override {
	}
};

class MockResourceFactory2: public MockResourceFactory {
public:
	MockResourceFactory2(): MockResourceFactory("Mock(prio = 2)", ResourcePriority::Second) {}
	virtual ~MockResourceFactory2() {}
};

class MockResourceFactory3: public MockResourceFactory {
public:
	MockResourceFactory3(): MockResourceFactory("Mock(prio = 3)", ResourcePriority::Third) {}
	virtual ~MockResourceFactory3() {}
};

TEST_CASE("ResourceManager can be constructed") {
	ResourceManager resMgr;
}

TEST_CASE("ResourceManager can hold factories") {
	ResourceManager resMgr;
	resMgr.addFactory(std::static_pointer_cast<ResourceFactory>(std::make_shared<MockResourceFactory>()));
	REQUIRE(resMgr.getFactories().size() == 1);
	REQUIRE(resMgr.getFactoryByName("Mock") != nullptr);
	REQUIRE(resMgr.getFactoriesByType(ResourceType::Text).size() == 1);
}

TEST_CASE("ResourceManager can sort factories by priority") {
	ResourceManager resMgr;
	SharedResourceFactoryList facs;

	resMgr.addFactory(std::static_pointer_cast<ResourceFactory>(std::make_shared<MockResourceFactory3>()));
	resMgr.addFactory(std::static_pointer_cast<ResourceFactory>(std::make_shared<MockResourceFactory2>()));

	facs = resMgr.getFactoriesByType(ResourceType::Text);

	REQUIRE(facs.size() == 2);
	REQUIRE(facs.front()->getName() == "Mock(prio = 2)");
	REQUIRE(facs.back()->getName() == "Mock(prio = 3)");
}

TEST_CASE("ResourceManager can create resource using factories") {
	ResourceManager resMgr;

	resMgr.addFactory(std::static_pointer_cast<ResourceFactory>(std::make_shared<MockResourceFactory>()));
	auto res = resMgr.createResource("test", ResourceType::Text);

	REQUIRE(res != nullptr);
	REQUIRE(res->getType() == ResourceType::Text);
	REQUIRE(res->getName() == "test");
	REQUIRE(res->getStage() == ResourceStage::Created);
}

TEST_CASE("ResourceManager can load resource using factories") {
	ResourceManager resMgr;

	resMgr.addFactory(std::static_pointer_cast<ResourceFactory>(std::make_shared<MockResourceFactory>()));
	auto res = resMgr.loadResource(Path("test.txt"));

	REQUIRE(res != nullptr);
	REQUIRE(res->getType() == ResourceType::Text);
	REQUIRE(res->getName() == "test");
	REQUIRE(res->getStage() == ResourceStage::Loaded);
}