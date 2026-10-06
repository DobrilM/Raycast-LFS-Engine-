#include "utils.hpp"

double phys::dBtoWm2(double intensity) {
	return 1e-12 * pow(10, intensity/10);
}

double phys::Wm2todB(double intensitydB) {
	return 10*std::log(intensitydB/1e-12);
}

vec3<double> phys::calcRefraction(vec3<double> direction) {
	vec3 refractedDirection;
	return refractedDirection;
}

