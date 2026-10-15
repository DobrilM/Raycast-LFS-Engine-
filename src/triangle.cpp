#include<ios>
#include<fstream>
#include<cstdint>
#include "triangle.hpp"
#include "ray.hpp"
#include<iostream>
triangle_t triangles::generateTriangleManually(vec3<double> p0, vec3<double> p1, vec3<double> p2) {
	triangle_t tri;

	tri.v0 = p0;
	tri.v1 = p1;
	tri.v2 = p2;

	vec3<double> ab = p1-p0;
	vec3<double> ac = p2-p0;

	vec3<double> crossAtPointA = ab%ac;
	tri.normal = crossAtPointA/crossAtPointA.length();

	tri.pMax = vec3<double>(
		std::max(tri.v0.x, std::max(tri.v1.x, tri.v2.x)),
		std::max(tri.v0.y, std::max(tri.v1.y, tri.v2.y)),
		std::max(tri.v0.z, std::max(tri.v1.z, tri.v2.z))
	);

	tri.pMin = vec3<double>(
		std::min(tri.v0.x, std::min(tri.v1.x, tri.v2.x)),
		std::min(tri.v0.y, std::min(tri.v1.y, tri.v2.y)),
		std::min(tri.v0.z, std::min(tri.v1.z, tri.v2.z))
	);
	return tri;


}
triangleBundle_t triangles::loadSTL(std::string filename) {

	std::ifstream stl;
	stl.open(filename, std::ios::in| std::ios::binary);
	stl.seekg(80, std::ios::beg);
	uint32_t count = 0;
	stl.read(reinterpret_cast<char*>(&count), sizeof(count));

	triangleBundle_t bundle;
	bundle.triangleCount = count;
	for (uint32_t i; i < count; i++) {
		float vectors[12]; //4*vec3 =12floats
		uint16_t attribute;

		stl.read(reinterpret_cast<char*>(&vectors), sizeof(vectors));
		stl.read(reinterpret_cast<char*>(&attribute), sizeof(attribute));

		triangle_t tri;


		tri.normal = vec3<double>(vectors[0], vectors[1], vectors[2]);
		tri.v0 = vec3<double>(vectors[3], vectors[4], vectors[5]);
		tri.v1 = vec3<double>(vectors[6], vectors[7], vectors[8]);
		tri.v2= vec3<double>(vectors[9], vectors[10], vectors[11]);
		tri.pMax = vec3<double>(
			std::max(tri.v0.x, std::max(tri.v1.x, tri.v2.x)),
			std::max(tri.v0.y, std::max(tri.v1.y, tri.v2.y)),
			std::max(tri.v0.z, std::max(tri.v1.z, tri.v2.z))
			);
		tri.pMin = vec3<double>(
			std::min(tri.v0.x, std::min(tri.v1.x, tri.v2.x)),
			std::min(tri.v0.y, std::min(tri.v1.y, tri.v2.y)),
			std::min(tri.v0.z, std::min(tri.v1.z, tri.v2.z))
			);
		bundle.triangles.push_back(tri);
	}
	return bundle;
}

// https://tavianator.com/2022/ray_box_boundary.html
bool triangles::rayIntersectsAABB(soundRay_t& ray, triangle_t &triangle){
	double t0 =0.0, tmax = INFINITY;
	vec3<double> inverseDirection = vec3(1/ray.direction.x,1/ray.direction.y,1/ray.direction.z);
	
	double t1 = (triangle.pMin.x - ray.startingPoint.x) * inverseDirection.x; 
	double t2 = (triangle.pMax.x - ray.startingPoint.x) * inverseDirection.x;
	t0 = std::max(t0, std::min(t1, t2));
	tmax = std::min(tmax, std::max(t1,t2));
	
	t1 = (triangle.pMin.y - ray.startingPoint.y) * inverseDirection.y; 
	t2 = (triangle.pMax.y - ray.startingPoint.y) * inverseDirection.y;
	t0 = std::max(t0, std::min(t1, t2));
	tmax = std::min(tmax, std::max(t1,t2));

	t1 = (triangle.pMin.z - ray.startingPoint.z) * inverseDirection.z; 
	t2 = (triangle.pMax.z - ray.startingPoint.z) * inverseDirection.z;
	t0 = std::max(t0, std::min(t1, t2));
	tmax = std::min(tmax, std::max(t1,t2));
	

	return t0<tmax;
}

// https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
vec3<double> triangles::findIntersecRayTriangle(soundRay_t& ray, triangle_t& triangle) {
	constexpr double EPSILON = 1e-6; 
	vec3<double>edge1 = triangle.v1 - triangle.v0;
	vec3<double>edge2 = triangle.v2 - triangle.v0;
	vec3<double>pvec = ray.direction%edge2;
	double det = edge1*pvec;
	if (std::fabs(det) < EPSILON) {
		return vec3<double>(0);
	}
	double inverseDet = 1/det;
	vec3 tvec = ray.startingPoint- triangle.v0;
	double u =(tvec*pvec) * inverseDet;
	if (u<-EPSILON || u > 1.0 + EPSILON) {
		return vec3<double>(0);
	}
	
	vec3<double>qvec = tvec%edge1;

	double v = (ray.direction*qvec) * inverseDet;
	if (v<-EPSILON || v + u > 1.0+ EPSILON) return vec3<double>(0);
	
	double t = (qvec*edge2) * inverseDet;



	return ray.direction*t + ray.startingPoint;
}
