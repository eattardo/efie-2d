/* This file contains tests for mesh.h implementation */

#include <string>
#include <iterator>
#include "gtest/gtest.h"
#include "../../json-develop/single_include/nlohmann/json.hpp"
#include "../src/json_reader/json_reader.h"

using namespace efie2d;
using namespace std;

// Test constructor
TEST(InputFileTest, TestExample1)
{
	string filename = "../../../data/PetersonCylinder/PetersonCyl.json";
	JsonReader jsonObj(filename);
	EXPECT_EQ(0, jsonObj.vRec.size());
	EXPECT_EQ(1, jsonObj.vCirc.size());
	EXPECT_EQ(0.0085, jsonObj.resolution);
	EXPECT_EQ(1, jsonObj.vMat.size());
}

#if 0
TEST(InputFileTest, TestExample2)
{
	InputFile inputFile;
	string filename = "../../test_example2.json";
	// read the input file and store info in inputFile
	ReadInputFile(filename, inputFile);
	EXPECT_EQ(3, inputFile.numObjs);
	EXPECT_EQ(1, inputFile.vRec.size());
	EXPECT_EQ(2, inputFile.vCirc.size());
	EXPECT_EQ(0.1, inputFile.resolution);
	EXPECT_EQ(1, inputFile.vFreq.size());
	EXPECT_EQ(1, inputFile.numFreq);
	EXPECT_EQ(3, inputFile.numMat);
	EXPECT_EQ(3, inputFile.vMat.size());
	// grab the material and test it
	std::map<int,Material>::iterator iter = inputFile.vMat.find(1);
	EXPECT_EQ(1.5, iter->second.GetEpsr());
	EXPECT_EQ(0, iter->second.GetSigma());
	// mat 2
	std::map<int,Material>::iterator iter_ = inputFile.vMat.find(2);
	EXPECT_EQ(3.5, iter_->second.GetEpsr());
	EXPECT_EQ(0, iter_->second.GetSigma());
	// mat 3
	std::map<int,Material>::iterator iter_3 = inputFile.vMat.find(3);
	EXPECT_EQ(31.5, iter_3->second.GetEpsr());
	EXPECT_EQ(10.0, iter_3->second.GetSigma());
	// Rectangle check
	Point2d aPt;
	std::map<int,Rectangle>::iterator iter2 = inputFile.vRec.find(2);
	aPt = iter2->second.pMin;
	EXPECT_EQ(0, aPt.x);
	EXPECT_EQ(0, aPt.y);
	aPt = iter2->second.pMax;
	EXPECT_EQ(5, aPt.x);
	EXPECT_EQ(5, aPt.y);
	// Circle check
	std::map<int,Circle>::iterator iter3 = inputFile.vCirc.find(1);
	aPt = iter3->second.center;
	EXPECT_EQ(0.2, aPt.x);
	EXPECT_EQ(0.2, aPt.y);
	// Circle check
	std::map<int,Circle>::iterator iter4 = inputFile.vCirc.find(3);
	aPt = iter4->second.center;
	EXPECT_EQ(0.9, aPt.x);
	EXPECT_EQ(0.9, aPt.y);
}
#endif