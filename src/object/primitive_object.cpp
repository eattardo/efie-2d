/* Implementation of the class PrimiteObj */
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>      // std::ifstream
#include <string>
#include <map>
#include <iomanip>
#include "primitive_object.h"

using namespace efie2d;

// Default constructor
PrimitiveObj::PrimitiveObj()
{
	typeObj = ShapeType::Circ; // default type
}


PrimitiveObj::PrimitiveObj(ShapeType typeObj_, Shape* ptrShape_, Material* ptrMaterial_)
{
	typeObj = typeObj_;
	if (typeObj ==ShapeType::Circ)
	{
		Circle* ptr = static_cast<Circle*>(ptrShape_);
		Circle* circPtr = new Circle(ptr);
		ptrShape = circPtr;
	}
	if (typeObj == ShapeType::Rec)
	{
		Rectangle* ptr = static_cast<Rectangle*>(ptrShape_);
		Rectangle* recPtr = new Rectangle(ptr);
		ptrShape = recPtr;
	}
	// set material
	ptrMaterial = ptrMaterial_;
}
//============================================


int PrimitiveObj::GetShapeId() noexcept
{
	return ptrShape->GetId();
}
//============================================


int PrimitiveObj::GetMaterialId() const noexcept
{
	return ptrMaterial.GetId();
}
//============================================

ShapeType PrimitiveObj::GetShapeType() const noexcept
{
	return typeObj;
}
//============================================

Material& PrimitiveObj::GetMaterial() noexcept
{
	return ptrMaterial;
}
//============================================

Shape* PrimitiveObj::GetShape() noexcept
{
	return ptrShape;
}
//============================================

bool PrimitiveObj::operator<(const PrimitiveObj& rhs) const
{
	return (ptrShape->GetId() < rhs.ptrShape->GetId());
}
//============================================
