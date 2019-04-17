#ifndef __EXCITATION_H__
#define __EXCITATION_H__

#include <armadillo>
#include "../mesh/mesh.h"

/* This class handls the excitation vector.
 */

namespace efie2d
{

class Excitation
{
protected:
	size_t numOfExcitations; ///< number of excitations vectors
	size_t dof;	///< number of DoF of the matrix (num rows)
public:
	arma::cx_mat Einc;  ///< Einc dof x numOfExcitation

	/**
	 * @brief      Constructs the object Excitation
	 *
	 * @param      mesh             The mesh
	 * @param[in]  numOfExcitation  The number of excitation
	 */
	Excitation(Mesh& mesh, const size_t numOfExcitation);


	/**
	 * @brief      Move assignment operator.
	 *
	 * @param[in]  object  rvalue object
	 */
	Excitation(Excitation &&) noexcept;


	/**
	 * @brief      Destroys the object Excitation
	 */
	virtual ~Excitation()
	{
		Reset();
	};



	/**
	 * @brief      Reset function
	 */
	void Reset()
	{
		numOfExcitations = 0;
		dof = 0;
	}


	/**
	 * @brief      Gets the degree of freedom.
	 *
	 * @return     The degree of freedom.
	 */
	size_t GetDof() const noexcept;


	/**
	 * @brief      Gets the number excitations.
	 *
	 * @return     The number excitations.
	 */
	size_t GetNumExcitations() const noexcept;

};

} // namespace efie2d


#endif /* #ifndef __EXCITATION_H__ */