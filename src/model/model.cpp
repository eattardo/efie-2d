#include <type_traits>
#include "model.h"
#include "../excitation/planewave.h"

using namespace efie2d;

Model::Model()
{
	ptrGeo = nullptr;
	ptrDielParams = nullptr;
	ptrEinc = nullptr;
}

Model::Model(JsonReader& jsonObj)
{
	// Create the geometry (mesh, material, and primitive objects)
	// the excitation, and
	// the dielectric parameters
	// Geo
	ptrGeo = new Geometry(jsonObj.resolution, jsonObj.vRec, jsonObj.vCirc,
		jsonObj.vMat, jsonObj.geo2Mat);
	// Dielectric Parameters
	ptrDielParams = new DielectricParameters();
	ptrDielParams->SetDielectricParameters(jsonObj.freq.GetOmega(), *ptrGeo);
	// Create the excitation
	const size_t numOfExcitation = 1; //hard coded here for the moment
	ptrEinc = new Planewave(ptrGeo->GetMesh(), numOfExcitation, ptrDielParams->GetKb(),
		jsonObj.startPhi, jsonObj.endPhi);
}
//============================================

Geometry* Model::GetPtrGeometry() noexcept
{
	return ptrGeo;
}
//============================================

Excitation* Model::GetPtrExcitation() noexcept
{
	return ptrEinc;
}
//============================================

DielectricParameters* Model::GetPtrDielectricParams() noexcept
{
	return ptrDielParams;
}
//============================================

Mesh* Model::GetPtrMesh() noexcept
{
	return std::addressof(ptrGeo->GetMesh());
}



