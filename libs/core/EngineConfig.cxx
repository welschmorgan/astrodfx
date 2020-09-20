//
// Created by darkboss on 9/19/20.
//

#include "EngineConfig.h"

namespace quasar {
	namespace core {
		ViewportConfig::ViewportConfig()
			: ConfigNode()
		{
			mSchema = &Schema();
			*this = Defaults();
		}

		ViewportConfig::ViewportConfig(const ConfigNode &cfg)
			: ConfigNode()
		{
			mSchema = &Schema();
			*this = cfg;
		}

		ViewportConfig &ViewportConfig::operator=(const ConfigNode &cfg) {
			ConfigNode::operator=(cfg);
			validate();
			return *this;
		}

		ViewportConfig &ViewportConfig::setClearColor(const Color4uc &col) {
			getChild("viewport")->setProperty("clear_color", col);
			return *this;
		}

		Color4uc ViewportConfig::getClearColor() const {
			return getChild("viewport")->getProperty<Color4uc>("clear_color");
		}


		RenderingConfig::RenderingConfig()
			: ConfigNode()
		{
			mSchema = &Schema();
			*this = Defaults();
		}

		RenderingConfig::RenderingConfig(const ConfigNode &cfg)
			: ConfigNode()
		{
			mSchema = &Schema();
			*this = cfg;
		}

		RenderingConfig &RenderingConfig::operator=(const ConfigNode &cfg) {
			ConfigNode::operator=(cfg);
			validate();
			return *this;
		}

		RenderingConfig &RenderingConfig::setViewports(const Vector<ViewportConfig> &vps) {
			auto viewportsNode = getChild("viewports");
			for (auto const& vp: vps) {
				viewportsNode->setChild(vp.getName(), vp);
			}
			return *this;
		}

		Vector<ViewportConfig> RenderingConfig::getViewports() const {
			auto viewportsNode = getChild("viewports");
			Vector<ViewportConfig> ret;
			for (auto const& viewportNode: viewportsNode->getChildren()) {
				ret.add(static_cast<const ViewportConfig&>(viewportNode));
			}
			return ret;
		}

		EngineConfig::EngineConfig()
			: ConfigNode()
		{
			mSchema = &Schema();
			*this = Defaults();
		}

		EngineConfig::EngineConfig(const ConfigNode &cfg)
			: ConfigNode()
		{
			mSchema = &Schema();
			*this = cfg;
		}

		EngineConfig &EngineConfig::operator=(const ConfigNode &cfg) {
			ConfigNode::operator=(cfg);
			validate();
			return *this;
		}

		const LoggingConfig &EngineConfig::getLogging() const {
			return static_cast<const LoggingConfig&>(*getChild("logging"));
		}

		LoggingConfig &EngineConfig::getLogging() {
			return static_cast<LoggingConfig&>(*getChild("logging"));
		}

		EngineConfig &EngineConfig::setLogging(const LoggingConfig &c) {
			setChild("logging", c);
			return *this;
		}

		EngineConfig &EngineConfig::setRendering(const RenderingConfig &c) {
			setChild("rendering", c);
			return *this;
		}

		RenderingConfig &EngineConfig::getRendering() {
			return static_cast<RenderingConfig&>(*getChild("rendering"));
		}

		const RenderingConfig &EngineConfig::getRendering() const {
			return static_cast<const RenderingConfig&>(*getChild("rendering"));
		}
	}
}