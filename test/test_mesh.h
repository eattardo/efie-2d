/* This file contains tests for mesh.h implementation */
#include <sstream>
#include <fstream>      // std::ifstream
#include <string>
#include "gtest/gtest.h"
#include "../src/geometry/geometry.h"
#include "../src/mesh/mesh.h"
#include "../../json-develop/single_include/nlohmann/json.hpp"
#include "../src/json_reader/json_reader.h"

using namespace efie2d;

// Test constructor
TEST(MeshTest, Constructor)
{
  Mesh mesh2d;
  int backgroundId = mesh2d.GetBackgroundId();
  size_t numCells  = mesh2d.GetNumCells();

  EXPECT_EQ(0, backgroundId);
  EXPECT_EQ(0, numCells);
}


// Test SetNumCells
TEST(MeshTest, NumCells)
{
  Mesh mesh2d;
  // single cell
  Point2d aPoint = {1.0, 0.0};
  int aSize = 5;
  for (size_t i = 0; i < aSize; i++)
  {
	  mesh2d.cells.insert(std::pair<int,Point2d>(static_cast<int>(i), aPoint));
  }
  mesh2d.SetNumCells(mesh2d.cells.size());
  EXPECT_EQ(aSize, mesh2d.GetNumCells());
}


// Test GetCoordCellId
TEST(MeshTest, GetCoordCellId)
{
  Mesh mesh2d;
  int aSize = 5;
  // single point
  Point2d aPoint;
  for (int i = 0; i < aSize; ++i)
  {
    aPoint.x = static_cast<double>(i);
    aPoint.y = static_cast<double>(i);
    mesh2d.cells.insert(std::pair<int,Point2d>(i, aPoint));
  }
  mesh2d.SetNumCells(mesh2d.cells.size());

  aPoint = mesh2d.GetCoordCellAt(1);
  EXPECT_EQ(1.0, aPoint.x);
  EXPECT_EQ(1.0, aPoint.y);

  aPoint = mesh2d.GetCoordCellAt(4);
  EXPECT_EQ(4.0, aPoint.x);
  EXPECT_EQ(4.0, aPoint.y);
}

// Test Distance function
TEST(MeshTest, Distance)
{
  Mesh mesh2d;
  int aSize = 2;
  // single POINT
  Point2d aPoint;
  for (int i = 0; i < aSize; ++i)
  {
    aPoint = {static_cast<double>(0), static_cast<double>(2*i)};
    mesh2d.cells.insert(std::pair<int,Point2d>(i, aPoint));
  }
  mesh2d.SetNumCells(mesh2d.cells.size());

  double dist = computeDistance(mesh2d.GetCoordCellAt(0),
                                mesh2d.GetCoordCellAt(1));
  EXPECT_EQ(2, dist);
}

// Test constructor
TEST(MeshTest, RadiusTest)
{
  std::string filename = "../../../data/CircleTest1/circle_test1.json";
  JsonReader jsonObj(filename);
  jsonObj.ReadInput();
  // Create the geometry, which in turn, will create the mesh
  Geometry geo(jsonObj.resolution, jsonObj.vRec, jsonObj.vCirc, jsonObj.vMat, jsonObj.geo2Mat);
  Mesh& mesh2d = geo.GetMesh();
  // std::cout << mesh2d << std::endl;
  EXPECT_EQ( 0.5/2, mesh2d.GetAn());
}
