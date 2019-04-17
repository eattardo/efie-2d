#include "point_source.h"
#include "../utils/physical_constants.h"
#include "../src/utils/stubs.h"
#include <complex_bessel.h>

using namespace efie2d;

// Call the ctor of the parent class Excitation
PointSource::PointSource(Mesh &mesh, const size_t numOfExcitation)
	: Excitation(mesh, numOfExcitation) {};
//============================================


void PointSource::ComputeEinc(Mesh &mesh, const std::complex<double> kb,
	const std::vector<Point2d> &pointSourceRt, const std::vector<std::complex<double>> &Ie,
	const double w)
{
	size_t dof = this->GetDof();
	size_t numOfExcitation = this->GetNumExcitations();
	if (pointSourceRt.size()!=numOfExcitation)
	{
		message("Position vector for point sources differ from numOfExcitation");
		exit(1);
	}
	// Start the loop for each position
	for (size_t i = 0; i < numOfExcitation; ++i)
	{
		// loop for each cell and add the contribute for the Einc
		for (auto const& cItCol : mesh.cells)
		{
			int idCell = cItCol.first;
			double dist = computeDistance(pointSourceRt[i], cItCol.second);
			// check for dist = 0, it means that source is inside the domain!
			std::complex<double> e0 =  - w * mue0 * 0.25 *  sp_bessel::hankelH2(0, kb * dist);
			Einc(idCell, i) = e0;
	
		}
		
	}
}
//============================================
