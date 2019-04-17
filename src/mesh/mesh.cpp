/* Implementation of the class Mesh */

#include "mesh.h"
#include <iostream>
#include <iterator>     // std::iterator
#include <algorithm>
#include <armadillo>
#include "utils\stubs.h"

using namespace efie2d;

Mesh::Mesh()
{
	backgroundId = 0;
	numOfCells   = 0;
	an = 0.0;
}
//============================================


void Mesh::SetBackgroundId(const int backgroundId_) noexcept
{
	backgroundId = backgroundId_;
}
//============================================


void Mesh::SetNumCells(const size_t numOfCells_) noexcept
{
	numOfCells = numOfCells_;
}
//=============================================

void Mesh::SetAn(const double resolution) noexcept
{
	// The resolution that we use to build the mesh,
	// represent the distance of two adjacent square cells.
	// Take half of this distance.
	an = resolution / 2;
}


int Mesh::GetBackgroundId() const noexcept
{
	return backgroundId;
}
//============================================


size_t Mesh::GetNumCells() const noexcept
{
	return numOfCells;
}
//============================================


Point2d Mesh::GetCoordCellAt(const int i)
{
	Point2d center;
	// define an iterator
	std::map<int,Point2d>::iterator iter = cells.find(i);
	if (iter != cells.end())
	{
		center = iter->second;
  }
  else
  {
  	std::cout << "Mesh id not found "<<std::endl;
    exit(1);
  }
  return center;
}
//============================================


double Mesh::GetAn() const noexcept
{
	return an;
}
//============================================


/**
 * @brief      Creates a mesh from background circle.
 *
 * @param[in]  circ        The circ object
 * @param[in]  resolution  The resolution
 * @param[in, out]      mesh        The mesh. Id of the cell must start from 0
 *
 * @return     { description_of_the_return_value }
 */
int Mesh::CreateMeshFromBackgroundCircle(Circle *circ, const double resolution)
{
	int error = 0;
	// Clear the map once we enter here
	cells.clear();
	// We assume that circle is envoloped within an equivalent square
	double xmin = circ->center.x - circ->radius;
	double xmax = circ->center.x + circ->radius;
	double ymin = circ->center.y - circ->radius;
	double ymax = circ->center.y + circ->radius;

	// Detect the number of points needed for the resolution
	size_t nx = static_cast<size_t>( (xmax - xmin + resolution) / resolution );
	size_t ny = static_cast<size_t>( (ymax - ymin + resolution) / resolution );
	if (nx!=ny)
	{
		error = 5;
		message("Circle must be envoled within a square");
		return error;
	}
	// Create the linspace of the x and y coordinates
	arma::vec xCoord = arma::linspace(xmin, xmax, nx);
	arma::vec yCoord = arma::linspace(ymin, ymax, ny);
	Point2d aPt;
	int id = 0;
	for (int i = 0; i < nx; ++i)
	{
		for (int j = 0; j < ny; ++j)
		{
			aPt = {xCoord[i], yCoord[j]};
			// take this cell
			if (computeDistance(aPt, circ->center) <= circ->radius)
			{
				cells.insert(std::pair<int,Point2d>(id, aPt));
				id++;
			}
		}
	}
	SetNumCells(cells.size());

	return error;
}
//============================================


/**
* @brief      Creates a mesh from background circle.
*
* @param[in]  circ        The circ object
* @param[in]  resolution  The resolution
* @param[in, out]      mesh        The mesh. Id of the cell must start from 0
*
* @return     { description_of_the_return_value }
*/
int Mesh::CreateMeshFromBackgroundRectangle(Rectangle *rec, const double resolution)
{
	int error = 0;
	// Clear the map once we enter here
	cells.clear();
	// We assume that circle is envoloped within an equivalent square
	double xmin = rec->pMin.x;
	double xmax = rec->pMax.x;
	double ymin = rec->pMin.y;
	double ymax = rec->pMax.y;

	// Detect the number of points needed for the resolution
	size_t nx = static_cast<size_t>((xmax - xmin + resolution) / resolution);
	size_t ny = static_cast<size_t>((ymax - ymin + resolution) / resolution);

	// Create the linspace of the x and y coordinates
	arma::vec xCoord = arma::linspace(xmin, xmax, nx);
	arma::vec yCoord = arma::linspace(ymin, ymax, ny);
	Point2d aPt;
	int id = 0;
	for (int i = 0; i < nx; ++i)
	{
		for (int j = 0; j < ny; ++j)
		{
			aPt = { xCoord[i], yCoord[j] };
				cells.insert(std::pair<int, Point2d>(id, aPt));
				id++;
		}
	}
	SetNumCells(cells.size());
	return error;
}
//============================================


/**
 * @brief      Generates the mesh (after reading the input file)
 *
 * @param      inputFile  The input file
 * @param      mesh       The mesh
 *
 * @return     error code
 */
int Mesh::GenerateMesh(const double resolution, std::vector<PrimitiveObj>& vPrObj)
{
	int error = 0; // no error detected

	// the background is given by the primitive object
	// that has minimum id.
	if (vPrObj.size() < 0)
	{
		error = 1;
		message("Number of primitive objs is not valid");
		return error;
	}

  auto backgroundId = std::min_element(std::begin(vPrObj), std::end(vPrObj));
  SetBackgroundId(backgroundId->GetShapeId());
  // where is in the vector
  size_t pos = std::distance(std::begin(vPrObj), backgroundId);
  // It's a rectangle
  if (vPrObj[pos].GetShapeType()==ShapeType::Rec)
  {
  	// cast to a proper rectangle object
  	Rectangle* ptrRec = static_cast<Rectangle*>(vPrObj[pos].GetShape());
    error = CreateMeshFromBackgroundRectangle(ptrRec, resolution);
    if (error!=0)
    {
      message("Error in creating the mesh from Rectangle");
      return error;
    }
  }
  // background is Circle
  else
  {
  	Circle* ptrCirc = static_cast<Circle*>(vPrObj[pos].GetShape());
    error = CreateMeshFromBackgroundCircle(ptrCirc, resolution);
    if (error!=0)
    {
      message("Error in creating the mesh from Circle");
      return error;
    }
  }

	// Set the radius of the single cells in the mesh
	SetAn(resolution);
	return error;
} // GenerateMesh
//============================================


namespace efie2d
{
	std::ostream& operator<<(std::ostream &os, const Mesh &mesh2d)
	{
		for (auto const& it : mesh2d.cells)
		{
			os << it.first  // id of the cell
				<< ':'
				<< it.second // Point value
				<< std::endl;
		}
		return os;
	}
}