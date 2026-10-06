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
	std::vector<soundRay_t> rays;
};

class ray {
	public:
		soundRayBundle_t generateRays(	int resolutionX,
						int resolutionY, 
						vec3<double> origin, 
						double intensity, 
						double frequency);
		
		void rayIntersection(soundRayBundle_t& bundle, int rayIndex,vec3<double> intersection, vec3<double> normalVec);
		void terminateRay(soundRayBundle_t& bundle, int rayIndex);
};
