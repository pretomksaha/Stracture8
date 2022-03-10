#include <string>
#include <iostream>
#include <fstream>
#include "Physicon.h"
using namespace std;

#ifndef RVEKTOR_H
#include "RVektor.h"
#endif

#ifndef RMATRIX_H
#include "RMatrix.h"
#endif

#ifndef	SMALLSQUARE_H
#include "SmallSquare.h"
#endif

#include "SquarePlate.h"



SquarePlate::SquarePlate()
{
	side_x = 0.10; // SquarePlate of 1 meter
	side_y = 0.16;
	potPlate = 0.5; //Potential of the plate 1 Volt
	potPlateNeg = -0.5; //Potential of the plate 1 Volt

	nX = 20;
	nY = 32;
	nN = 336;// saheris 640
	//nN = 368;//PS
	//nN = 256;//akib
	nBN = (nX*nY);
	myNameT = "TOPLAYER";
	myNameB = "BOTTOMLAYER";
}


SquarePlate::~SquarePlate()
{
}
//--------------------------------------------------------
void SquarePlate::CalculateTotalCharge()
{
	//std::cout << "\n Calculate The Total Charge\n\n";
	double area = vPlate[0].GetArea();

	totalCharge = chargeDensity.SumupElements();

	totalCharge *= area;

	std::cout << "\n\nTotal Charge =" << totalCharge << " coulombs \n\n";
}
//--------------------------------------------------------
void SquarePlate::FindChargeDistribution()
{
	std::cout << "\nCalculating Charge Distribution \n\n";

	chargeDensity.SetDim(nN+nBN);

	chargeDensity = RealGaussElimination(aMa, gmVec);

	int iN = 0;
	for (int i = 0; i < nX; i++)
	{
		std::cout << iN<< "= ";
		for (int j = 0; j < nY; j++)
		{
			
			std::cout << chargeDensity[iN] << " ";
			iN++;
		}
	}
	//std::cout <<"(Done)"<< "\n";
}
//--------------------------------------------------------
void SquarePlate::CreateMatrix()
{
	std::cout << "\nCalculating Matrix \n\n";

	aMa.SetDimension(nN+nBN, nN+nBN);

	for (int i = 0; i < nN+nBN; i++)
	{
		for (int j = 0; j < nN+nBN; j++)
		{
			aMa[i][j] = vPlate[i].CouplingCoefficient(vPlate[j]);
		}
	}

	//std::cout << "\n aMa = \n" << aMa << "\n";
	//std::cout << "(Done)" << "\n";
}
//--------------------------------------------------------
void SquarePlate::CreateGmVektor()
{
	std::cout << "\nCalculating GmVektor \n";

	gmVec.SetDim(nN+nBN);

	for (int i = 0; i < nBN; i++)
	{
		gmVec[i] = potPlateNeg;
	}
	for (int i = nBN; i < nN+nBN; i++)
	{
		gmVec[i] = potPlate;
	}
	std::cout << "gmVec = " << gmVec << "\n";
	//std::cout << "(Done)" << "\n";
}
//--------------------------------------------------------
//serish
//------------------------------------------------------
void SquarePlate::CreateTopLayer(double zCor) {
	std::cout << "\nCalculating TopLayer\n\n";
	tPlate.SetDim(nN);
	double delX = side_x / nX;
	double delY = side_y / nY;

	int iN = 0;

	for (int iX = -nX / 2; iX < nX / 2; iX++)
	{
		double x = delX * iX;
		for (int iY = -nY / 2; iY < nY / 2; iY++)
		{
			double y = delY * iY;

			if ((iY < -12 || iY >= 12) || (iY < -2 && iY >= -6))
			{
				tPlate[iN].MoveToTop(x, y, zCor);
				tPlate[iN].SetSide(delX);
				std::cout << iN << " " << tPlate[iN];
				iN++;
			}
			else if (iX < -6 && (iY >= -2 && iY < 12))
			{
				tPlate[iN].MoveToTop(x, y, zCor);
				tPlate[iN].SetSide(delX);
				std::cout << iN << " " << tPlate[iN];
				iN++;
			}
			else if ((iX < 6 && iX >= 2) && (iY >= -12 && iY < 2))
			{
				tPlate[iN].MoveToTop(x, y, zCor);
				tPlate[iN].SetSide(delX);
				std::cout << iN << " " << tPlate[iN];
				iN++;
			}
		}
	}
}
//------------------------------------------------------------------
//AKIB AND BRO
//------------------------------------------------------------------
/*void SquarePlate::CreateTopLayer(double zCor) {
	std::cout << "\nFunction: CreateTopLayer()\n\n";
	tPlate.SetDim(nN);
	double delX = side_x / nX;
	double delY = side_y / nY;

	int iN = 0;

	for (int iX = -nX / 2; iX < nX / 2; iX++)
	{
		double x = delX * iX;
		for (int iY = -nY / 2; iY < nY / 2; iY++)
		{
			double y = delY * iY;

			if ((iY < -12 || iY >= 12) || (iX < 2 && iX >= -2))
			{
				tPlate[iN].MoveToTop(x, y, zCor);
				tPlate[iN].SetSide(delX);
				//std::cout << iN << " " << tPlate[iN];
				iN++;
			}
		}
	}
}*/
//-----------------------------------------------------
//  source code of function void SquarePlate::CreateTopLayer(double zCor)  PS
//-----------------------------------------------------
/*
void SquarePlate::CreateTopLayer(double zCor) {
	std::cout << "\n Create The TopLayer For Shape 8\n\n";
	tPlate.SetDim(nN);
	double delX = side_x / nX;
	double delY = side_y / nY;

	int iN = 0;

	for (int iX = -nX / 2; iX < nX / 2; iX++)
	{
		double x = delX * iX;
		for (int iY = -nY / 2; iY < nY / 2; iY++)
		{
			double y = delY * iY;
			if (iX>=-6 && iX < 6)
			{
			
				if (iY < -12 || iY >= 12) {
					tPlate[iN].MoveToTop(x, y, zCor);
					tPlate[iN].SetSide(delX);
					std::cout << iN << " " << tPlate[iN] << "\n";
					iN++;
				}
				else if (iY < 2 && iY >=-2) {
					tPlate[iN].MoveToTop(x, y, zCor);
					tPlate[iN].SetSide(delX);
					std::cout << iN << " " << tPlate[iN] << "\n";
					iN++;
				}
		

			}
			else
			{
				if(iY>=2 || iY<-2)
				{ 
					tPlate[iN].MoveToTop(x, y, zCor);
					tPlate[iN].SetSide(delX);
					std::cout << iN << " " << tPlate[iN]<<"\n";
					iN++;
				}
				
			}
			
			
		}
	}
	std::cout << "(Done)" << "\n";

} */
//-----------------------------------------------------
//  source code of function SquarePlate::CreateBottomLayer()
//-----------------------------------------------------
void SquarePlate::CreateBottomLayer()
{
	std::cout << "\nCalculating BottomLayer\n\n";

	bPlate.SetDim(nBN);
	double delX = side_x / nX;
	double delY = side_y / nY;

	int iN = 0;

	for (int iX = -nX / 2; iX < nX / 2; iX++)
	{
		double x = delX * iX;
		for (int iY = -nY / 2; iY < nY / 2; iY++)
		{
			double y = delY * iY;
			bPlate[iN].MoveTo(x, y);
			bPlate[iN].SetSide(delX);
			//std::cout << iN << " " << bPlate[iN] << "\n";
			iN++;
		}
	}
	//std::cout << "(Done)" << "\n";
}

//-----------------------------------------------------
//  source code of function SquarePlate::SavePlate()
//-----------------------------------------------------
void SquarePlate::SavePlate()
{
	std::ofstream aFile;
	aFile.open("Charge_distribution_capacitance_group_4.txt");

	aFile << myNameB <<"\n";
	aFile << nBN << "," << potPlateNeg << "\n";
	for (int i = 0; i < nBN; i++)
	{
		aFile << vPlate[i] << "," << chargeDensity[i] << ")" <<"\n";
	}

	aFile << myNameT << "\n";
	aFile << nN << "," << potPlate << "\n";
	for (int i = nBN; i < nN+nBN; i++)
	{
		aFile << vPlate[i] << "," << chargeDensity[i] << ")" << "\n";
	}
	aFile.close();
	std::cout << "\nData of Plate stored in Charge_distribution_capacitance_group_4.txt \n\n";
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#pragma region Geometry of the Structure
/*This Function is to define the Geometry of the Structure*/
void SquarePlate::CreateStructure(double distance)
{
	CreateBottomLayer();
	CreateTopLayer(distance);
	CreateTwoPlates();
}

/*This Function is to define the Geometry of the Base Plate*/
#pragma endregion
//------------------------------------------------------------
void SquarePlate::CreateTwoPlates()
{
	
	vPlate.SetDim(nN + nBN);


	int iM = 0;

	for (int iN = 0; iN < nBN; iN++)
	{
		vPlate[iM] = bPlate[iN];
		iM++;
	}
	for (int iN = 0; iN < nN; iN++)
	{
		vPlate[iM] = tPlate[iN];
		iM++;
	}

}

//*******************************
void SquarePlate::CalculateCapacitance()
{
	capacitance = abs(totalCharge) / (potPlate - potPlateNeg);
	std::cout << "\nTotal Capacitance = " << capacitance << " Farad\n\n";
}
