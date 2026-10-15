#include <iostream>

#include "ray.hpp"
#include "triangle.hpp"
#include "utils.hpp"


int main() {
	soundRay_t ray;
	ray.direction = vec3(1.0,1.0,1.0);
	ray.startingPoint = vec3(0.0);
	ray.frequency = 11037;
	ray.intensity = 11037;

	vec3<double> p0 = vec3(1.0,0.0,0.0);
	vec3<double> p1 = vec3(0.0,1.0,0.0);
	vec3<double> p2 = vec3(1.22,1.22,1.0);
	
	triangle_t tri = triangles::generateTriangleManually(p0, p1, p2);
	bool isIntersectingAABB = triangles::rayIntersectsAABB(ray, tri);

	std::cout << isIntersectingAABB;

	if (isIntersectingAABB) {
		vec3<double> intersection = triangles::findIntersecRayTriangle(ray, tri);
		
		if (intersection.x == 0.0 && intersection.y == 0.0 && intersection.z == 0.0) {
			std::cout << "No intersection between ray and triangle found";
		} else {
			std::cout << "Intersection found at:" << '\n';
			std::cout << intersection.x << '\n';
			std::cout << intersection.y << '\n';
			std::cout << intersection.z << '\n';
		}
	} else {
		std::cout << "No intersection between ray and AABB";
	}
	
}
