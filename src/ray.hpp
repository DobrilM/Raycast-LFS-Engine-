#pragma once

//includes

#include <vector>
#include "utils.hpp"

struct soundRay_t {
	vec3<double> direction;
	vec3<double> startingPoint;
	double intensity;
	double frequency;
};
struct soundRayBundle_t {
	int row;
	int column;
	std::vector<soundRay_t> ray;
};

class ray {
	public:
		soundRayBundle_t generateRays(	int resolutionX, 
						int resolutionY, 
						std::vector<double> origin, 
						double intensity, 
						double frequency);
		
		void terminateRay(soundRayBundle_t& Rays, int rayIndex);
};
