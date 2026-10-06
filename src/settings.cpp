
#include "settings.hpp"
#include <string>
#include <iostream>
std::vector<char*> argumentParse::getInput(int argc, char** argv) {
	std::vector<char*> args = {};

	for (int i =0; i<argc; i++) {
		args.push_back(argv[i]);
	}
	return args;
}

settings_t argumentParse::parseSettings(std::vector<char*>&args) {
	//default settings
	settings_t settings = {
		true, //is_verbal
		100.0f,	//frequency
		1000,	//rosterX
		1000,	//rosterY
		100,	//rayX
		100,	//rayY
		80,	//intensity
		"./output/"	//output dir
	};

	for (int i=0; i < args.size(); i++) {
		if (args.at(i)[0] == '-'){
			switch (args.at(i)[1]) {
				case 'h': printHelp(); break; 
				case 'f': assignSetting(settings, FREQUENCY , std::stod(args.at(i+1))) ; break;
				case 'v': assignSetting(settings, IS_VERBAL, true); break;
				case 'm': assignSetting(settings, RASTER_X, std::stoi(args.at(i+1)));
					  assignSetting(settings, RASTER_Y, std::stoi(args.at(i+2))); break;
				case 'r': assignSetting(settings, RAY_X, std::stoi(args.at(i+1)));
					  assignSetting(settings, RAY_Y, std::stoi(args.at(i+2))); break;
				case 'i': assignSetting(settings, INTENSITY, std::stod(args.at(i+1))); break;
				case 'o': assignSetting(settings, OUTPUT_DIR, args.at(i+1)); break;
				default: std::cout << "using default settings (not verbose)";
			}
		}
	}

	return settings;
}
// overloading of the assignSetting based on type
   void argumentParse::assignSetting(settings_t& s, settingsType_t arg, bool value) {
        switch (arg) {
            case IS_VERBAL: s.verbal = value; break;
            default: /* error or ignore */ break;
        }
    }

    void argumentParse::assignSetting(settings_t& s, settingsType_t arg, double value) {
        switch (arg) {
            case FREQUENCY: s.frequency = value; break;
            case INTENSITY: s.intensity = value; break;
            default: /* error */ break;
        }
    }

    void argumentParse::assignSetting(settings_t& s, settingsType_t arg, int value) {
        switch (arg) {
            case RASTER_X: s.rasterX= value; break;
            case RASTER_Y: s.rasterY= value; break;
            case RAY_X: s.rayX= value; break;
            case RAY_Y: s.rayY= value; break;
            default: /* error */ break;
        }
    }

    void argumentParse::assignSetting(settings_t& s, settingsType_t arg, const std::string& value) {
        switch (arg) {
            case OUTPUT_DIR: s.outputDir= value; break;
            default: /* error */ break;
        }
    }

