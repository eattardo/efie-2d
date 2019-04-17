/* This file contains tests for geometry.h implementation */
#include <map>
#include <sstream>
#include <fstream>      // std::ifstream
#include <string>

#include "gtest/gtest.h"
#include "../src/geometry/geometry.h"
#include "../src/json_reader/json_reader.h"

using namespace efie2d;
using namespace std;

// Test Peterson Cyl
TEST(GeometryTest, PetersonCyl)
{
	std::string filename = "PetersonCyl.json";
	JsonReader jsonObj(filename);
	// Create the geometry, which in turn, will create the mesh
	Geometry geo(jsonObj.resolution, jsonObj.vRec, jsonObj.vCirc, jsonObj.vMat, jsonObj.geo2Mat);
	EXPECT_EQ(1, geo.GetPrimitiveObjVec().size());
}

// Test Peterson Cyl
TEST(GeometryTest, GeoPrimitiveObj)
{
	std::string filename = "PetersonCyl.json";
	JsonReader jsonObj(filename);
	// Create the geometry, which in turn, will create the mesh
	Geometry geo(jsonObj.resolution, jsonObj.vRec, jsonObj.vCirc, jsonObj.vMat, jsonObj.geo2Mat);
	// get vec of primitive obj
	auto vPrObj = geo.GetPrimitiveObjVec();
	EXPECT_EQ(ShapeType::Circ, vPrObj[0].GetShapeType());
	auto ptr = vPrObj[0].GetMaterial();
	EXPECT_EQ(3.0, ptr.GetEpsr());
	EXPECT_EQ(0.0, ptr.GetSigma());
}


// Test three objects
TEST(GeometryTest, ThreeObjs)
{
	std::string filename = "ThreeObjects.json";
	JsonReader jsonObj(filename);
	// Create the geometry, which in turn, will create the mesh
	Geometry geo(jsonObj.resolution, jsonObj.vRec, jsonObj.vCirc, jsonObj.vMat, jsonObj.geo2Mat);
	// get vec of primitive obj
	auto vPrObj = geo.GetPrimitiveObjVec();
	EXPECT_EQ(3, geo.GetPrimitiveObjVec().size());

	EXPECT_EQ(ShapeType::Rec, vPrObj[0].GetShapeType());
	EXPECT_EQ(ShapeType::Circ, vPrObj[1].GetShapeType());
	EXPECT_EQ(ShapeType::Circ, vPrObj[2].GetShapeType());

	auto ptr = vPrObj[0].GetMaterial();
	EXPECT_EQ(31.5, ptr.GetEpsr());
	EXPECT_EQ(10.0, ptr.GetSigma());

	auto ptr2 = vPrObj[1].GetMaterial();
	EXPECT_EQ(1.5, ptr2.GetEpsr());
	EXPECT_EQ(0.0, ptr2.GetSigma());

	auto ptr3 = vPrObj[2].GetMaterial();
	EXPECT_EQ(3.5, ptr3.GetEpsr());
	EXPECT_EQ(0.0, ptr3.GetSigma());
}