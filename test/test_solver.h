#include "gtest/gtest.h"
#include "../src/mesh/mesh.h"
#include "../src/mesh/generate_mesh.h"
#include "../src/utils/physical_constants.h"
#include "../src/kernel/ai_ker.h"
#include "../src/material/dielectric_parameters.h"
#include "../src/preprocessing/input_file.h"
#include "../src/preprocessing/read_input_file.h"
#include "../src/solver/planewave.h"
#include "../src/solver/solver.h"
#include "../src/solver/incident_field_utils.h"

using namespace efie2d;

// Test direction phi=0
TEST(Solver, TestSolver1)
{
	Mesh mesh2d;
	InputFile inputFile;
	string filename = "../../circle_test1.json";
	// read the input file and store info in inputFile
	ReadInputFile(filename, inputFile);
	int ierr = GenerateMesh(inputFile, mesh2d);
	DielectricParameters dielectricParams;
	SetDielectricParameters(1, inputFile, mesh2d, dielectricParams);

  arma::cx_mat Einc = CreatePlanewaveExcitation(inputFile, mesh2d, dielectricParams);

	// Assemble a test matrix
	AiKer aZmat(mesh2d); // zeros matrix
	aZmat.AssembleZmat(dielectricParams, mesh2d);

	// Create now an instance of the solver
	Solver aSolver(aZmat, Einc);
	// solve the linear
	aSolver.Solve();

	arma::vec residuaVec;
	aSolver.ComputeResidua(residuaVec);
	EXPECT_LE(residuaVec(0), 1e-6);
}

