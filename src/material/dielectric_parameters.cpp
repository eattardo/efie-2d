#include "dielectric_parameters.h"
#include <iterator>
#include "../utils/physical_constants.h"
#include "../utils/stubs.h"

using namespace efie2d;

std::map<int,std::complex<double>>& DielectricParameters::GetChi() noexcept
{
	return chi;
}
//============================================


std::complex<double> DielectricParameters::GetKb() noexcept
{
	return kb;
}
//============================================


std::complex<double> DielectricParameters::GetEpsrcBackground() noexcept
{
	return epsrcBackground;
}
//============================================

void DielectricParameters::SetDielectricParameters(const double w, Geometry& geo)
{
	// In case we have only one object, we assume that the object is immersed in free space.
	// Then, we can have a contrast that is different from zero.

	// get the mesh and the primitive objects
	Mesh& mesh = geo.GetMesh();
	std::vector<PrimitiveObj>& vPrObj = geo.GetPrimitiveObjVec();
	size_t numObjs = vPrObj.size();
	// Set all contrast to zero
	for (auto const& itMesh : mesh.cells)
		chi.insert(std::pair<int,std::complex<double>>(itMesh.first, std::complex<double>(0.0, 0.0)));

	// Look for the background material
	std::complex<double> chiVal;
	std::complex<double> epsc;
	int backgroundId = mesh.GetBackgroundId();

	// Loop over the primitive objects
	for (size_t i=0; i < vPrObj.size(); i++)
	{
		int idObj = vPrObj[i].GetShapeId();
		Material& aMat = vPrObj[i].GetMaterial();
		// Assign the background
		if (idObj == backgroundId)
		{
			// Asuming propagation in free space in case of one object
			if (numObjs==1)
			{
				epsrcBackground = std::complex<double>(1.0, 0.0);
				kb = w * std::sqrt(mue0 * eps0);
				epsc = aMat.GetComplexEpsr();
				chiVal = epsc / epsrcBackground - 1.0;
			}
			else
			{
				epsrcBackground = aMat.GetComplexEpsr();;
				kb = w * std::sqrt(mue0 * eps0 * aMat.GetComplexEpsr());
				epsc = epsrcBackground; // set the background relative permittivity
				chiVal = std::complex<double>(0.0, 0.0);
			}
		}
		else
		{
			epsc = aMat.GetComplexEpsr();;
			chiVal = epsc / epsrcBackground - 1.0;
		}

		// Rectangle
		if (vPrObj[i].GetShapeType()==ShapeType::Rec)
		{
	  	Rectangle* ptrRec = static_cast<Rectangle*>(vPrObj[i].GetShape());
			// loop over all mesh
			for (auto const& itMesh : mesh.cells)
			{
				double x = itMesh.second.x;
				double y = itMesh.second.y;
				if ((x>=ptrRec->pMin.x && x<= ptrRec->pMax.x) &&
						(y >= ptrRec->pMin.y && y <= ptrRec->pMax.y))
					chi[itMesh.first] = chiVal;
			}
		}
		// Circle
		if (vPrObj[i].GetShapeType()==ShapeType::Circ)
		{
	  	Circle* ptrCirc = static_cast<Circle*>(vPrObj[i].GetShape());
			// loop over all mesh
			for (auto const& itMesh : mesh.cells)
			{
				double xCenter = ptrCirc->center.x;
				double yCenter = ptrCirc->center.y;
				double radius = ptrCirc->radius;
				double x = itMesh.second.x - xCenter;
				double y = itMesh.second.y - yCenter;
				if (std::sqrt(x*x + y*y) <= radius)
					chi[itMesh.first] = chiVal;
			}
		}
	}
}


