#include "23v.hpp"


struct Rom : Module {
	enum ParamIds {
		PAGE_PARAM,
		POSITION_PARAM,
		LENGTH_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		PAGE_INPUT,
		POSITION_INPUT,
		LENGTH_INPUT,
		RESET_INPUT,
		TRIG_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		ROM_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		OUTPUT_LIGHT,
		NUM_LIGHTS
	};

	//float phase = 0.0;
	//float blinkPhase = 0.0;
	int page = 0;
	int position = 0;
	int length = 63;
	float rom[1024];
	SchmittTrigger trigTrigger;
	SchmittTrigger resetTrigger;
	float outputLight = 0.0f;

	Rom() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
	void step() override;
	void onReset() override;
	void onRandomize() override;
	json_t *toJson() override;
	void fromJson(json_t *rootJ) override;
	
	// For more advanced Module features, read Rack's engine.hpp header file
	// - toJson, fromJson: serialization of internal data
	// - onSampleRateChange: event triggered by a change of sample rate
	// - onReset, onRandomize, onCreate, onDelete: implements special behavior when user clicks these from the context menu
};

// This is called when user click on "initialize"
void onReset() override {
	//
}

// This is called when user click on "randomize"
void onRandomize() override {
	// In the module context, we could shuffle the whole ROM 
}

// Serialize module patch to json
json_t *toJson() override {
	json_t *rootJ = json_object();

	/*// isVoid
	json_object_set_new(rootJ, "isVoid0", json_real(isVoid[0]));
	json_object_set_new(rootJ, "isVoid1", json_real(isVoid[1]));
	
	// isReverse
	json_object_set_new(rootJ, "isReverse0", json_real(isReverse[0]));
	json_object_set_new(rootJ, "isReverse1", json_real(isReverse[1]));
	
	// isRandom
	json_object_set_new(rootJ, "isRandom0", json_real(isRandom[0]));
	json_object_set_new(rootJ, "isRandom1", json_real(isRandom[1]));
	
	// panelTheme
	json_object_set_new(rootJ, "panelTheme", json_integer(panelTheme));

	// cvMode
	json_object_set_new(rootJ, "cvMode", json_integer(cvMode));*/

	return rootJ;
}

// Retrieve Module context from Json
void fromJson(json_t *rootJ) override {
	/*// isVoid
	json_t *isVoid0J = json_object_get(rootJ, "isVoid0");
	if (isVoid0J)
		isVoid[0] = json_number_value(isVoid0J);
	json_t *isVoid1J = json_object_get(rootJ, "isVoid1");
	if (isVoid1J)
		isVoid[1] = json_number_value(isVoid1J);

	// isReverse
	json_t *isReverse0J = json_object_get(rootJ, "isReverse0");
	if (isReverse0J)
		isReverse[0] = json_number_value(isReverse0J);
	json_t *isReverse1J = json_object_get(rootJ, "isReverse1");
	if (isReverse1J)
		isReverse[1] = json_number_value(isReverse1J);

	// isRandom
	json_t *isRandom0J = json_object_get(rootJ, "isRandom0");
	if (isRandom0J)
		isRandom[0] = json_number_value(isRandom0J);
	json_t *isRandom1J = json_object_get(rootJ, "isRandom1");
	if (isRandom1J)
		isRandom[1] = json_number_value(isRandom1J);

	// panelTheme
	json_t *panelThemeJ = json_object_get(rootJ, "panelTheme");
	if (panelThemeJ)
		panelTheme = json_integer_value(panelThemeJ);

	// cvMode
	json_t *cvModeJ = json_object_get(rootJ, "cvMode");
	if (cvModeJ)
		cvMode = json_integer_value(cvModeJ);

	posA = 0;// no need to check isVoid here, will be checked in step()
	posB = 0;// no need to check isVoid here, will be checked in step()
	posAnext = (posA + (isReverse[0] ? 7 : 1)) % 8;// no need to check isVoid here, will be checked in step()
	posBnext = (posB + (isReverse[1] ? 7 : 1)) % 8;// no need to check isVoid here, will be checked in step()*/
}


void Rom::step() {
	/*// Implement a simple sine oscillator
	float deltaTime = engineGetSampleTime();

	// Compute the frequency from the pitch parameter and input
	float pitch = params[PITCH_PARAM].value;
	pitch += inputs[PITCH_INPUT].value;
	pitch = clamp(pitch, -4.0f, 4.0f);
	// The default pitch is C4
	float freq = 261.626f * powf(2.0f, pitch);

	// Accumulate the phase
	phase += freq * deltaTime;
	if (phase >= 1.0f)
		phase -= 1.0f;

	// Compute the sine output
	float sine = sinf(2.0f * M_PI * phase);
	outputs[SINE_OUTPUT].value = 5.0f * sine;

	// Blink light at 1Hz
	blinkPhase += deltaTime;
	if (blinkPhase >= 1.0f)
		blinkPhase -= 1.0f;
	lights[BLINK_LIGHT].value = (blinkPhase < 0.5f) ? 1.0f : 0.0f;*/
}


struct RomWidget : ModuleWidget {
	RomWidget(Rom *module) : ModuleWidget(module) {
		/*setPanel(SVG::load(assetPlugin(plugin, "res/MyModule.svg")));

		addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(Widget::create<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(Widget::create<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(ParamWidget::create<Davies1900hBlackKnob>(Vec(28, 87), module, Ram::PITCH_PARAM, -3.0, 3.0, 0.0));

		addInput(Port::create<PJ301MPort>(Vec(33, 186), Port::INPUT, module, Ram::PITCH_INPUT));

		addOutput(Port::create<PJ301MPort>(Vec(33, 275), Port::OUTPUT, module, Ram::SINE_OUTPUT));

		addChild(ModuleLightWidget::create<MediumLight<RedLight>>(Vec(41, 59), module, Ram::BLINK_LIGHT));*/
	}
};


// Specify the Module and ModuleWidget subclass, human-readable
// author name for categorization per plugin, module slug (should never
// change), human-readable module name, and any number of tags
// (found in `include/tags.hpp`) separated by commas.
Model *modelRom = Model::create<Rom, RamWidget>("23v", "ROM", "ROM", SEQUENCER_TAG);
