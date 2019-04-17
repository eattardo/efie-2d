#ifndef __PLANEWAVE_H__
#define __PLANEWAVE_H__

#include <armadillo>
#include <complex>
#include "excitation.h"

// Class planewave implements the plane wave excitations.
// It inherits from the base class Excitation.
namespace efie2d
{

class Planewave : public Excitation
{
public:


	/**
	 * @brief      Ctor of Planewave object
	 *
	 * @param      mesh             The mesh object
	 * @param[in]  numOfExcitation  The number of excitations
	 */
	Planewave(Mesh &mesh, const size_t numOfExcitation);


	Planewave(Mesh &mesh, const size_t numOfExcitation, std::complex<double> kb, const double startPhi,
					  const double );


	/**
	 * @brief      Destroys the plane wave object
	 */
	~Planewave() = default;

	/**
	 * @brief      Calculates the Einc for all the angles of incidence
	 *
	 * @param[in]      mesh    The mesh
	 * @param[in]  kb      The complex wavenumber
	 * @param[in]      phiInc  Vector that contains the phi-angle of incidence (rad)
	 */
	void ComputeEinc(Mesh &mesh, const std::complex<double> kb, arma::vec &phiInc);
};

} // namespace efie2d


#endif /* #ifndef __PLANEWAVE_H__ */