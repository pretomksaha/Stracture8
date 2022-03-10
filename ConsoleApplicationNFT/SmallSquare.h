#ifndef SMALLSQUARE_H
#define SMALLSQUARE_H
#pragma once
class SmallSquare
{

private:
	RVektor rCenter; //Centre of the square in meter
	double side; //Sidelength in meter
public:
	SmallSquare();
	~SmallSquare();

	void MoveTo(const RVektor& aVec) { rCenter = aVec; }; // Moves Square to aVec
	void MoveTo(const double x, const double y);
	void MoveToTop(const double x, const double y,const double z);
	void SetSide(const double aSide) { side = aSide; }; // to set side value
	double GetSide() const { return side; }; //To get the side
	RVektor GetCenter() const { return rCenter; }; //To get the center Vector
	double GetArea() { return side * side; }; // Calculates the area of a small square

	double CouplingCoefficient(const SmallSquare& aSq); //Calculate coupling to square aSq
	double SelfCoupling(); // is call for i = j
	double DistanceCoupling(const SmallSquare& aSq);

	bool IsSelfCoupling(const SmallSquare& aSq); //Identical squares
};

//------------------------------------------------
//Stream Output
std::ostream& operator<<(std::ostream& os, const SmallSquare& aSq);
#endif
