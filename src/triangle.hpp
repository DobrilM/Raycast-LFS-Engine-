#pragma once
#include <string>
#include "utils.hpp"
#include "ray.hpp"


struct triangle_t {
	vec3<double> normal;
	vec3<double> v0;
	vec3<double> v1;
	vec3<double> v2;
	vec3<double> pMin;
	vec3<double> pMax;
};

struct triangleBundle_t {
	int triangleCount;
	std::vector<triangle_t> triangles;
};

// using the möller-trumbore intersection algorithm


namespace triangles {

	triangleBundle_t loadSTL(std::string filedir);
	bool rayIntersectsAABB(soundRay_t& ray, triangle_t& triangle);
	vec3<double> findIntersecRayTriangle(soundRay_t& ray, triangle_t& triangle);

};
