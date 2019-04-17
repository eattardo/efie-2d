#ifndef __AI_KER_H__
#define __AI_KER_H__

#include "kernel.h"

namespace efie2d
{

// This integral equation kernel is based on the so-called
// Contrast sorce integral equation (CS-IE) (Van den Berg).
// The CS-IE is an EFIE obtained from the volumetric equivalence principle.
// The discretization is done with pulse basis functions and the testing with
// Dirac's delta.
// Only infinite cylinder geometry are considered in the plane xy.
// This means that the polarized of the fields is always Ez (we consider TM polarization).
//
class AiKer : public Kernel
{
public:


	/**
	 * @brief      Ctor of the class
	 *
	 * @param      mesh  The mesh object
	 */
	AiKer(Mesh &mesh);

	/**
	 * @brief      Dtor of the class
	 */
	~AiKer() = default;

	/**
	 * @brief      Assemble the entire Z matrix
	 *
	 * @param[in]  dielectricParams  The dielectric parameters object
	 * @param[in]  mesh              The mesh object
	 */
	virtual void AssembleZmat(DielectricParameters &dielectricParams, Mesh &mesh);


	/**
	 * @brief      Assembling of irow of the matrix Considering symmetry Z(i,j) =
	 *             Z(j,i)
	 *
	 * @param[in]  irow              The irow
	 * @param[in]  aa                { parameter_description }
	 * @param[in]  dielectricParams  The dielectric parameters
	 * @param[in]  mesh              The mesh
	 */
	virtual void AssembleZmatRow(const int irow, const double aa, DielectricParameters &dielectricParams,
                                Mesh &mesh);
}; // end class AiKer

} // namespace efie2d

#endif /* #ifndef __AI_KER_H__ */