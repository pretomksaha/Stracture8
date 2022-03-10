#include <string>
#include <iostream>
#include "Physicon.h"

#ifndef RVEKTOR_H
#include "RVektor.h"
#endif

#include "SmallSquare.h"



SmallSquare::SmallSquare()
{
	rCenter = RVektor(0., 0., 0.);
	side = 0.;
}


SmallSquare::~SmallSquare()
{
}
//------------------------------------------------
bool SmallSquare::IsSelfCoupling(const SmallSquare& aSq)
{
	return (rCenter == aSq.rCenter);
}
//------------------------------------------------
double SmallSquare::SelfCoupling()
{
	double retVal = side / (PI*EPS_0);
	retVal *= log(sqrt(2.) + 1);

	return retVal;
}
//------------------------------------------------
double SmallSquare::DistanceCoupling(const SmallSquare& aSq)
{
	RVektor disVec = rCenter - aSq.rCenter;
	double dis = disVec.Norm();

	double retVal = side * side;
	retVal /= 4.*PI*EPS_0*dis;

	return retVal;
}
//------------------------------------------------
double SmallSquare::CouplingCoefficient(const SmallSquare& aSq)
{
	//RVektor disVec = rCenter - aSq.rCenter;
	//double dis = disVec.Norm();

	//return dis;

	if (IsSelfCoupling(aSq))
		return SelfCoupling();
	else
		return DistanceCoupling(aSq);
}
//------------------------------------------------
void SmallSquare::MoveTo(const double x, const double y)
{
	rCenter.SetX(x);
	rCenter.SetY(y);
}
void SmallSquare::MoveToTop(const double x, const double y, const double z)
{
	rCenter.SetX(x);
	rCenter.SetY(y);
	rCenter.SetZ(z);
}
//------------------------------------------------
//Stream Output
//------------------------------------------------
std::ostream& operator<<(std::ostream& os, const SmallSquare& aSq)
{
	os << '(';
	os << aSq.GetSide() << ',';
	os << aSq.GetCenter();

	return os;
}