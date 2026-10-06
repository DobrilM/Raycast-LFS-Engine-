#include<ios>
#include<fstream>
#include<cstdint>
#include "triangle.hpp"
#include "ray.hpp"

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

bool triangles::rayIntersectsAABB(soundRay_t& ray, triangle_t &triangle){
	double t0 =0.0, tmax = 1e4 *1.0; 
	
	return 1;
}

//https://cadxfem.org/inf/Fast%20MinimumStorage%20RayTriangle%20Intersection.pdf
vec3<double> triangles::findIntersecRayTriangle(soundRay_t& ray, triangle_t& triangle) {
	constexpr double EPSILON = 1e-6; 
	vec3<double>edge1 = triangle.v1 - triangle.v0;
	vec3<double>edge2 = triangle.v2 - triangle.v0;
	vec3<double>pvec = edge1%edge2;
	double det = edge1*pvec;
	if (std::fabs(det) < EPSILON) {
		return {};
	}

	double inverseDet = 1/det;
	vec3 tvec = ray.startingPoint- triangle.v0;
	double u =tvec*pvec;
	if (u<-EPSILON || u > det) {
		return {};
	}
	
	vec3<double>qvec = tvec%edge1;

	double v = ray.direction*qvec;
	if (v<-EPSILON || v + u > det) return{};
	
	double t = qvec*edge2;



	return ray.direction*t + ray.startingPoint;
}
