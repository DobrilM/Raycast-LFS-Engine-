#pragma once
#include <string>
#include <vector>

enum settingsType_t {
	IS_VERBAL,
	FREQUENCY,
	RASTER_X,
	RASTER_Y,
	RAY_X,
	RAY_Y,
	INTENSITY,
	OUTPUT_DIR
};

struct settings_t
{

	bool verbal;
	double frequency;
	int rasterX;
	int rasterY;
	int rayX;
	int rayY;
	int intensity;
	std::string outputDir;	
};

class argumentParse {
	public:
		//set arguments to internal vector
		std::vector<char*> getInput(int argc, char** argv);
		
		settings_t parseSettings(std::vector<char*>& args);
		//assign value to settings
		void assignSetting(settings_t& settings, settingsType_t arg, bool value);
		void assignSetting(settings_t& settings, settingsType_t arg, double value);
		void assignSetting(settings_t& settings, settingsType_t arg, int value);
		void assignSetting(settings_t& settings, settingsType_t arg, const std::string& value);
	private:
		std::vector<char*> args;
		void printHelp();
};
