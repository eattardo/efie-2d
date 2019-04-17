#include <map>
#include <iterator>
#include "gtest/gtest.h"
#include "../src/mesh/mesh.h"
#include "../src/mesh/generate_mesh.h"
#include "../src/kernel/ai_ker.h"
#include "../src/material/dielectric_parameters.h"
#include "../src/preprocessing/input_file.h"
#include "../src/preprocessing/read_input_file.h"


using namespace efie2d;

// Test constructor
TEST(AssembleMath, CircleTest1)
{
	Mesh mesh2d;
	InputFile inputFile;
	string filename = "../../circle_test1.json";

	int ierr = GenerateMesh(inputFile, mesh2d);
	AiKer aZmat(mesh2d); // zeros matrix

	EXPECT_EQ(mesh2d.cells.size(), aZmat.Zmat.n_rows);
	EXPECT_EQ(mesh2d.cells.size(), aZmat.Zmat.n_cols);
	EXPECT_EQ(mesh2d.cells.size(), aZmat.GetDoF());
}

// Test two rows of impedance matrix
TEST(AssembleMath, AssembleRow0)
{
	Mesh mesh2d;
	InputFile inputFile;
	string filename = "../../circle_test1.json";
	// read the input file and store info in inputFile
	ReadInputFile(filename, inputFile);
	int ierr = GenerateMesh(inputFile, mesh2d);
	DielectricParameters dielectricParams;
	SetDielectricParameters(1, inputFile, mesh2d, dielectricParams);
	AiKer aZmat(mesh2d); // zeros matrix
	aZmat.AssembleZmatRow(0, dielectricParams, mesh2d);
	aZmat.AssembleZmatRow(1, dielectricParams, mesh2d);
	EXPECT_EQ(aZmat.Zmat(0,0).real(), aZmat.Zmat(1,1).real());
	EXPECT_EQ(aZmat.Zmat(0, 0).imag(), aZmat.Zmat(1, 1).imag());
}

// Test full matrix
TEST(AssembleMath, AssembleFullMatrix)
{
	Mesh mesh2d;
	InputFile inputFile;
	string filename = "../../circle_test1.json";
	// read the input file and store info in inputFile
	ReadInputFile(filename, inputFile);
	int ierr = GenerateMesh(inputFile, mesh2d);
	DielectricParameters dielectricParams;
	SetDielectricParameters(1, inputFile, mesh2d, dielectricParams);
	AiKer aZmat(mesh2d); // zeros matrix
	size_t dof = aZmat.GetDoF();
	EXPECT_EQ(dof, aZmat.Zmat.n_rows);

	aZmat.AssembleZmat(dielectricParams, mesh2d);
	for (int i = 0; i < dof; i++)
	{
		for (int j = 0; j < dof; j++)
		{
			if (i == j)
			{
				EXPECT_EQ(aZmat.Zmat(i,i).real(), aZmat.Zmat(j,j).real());
				EXPECT_EQ(aZmat.Zmat(i,i).imag(), aZmat.Zmat(j,j).imag());
			}
			else
			{
				EXPECT_EQ(aZmat.Zmat(i, j).real(), aZmat.Zmat(j, i).real());
				EXPECT_EQ(aZmat.Zmat(i, j).imag(), aZmat.Zmat(j, i).imag());
			}
		}
	}
	//aZmat.SaveZmatFile("Zfull.txt");
}

