#include "ai_ker.h"
#include "../src/utils/physical_constants.h"
// Include the Hankel/Bessel functions
#include <complex_bessel.h>
#include <complex>


using namespace efie2d;

AiKer::AiKer(Mesh &mesh) : Kernel(mesh) {};
//============================================

void AiKer::AssembleZmat(DielectricParameters &dielectricParams, Mesh &mesh)
{
	// Get the number of DoF
	size_t dof = this->GetDoF();
	if (dof!=Zmat.n_rows)
	{
		std::cout << "DoF not equal to number of rows in the impedance matrix\n";
		exit(1);
	}
	// Assemble the matrix row-by-row
	for (int irow = 0; irow < dof; irow++)
	{
		AssembleZmatRow(irow, dielectricParams, mesh);
	}
}
//============================================

// Note that the matrix is not symmetric with the Aimod operator
void AiKer::AssembleZmatRow(const int irow,
														DielectricParameters &dielectricParams,
														Mesh &mesh)
{
	const std::complex<double> j(0.0,1.0); // imaginary unit
	const double an = mesh.GetAn();
	std::complex<double> kb_an = dielectricParams.GetKb() * an;

	// Constant used for the off-diagonal entry
	std::complex<double> cOffDiag = 0.5 * j *  pi * kb_an * sp_bessel::besselJ(1, kb_an);

	// Take the reference to the irow cell
	std::map<int, Point2d>::const_iterator cItRow = mesh.cells.find(irow);
	// Start the loop for this row
	for (auto const& cItCol : mesh.cells)
	{
		int icol = cItCol.first;
		// Look for this contrast element
		std::map<int, std::complex<double>>::const_iterator itChi = dielectricParams.GetChi().find(icol);
		std::complex<double> chi = itChi->second;
		// Assembling of the matrix
		// irow = icol (singularity computation done analytically)
		// Self-terms
		if (irow == icol)
		{
			std::complex<double> aii = 0.5 * j * (pi * kb_an * sp_bessel::hankelH2(1, kb_an) - 2.0*j);
			// set the matrix entry
			Zmat(irow, icol) = 1.0 + aii * chi;
		}
		// Off-diagonal entries (not singular)
		else
		{
			//compute distance between two cells
			double dist = computeDistance(cItRow->second, cItCol.second);
			Zmat(irow, icol) = cOffDiag * sp_bessel::hankelH2(0, dielectricParams.GetKb() * dist) * chi;
		}
	}
}
//============================================
