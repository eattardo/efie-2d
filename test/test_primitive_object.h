/* This file contains tests for mesh.h implementation */
#include <map>

#include "gtest/gtest.h"
#include "../src/object/primitive_object.h"
#include "../src/object/shape.h"
#include "../src/material/material.h"

using namespace efie2d;
using namespace std;

// Test constructor
TEST(PrimitiveObj, ConstructorCirc)
{
	// circle
  Circle aCirc;
  aCirc.center.x = 1.0; aCirc.center.y = 1.0;
  aCirc.radius = 2.0;
  int id = 10; aCirc.id = id;
  Shape* ptrShape = &aCirc;
  // material
  Material aMat;
  Material* ptrMaterial = &aMat;
  PrimitiveObj prObj(ShapeType::Circ, ptrShape, ptrMaterial);


	EXPECT_EQ(id, prObj.GetShapeId());
	EXPECT_EQ(0, prObj.GetMaterialId());
	EXPECT_EQ(ShapeType::Circ, prObj.GetShapeType());
}


TEST(PrimitiveObj, ConstructorRec)
{
	// rectangle
	Rectangle aRec;
  aRec.pMin.x = 0.0; aRec.pMin.y = 0.0;
  aRec.pMax.x = 1.0; aRec.pMax.y = 1.0;
  int id = 10; aRec.id = id;
  Shape* ptrShape = &aRec;
  // material
  Material aMat;
  Material* ptrMaterial = &aMat;
  PrimitiveObj prObj(ShapeType::Rec, ptrShape, ptrMaterial);

	EXPECT_EQ(id, prObj.GetShapeId());
	EXPECT_EQ(0, prObj.GetMaterialId());
	EXPECT_EQ(ShapeType::Rec, prObj.GetShapeType());
}