#include "geometry.h"

#include <vector>
#include <map>

using namespace efie2d;

Geometry::Geometry(const double resolution, std::vector<Rectangle>& vRec, std::vector<Circle>& vCirc,
      std::vector<Material>& vMat, std::map<int, int>& geo2Mat)
{
  // Add the primitive objs
  AddPrimitiveObjects(vRec, vCirc, vMat, geo2Mat);
  // generate the mesh (an instante is already created)
  int ierr = mesh2d.GenerateMesh(resolution, GetPrimitiveObjVec());
  if (ierr != 0)
  {
    std::cerr << "Error while generating the mesh. . .\n";
    exit(1);
  }
  std::cout << "\nGenerated mesh with " << mesh2d.GetNumCells() << " cells\n";
  std::cout << "Radius of cell is set to " << mesh2d.GetAn() << " m\n";

}
//============================================


void Geometry::AddPrimitiveObjects(std::vector<Rectangle>& vRec, std::vector<Circle>& vCirc,
																	 std::vector<Material>& vMat, std::map<int,int>& geo2Mat)
{
	// Check that we have a mateiral for each obj
	if (vRec.size() + vCirc.size() != vMat.size())
	{
		std::cout << "A material must be defined for each object"<< std::endl;
    exit(1);
	}

	int id_mat;
	std::map<int,int>::iterator geo2MatIt;
	// Loop over the rectangle
	for (size_t i = 0; i < vRec.size(); ++i)
	{
		//
		geo2MatIt = geo2Mat.find(vRec[i].id);
		// suppose we always find one
		if (geo2MatIt != geo2Mat.end()) id_mat = geo2MatIt->second;
		Shape* ptrShape = &vRec[i];
		// loop over the materials
		for (int j = 0; j < vMat.size(); ++j)
		{
			Material* ptrMaterial = vMat[j].GetMaterialFromId(id_mat);
			if (ptrMaterial)
			{
				PrimitiveObj prObj(ShapeType::Rec, ptrShape, ptrMaterial);
				vObj.push_back(prObj);
				break;
			}
		}
	}

	// Loop over the circle
	for (int i = 0; i < vCirc.size(); ++i)
	{
		//
		geo2MatIt = geo2Mat.find(vCirc[i].id);
		// suppose we always find one
		if (geo2MatIt != geo2Mat.end()) id_mat = geo2MatIt->second;
		Shape* ptrShape = &vCirc[i];
		// loop over the materials
		for (int j = 0; j < vMat.size(); ++j)
		{
			Material* ptrMaterial = vMat[j].GetMaterialFromId(id_mat);
			if (ptrMaterial)
			{
				PrimitiveObj prObj(ShapeType::Circ, ptrShape, ptrMaterial);
				vObj.push_back(prObj);
				break;
			}
		}
	}
}
//============================================


std::vector<PrimitiveObj>& Geometry::GetPrimitiveObjVec()
{
	return vObj;
}
//=============================================


Mesh& Geometry::GetMesh() noexcept
{
  return mesh2d;
}
//============================================
