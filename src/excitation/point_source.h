#ifndef __POINT_SOURCE_H__
#define __POINT_SOURCE_H__

#include <complex>
#include <vector>
#include "excitation.h"
#include "../mesh/point2d.h"

// Class planewave implements the plane wave excitations.
// It inherits from the base class Excitation.
namespace efie2d
{

class PointSource : public Excitation
{
public:


	/**
	 * @brief      Ctor of PointSource object
	 *
	 * @param      mesh             The mesh object
	 * @param[in]  numOfExcitation  The number of excitations
	 */
	PointSource(Mesh &mesh, const size_t numOfExcitation);

	/**
	 * @brief      Destroys the PointSource
	 */
	~PointSource() = default;

	/**
	 * @brief      Calculates the Einc for all the point sources
	 *
	 * @param[in]      mesh    The mesh
	 * @param[in]  		 kb      wavenumber of Background
	 * @param[in]      pointSourceRt  Vector that contains the position of point sources
	 */
	void ComputeEinc(Mesh &mesh, const std::complex<double> kb,
					 const std::vector<Point2d> &pointSourceRt, const std::vector<std::complex<double>> &Ie,
					 const double w);
};

} // namespace efie2d


#endif /* #ifndef __POINT_SOURCE_H__ */