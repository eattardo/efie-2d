#ifndef __SOLVER_H__
#define __SOLVER_H__

#include <armadillo>
#include "../kernel/kernel.h"

namespace efie2d
{
/* Solver class is used for performing the solution of the linear system
 * The matrix and the RHS must be properly assembled and filled before
 * instanciating this class.
 * We prefer to have always available (and public) the reference to the objects.
*/
class Solver
{
public:
	Kernel* matPtr; ///< pointer to the base class Kernel
	arma::cx_mat* EincPtr; ///< pointer to the base incident fields
	arma::cx_mat Etot;  ///< Etot (solution of the linear system) dof x numOfExcitation


	/**
	 * @brief      Solver ctor
	 *
	 * @param[in]  Mat   The reference to the matrix
	 * @param[in]  Einc  The reference to the incident field
	 */
	Solver(Kernel &Mat, arma::cx_mat &Einc);


	/**
	 * @brief      Solver dtor
	 */
	~Solver() = default;


	/**
	 * @brief      Solve the linear system
	 */
	void Solve();


	/**
	 * @brief      Calculates the residua of the solutions
	 *
	 * @param      residuaVec  The residua vector
	 */
	void ComputeResidua(arma::vec& residuaVec);
};

} // namespace efie2d


#endif /* #ifndef __SOLVER_H__ */