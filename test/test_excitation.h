#include <armadillo>
#include "gtest/gtest.h"
#include "../src/mesh/mesh.h"
#include "../src/mesh/generate_mesh.h"
#include "../src/solver/planewave.h"
#include "../src/material/dielectric_parameters.h"
#include "../src/preprocessing/input_file.h"
#include "../src/preprocessing/read_input_file.h"
#include "../src/utils/physical_constants.h"

using namespace efie2d;

// Test direction phi=0
TEST(Excitation, TestPlwPhi0)
{
	Mesh mesh2d;
	InputFile inputFile;
	string filename = "../../circle_test1.json";
	// read the input file and store info in inputFile
	ReadInputFile(filename, inputFile);
	int ierr = GenerateMesh(inputFile, mesh2d);
	DielectricParameters dielectricParams;
	SetDielectricParameters(1, inputFile, mesh2d, dielectricParams);
	// Create angle of excitation
	size_t numOfExcitations = 1;
	arma::vec phiInc(numOfExcitations);
	phiInc(0) = 0;
	// create the planewave obj
	Planewave plw(mesh2d, numOfExcitations);
	// set the excitation
	plw.ComputeEinc(mesh2d, dielectricParams.kb, phiInc);
	//std::cout << "Plw: \n" << plw.Einc << std::endl;
	//std::cout << "Mesh: \n" << mesh2d << std::endl;
	for (size_t i = 4; i < 9; i++)
		EXPECT_EQ(1.0, std::abs(plw.Einc(i)));
}

// Test direction phi=pi/2
TEST(Excitation, TestPlwPhiPiOver2)
{
	Mesh mesh2d;
	InputFile inputFile;
	string filename = "../../circle_test1.json";
	// read the input file and store info in inputFile
	ReadInputFile(filename, inputFile);
	int ierr = GenerateMesh(inputFile, mesh2d);
	DielectricParameters dielectricParams;
	SetDielectricParameters(1, inputFile, mesh2d, dielectricParams);
	// Create angle of excitation
	size_t numOfExcitations = 1;
	arma::vec phiInc(numOfExcitations);
	phiInc(0) = pi/2;
	// create the planewave obj
	Planewave plw(mesh2d, numOfExcitations);
	// set the excitation
	plw.ComputeEinc(mesh2d, dielectricParams.kb, phiInc);
	//std::cout << "Plw: \n" << plw.Einc << std::endl;
	//amstd::cout << "Mesh: \n" << mesh2d << std::endl;
	for (size_t i = 4; i < 9; i++)
		EXPECT_EQ(1.0, std::abs(plw.Einc(i)));
}



