//-----------------------------------------------------------------------------
//
//  EFIE2D - Main
//
//-----------------------------------------------------------------------------

// General headers
#include <sstream>
#include <fstream>      // std::ifstream
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
// EFIE2D Includes
#include "src/utils/physical_constants.h"
#include "src/utils/stubs.h"
#include "src/geometry/geometry.h"
#include "src/material/dielectric_parameters.h"
#include "src/json_reader/json_reader.h"
#include "../../../json-develop/single_include/nlohmann/json.hpp"
#include "src/model/model.h"
#include "src/solver/solver.h"
#include "src/kernel/ai_ker.h"
#include "src/utils/hr_time.h"
#include "src/request/writing_utils.h"

// using the EFIE2D namespace
using namespace efie2d;



//=========================================================================================
//  START EFIE2D
//=========================================================================================
int main(int argc, char** argv)
{
	// Clear the console window (only Windows)
	printLogo();

	// INPUT file to be read (e.g.,"D:\CODE\EFIE2D\PetersonCyl.input" )
	std::string inputFilename;
  parseInput(argc, argv, inputFilename);

	// Create the json object from the input file
	JsonReader jsonObj(inputFilename);

	// create the model object (it contains the geometry, the mesh, the dielectric parameters, and the excitation)
	Model* ptrMod = new Model(jsonObj);
	Mesh* ptrMesh = ptrMod->GetPtrMesh();
	DielectricParameters* ptrDielParams = ptrMod->GetPtrDielectricParams();

  // Assemble the impedance matrix
  CStopWatch timer_build_zmat;      // Timer assembling the matrix
  timer_build_zmat.startTimer();
  AiKer aZmat(*ptrMesh); // zeros matrix
  aZmat.AssembleZmat(*ptrDielParams, *ptrMesh);
  std::cout << "Assembled a BEM matrix of size: [" << aZmat.Zmat.n_rows << " x " << aZmat.Zmat.n_cols << "]";
  std::cout << " in " << timer_build_zmat.getElapsedTime_sec() << " (sec)\n";

  // Create now an instance of the solver
  // Use a ptr to the base class and redirect
  // to the correct incident field
  message("Solution of the linear system. . .");
  Excitation* ptrEinc = ptrMod->GetPtrExcitation();
  CStopWatch timer_solution;
  timer_solution.startTimer();
  Solver aSolver(aZmat, ptrEinc->Einc);
  // and solve the linear system
  aSolver.Solve();
  std::cout << " in " << timer_solution.getElapsedTime_sec() << " (sec)\n";

  // write solution on file
  // write solution for y=0 on file
    // Get the filename without .input
  std::string fileNameWithoutExtension = inputFilename.substr(0, inputFilename.rfind("."));
  std::string tmpName = fileNameWithoutExtension + "_Y0.output";
  writeEtotLine(2, tmpName.c_str(), aSolver.Etot.col(0), *ptrMesh, 0.0);

	message("EFIE2D has terminated");
}
