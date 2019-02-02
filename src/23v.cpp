#include "23v.hpp"


Plugin *plugin;


void init(Plugin *p) {
	plugin = p;
	p->slug = TOSTRING(SLUG);
	p->version = TOSTRING(VERSION);

	p->website = "https://github.com/23volts/vcv-free";
 	p->manual = "https://github.com/23volts/vcv-free/blob/master/README.md";
	// Add all Models defined throughout the plugin
	p->addModel(modelJunctions);
	p->addModel(modelRam);
	p->addModel(modelRoutes);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
