#pragma once


//
// Vector definition
//
#include <cmath>

template <typename T>
struct vec3 {
	T x,y,z;

	vec3() {};
	
	explicit vec3(T i) : x(i) , y(i ), z(i) {};
	explicit vec3(T x, T y, T z) : x(x) , y(y), z(z) {};
	
	//directional vector from points
	vec3(vec3<T> firstPoint, vec3<T> secondPoint) : x(secondPoint.x - firstPoint.x),
							y(secondPoint.y - firstPoint.y),
							z(secondPoint.z - firstPoint.z) {};
	
	//addition and subtraction
	vec3 operator+(vec3 secondVector) {return {x + secondVector.x,y + secondVector.y,z + secondVector.z};}
	vec3 operator-(vec3 secondVector) {return {x - secondVector.x,y - secondVector.y,z - secondVector.z};}

	//scaling
	vec3 operator*(double scale) {return {x*scale, y*scale, z*scale};}
	vec3 operator/(double scale) {return {x/scale, y/scale, z/scale};}

	//dot product
	double operator*(vec3 secondVector) {return{x*secondVector.x + y*secondVector.y + z*secondVector.z};}

	//cross product
	vec3 operator%(vec3 secondVector) {return{	y*secondVector.z - z*secondVector.y,
							z*secondVector.x - x*secondVector.z,
							x*secondVector.y - y*secondVector.x};}

	//vector length
	double length() {return std::sqrt(x*x+y*y+z*z);}
};
namespace phys {
	double dBtoWm2(double intensity);
	double Wm2todB(double intensity);
	vec3<double> calcRefraction(vec3<double> direction);
}

