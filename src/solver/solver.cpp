#include "solver.h"

using namespace efie2d;

// Ctor of the Solver class
Solver::Solver(Kernel &Mat, arma::cx_mat &Einc)
{
	// Set the pointers to the reference objects
	matPtr = &Mat;
	EincPtr = &Einc;
	// Allocate the memory and set to zero
	// Solution will be dof x numExcitations
	Etot.zeros(Mat.GetDoF(), EincPtr->n_cols);
}
//============================================


void Solver::Solve()
{
	// For the moment solve with fast option and
	// use direct solver
	try
	{
		Etot = arma::solve(matPtr->Zmat, *EincPtr,
			               arma::solve_opts::fast);
	}
	catch(std::runtime_error &e)
	{
		std::cout<<"Runtime error in solving the system: " << e.what() << std::endl;
	}
}
//============================================


void Solver::ComputeResidua(arma::vec &residuaVec)
{
	residuaVec.zeros(EincPtr->n_cols);
	for (size_t i = 0; i < EincPtr->n_cols; i++)
	{
		residuaVec(i) = arma::norm(matPtr->Zmat * Etot.col(i) - EincPtr->col(i));
	}
}
//============================================