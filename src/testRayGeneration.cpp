#include "utils.hpp"
#include "ray.hpp"
#include <iostream>

int main() {
	soundRayBundle_t rays = ray::generateRays(10,10,vec3<double>(0), 10.0, 125.0);

	for (int i =0; i < rays.rays.size(); i++) {
		std::cout<< "x:" << rays.rays.at(i).direction.x;
		std::cout<< "y:" << rays.rays.at(i).direction.y;
		std::cout<< "z:" << rays.rays.at(i).direction.z;
		std::cout<< '\n';
	}

	
	return 0;

}
