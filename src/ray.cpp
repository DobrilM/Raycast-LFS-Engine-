#include "ray.hpp"

soundRayBundle_t ray::generateRays(int resolutionX, int resolutionY, vec3<double> origin, double intensity, double frequency) {
	std::vector<soundRay_t> rays;
	

	double intensityWm2 = phys::dBtoWm2(intensity);
	for (int i =0; i < resolutionY; i++) {
		for (int j=0; i<resolutionX; j++) {
			soundRay_t tempRay;
			//x from -0.5 to 0.5
			double positionX = (i*1.0f/(resolutionX*1.0f)) - 0.5f;
			//y from 0.5 to -0.5 (top left corner to bottom right)
			double positionY = 0.5f - (j*1.0f/(resolutionY*1.0f));
			rays.push_back(soundRay_t{
				vec3<double>(positionX, positionY, 1.0),
				vec3<double>(0, 0, 0),
				intensityWm2,
				frequency
			});
		}
	}

	soundRayBundle_t bundle = {resolutionX, resolutionY, rays};
	

	return bundle;	 

}


void ray::rayIntersection(soundRayBundle_t& bundle, int rayIndex,vec3<double> intersection, vec3<double> normalVec) {
	soundRay_t tempRay = bundle.rays.at(rayIndex);
	
	double distance = vec3(intersection - tempRay.startingPoint).length();
	
	//tempRay.intensity -= util::calcLostIntensityDistance(distance)
	//tempRay.intensity -= util::calcLostIntensityReflection(normalVec)
	
	tempRay.startingPoint = intersection;
	tempRay.direction = phys::calcRefraction(tempRay.direction);
	bundle.rays.at(rayIndex) = tempRay;
}
