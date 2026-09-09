#pragma once

//includes
#include <vector>
#include "ray.hpp"
#define distanceSourceReciever 1000.0f
struct recieverMatrix_t{
	std::vector<double> startingPoint;
	std::vector<double> recieverDimension;
	
	std::vector<int> matrix;
};

class reciever{
	
	public:
		recieverMatrix_t generateReciever(int resolutionX, int resolutionY, std::vector<double> positionCentre);
		void addToReciever(soundRay_t incidentRay, recieverMatrix_t&);
		void generatePPM(recieverMatrix_t);


	private:
		//generateReciever
		
		//addToReciever

		std::vector<int> intersectionPosition(soundRay_t& incidentRay); //returns the matrix cell needed to increment
		void incrementMatrixCell(soundRay_t& incidentRay, std::vector<int> matrixCell);
		//terminateRay (defined in soundray class)
};
