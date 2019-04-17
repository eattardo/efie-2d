/* This file contains tests for mesh.h implementation */
#include <map>

#include "gtest/gtest.h"
#include "../src/material/material.h"
#include "../src/utils/physical_constants.h"

using namespace efie2d;
using namespace std;

// Test constructor
TEST(MaterialTest, ConstructorEmpty)
{
	Material mat;
	int id;
	id = 0;
	double epsr = 1.0;
	double sigma = 0.0;
	EXPECT_EQ(id, mat.GetId());
	EXPECT_EQ(epsr, mat.GetEpsr());
	EXPECT_EQ(sigma, mat.GetSigma());
}

// Test constructor
TEST(MaterialTest, Empty)
{
int id = 100;
double epsr = 1.5;
double sigma = 0.1;
double freq = 1e9;
// call the ctor
Material mat(id, epsr, sigma, freq);
EXPECT_EQ(id, mat.GetId());
EXPECT_EQ(epsr, mat.GetEpsr());
EXPECT_EQ(sigma, mat.GetSigma());
}

// Test constructor
TEST(MaterialTest, SetAllId)
{
	int id = 100;
	// call the ctor
	Material mat;
	mat.SetId(id);

	EXPECT_EQ(id, mat.GetId());
}

// Test return ptr
TEST(MaterialTest, MatFromId)
{
	int id = 100;
	// call the ctor
	Material mat;
	mat.SetId(id);

	Material* rightPtr = mat.GetMaterialFromId(id);
	Material* WrongPtr = mat.GetMaterialFromId(1);
	EXPECT_EQ(id, rightPtr->GetId());
	EXPECT_FALSE(WrongPtr);
}

