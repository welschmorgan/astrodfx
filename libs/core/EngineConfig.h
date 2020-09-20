//
// Created by darkboss on 9/19/20.
//

#ifndef QUASARFX_ENGINECONFIG_H
#define QUASARFX_ENGINECONFIG_H


#include "Config.h"
#include "LoggingConfig.h"
#include "Color.h"

namespace quasar {
	namespace core {

		class ViewportConfig: public ConfigNode {
		public:

			static const ConfigNode        &Schema() {
				static const ConfigNode schema(nullptr, "viewport", {}, {
					{"clear_color", "rgba(128, 128, 128, 255)"}
				});
				return schema;
			}
			static const ViewportConfig    &Defaults() {
				static const ViewportConfig defaults(Schema());
				return defaults;
			}

		public:
			ViewportConfig();
			ViewportConfig(const ViewportConfig &cfg) = default;
			explicit ViewportConfig(const ConfigNode &cfg);
			virtual ~ViewportConfig() = default;

			ViewportConfig                  &operator=(const ViewportConfig &cfg) = default;
			ViewportConfig                  &operator=(const ConfigNode &cfg);

			ViewportConfig                  &setClearColor(const Color4uc &col);
			Color4uc                        getClearColor() const;
		};

		class RenderingConfig: public ConfigNode {
		public:
			static const ConfigNode         &Schema() {
				static const ConfigNode schema(nullptr, "rendering", {
					ConfigNode{nullptr, "viewports", {
						{ViewportConfig::Schema().merged(ConfigNode(nullptr, "main"))}
					}},
				});
				return schema;
			};
			static const RenderingConfig    &Defaults() {
				static const RenderingConfig defaults(Schema());
				return defaults;
			}

		public:
			RenderingConfig();
			RenderingConfig(const RenderingConfig &cfg) = default;
			explicit RenderingConfig(const ConfigNode &cfg);
			virtual ~RenderingConfig() = default;

			RenderingConfig                 &operator=(const RenderingConfig &cfg) = default;
			RenderingConfig                 &operator=(const ConfigNode &cfg);

			RenderingConfig                 &setViewports(const Vector<ViewportConfig> &vps);
			Vector<ViewportConfig>          getViewports() const;
		};

		class EngineConfig: public ConfigNode {
		public:
			static const ConfigNode     &Schema() {
				static const ConfigNode schema(nullptr, "engine", {
					RenderingConfig::Schema(),
					LoggingConfig::Schema()
				}, {});
				return schema;
			};
			static const EngineConfig   &Defaults() {
				static const EngineConfig defaults(Schema());
				return defaults;
			}

		public:
			EngineConfig();
			EngineConfig(const EngineConfig &cfg) = default;
			explicit EngineConfig(const ConfigNode &cfg);
			virtual ~EngineConfig() = default;

			EngineConfig            &operator=(const EngineConfig &cfg) = default;
			EngineConfig            &operator=(const ConfigNode &cfg);

			const LoggingConfig     &getLogging() const;
			LoggingConfig           &getLogging();
			EngineConfig            &setLogging(const LoggingConfig &c);

			EngineConfig            &setRendering(const RenderingConfig &col);
			RenderingConfig         &getRendering();
			const RenderingConfig   &getRendering() const;
		};
	}
}

#endif //QUASARFX_ENGINECONFIG_H
