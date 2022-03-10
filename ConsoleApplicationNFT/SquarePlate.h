#ifndef SQUAREPLATE_H
#define SQUAREPLATE_H
#pragma once
class SquarePlate
{

private:
	double side_x; //Side length in meter
	double side_y;
	double potPlate; //Potential of the plate in Volt
	double potPlateNeg; //Potential of the plate in negetive Volt
	double totalCharge; //Total amount of charges on the plate
	std::string myNameT;
	std::string myNameB;
	int nX; //Number of SmallSquares in x-direction, must be an odd number
	int nY; //must equal to nX,

	int nN; //Total number of Squares
	int nBN; //Total number of Squares in Base


	Vektor<SmallSquare> vPlate;
	Vektor<SmallSquare> bPlate;
	Vektor<SmallSquare> tPlate;

	RVektor gmVec; //gm-vector of Momentum Method
	RMatrix aMa; // Matrix of Momentum Method

	RVektor chargeDensity; //Charge density vector
	double capacitance;


public:
	SquarePlate();
	~SquarePlate();

	void CreateTwoPlates();
	void CreateTopLayer(double zCor);// Creates TopLayer of the Plate
	// Creates all SmallSquares of the Plate
	void CreateBottomLayer();// Creates BottomLayer of the Plate
	void CreateGmVektor(); // Creates the gm-Vektor of Momentum method
	void CreateMatrix(); // Creates the matrix of Momentum method
	void FindChargeDistribution(); //calculates the charge density in each square
	void CalculateTotalCharge();//Sums up all charges
	void CalculateCapacitance();
	void SavePlate(); // saves plate

	void CreateStructure(double distance);

	

};
#endif
