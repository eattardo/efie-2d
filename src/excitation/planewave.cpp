#include "planewave.h"
#include "../src/utils/stubs.h"
#include <armadillo>

using namespace efie2d;

// Call the ctor of the parent class Excitation
Planewave::Planewave(Mesh &mesh, const size_t numOfExcitation)
	: Excitation(mesh, numOfExcitation)
{

};
//============================================


Planewave::Planewave(Mesh &mesh, const size_t numOfExcitation, std::complex<double> kb, const double startPhi,
					  const double endPhi)
 :  Excitation(mesh, numOfExcitation)
{
	// Create planewave excitations
  double startPhiRad = Deg2Rad(startPhi);
  double endPhiRad = Deg2Rad(endPhi);
  arma::vec phiInc = arma::linspace(startPhiRad, endPhiRad, numOfExcitations);
  // set the excitation
	ComputeEinc(mesh, kb, phiInc);
}
//============================================


void Planewave::ComputeEinc(Mesh &mesh, const std::complex<double> kb,
														arma::vec &phiInc)
{
	size_t dof = this->GetDof();
	size_t numOfExcitation = this->GetNumExcitations();
	if (phiInc.size()!=numOfExcitation)
	{
		std::cout<<"Angles of incidence differ from numOfExcitation\n";
		exit(1);
	}
	const std::complex<double> j(0.0,1.0); // imaginary unit
	// Start the loop for each angle
	for (size_t i = 0; i < numOfExcitation; ++i)
	{
		double cosPhi = std::cos(phiInc(i));
		double sinPhi = std::sin(phiInc(i));

		// loop for each cell and add the contribute for the Einc
		for (auto const& cItCol : mesh.cells)
		{
			int idCell = cItCol.first;
			std::complex<double> e0 = std::exp(-j*kb*(cItCol.second.x*cosPhi + cItCol.second.y*sinPhi));
			Einc(idCell, i) = e0;
		}
	}
}
//============================================
