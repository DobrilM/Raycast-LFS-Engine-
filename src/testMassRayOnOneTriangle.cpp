#include "utils.hpp"
#include "ray.hpp"
#include "triangle.hpp"
#include <iostream>

int main() {
	soundRayBundle_t rays = ray::generateRays(10,10,vec3<double>(0,0,1), 10.0, 125.0);

	for (int i =0; i < rays.rays.size(); i++) {
		std::cout<< "x:" << rays.rays.at(i).direction.x;
		std::cout<< "y:" << rays.rays.at(i).direction.y;
		std::cout<< "z:" << rays.rays.at(i).direction.z;
		std::cout<< '\n';
	}
	vec3<double> p0 = vec3(1.0,0.0,2.0);
	vec3<double> p1 = vec3(-1.0,1.0,3.0);
	vec3<double> p2 = vec3(-1.0,-1.0,4.0);
	
	triangle_t tri = triangles::generateTriangleManually(p0, p1, p2);
	std::cout << "beginning checking for intersect\n";
	std::cout << "vector count:" << rays.rays.size() << '\n';
	for (int i = 0; i <rays.rays.size(); i++) {
		std::cout << "Vector #" << i << ": ";
		bool intersectsAABB = triangles::rayIntersectsAABB(rays.rays.at(i), tri);
		if (!intersectsAABB) {
			std::cout << "0;0;0,0,0\n";
			continue;
		}
		
		vec3<double> intersection =  triangles::findIntersecRayTriangle(rays.rays.at(i), tri);
		if(intersection.x == 0.0 && intersection.y == 0.0 && intersection.z == 0.0) {
			std::cout << "1;0;0,0,0\n";
			continue;
		} else {
			std::cout << "1;1;" <<intersection.x <<","<< intersection.y <<"," << intersection.z << '\n';
		}
	}

}
