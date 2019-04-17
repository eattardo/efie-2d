#include "excitation.h"

using namespace efie2d;

// Ctor implementation of the class
Excitation::Excitation(Mesh &mesh, const size_t numOfExcitation_)
{
	// set the number of unknowns (or rows)
	dof = mesh.cells.size();
	numOfExcitations = numOfExcitation_;
	// Square matrix
	Einc.zeros(dof, numOfExcitations); // allocate the memory and set to zero
}
//============================================


Excitation::Excitation(Excitation &&rhs) noexcept
{
	Einc = std::move(rhs.Einc);
	dof = rhs.dof;
	numOfExcitations = rhs.GetNumExcitations();
	rhs.Reset();
}
//============================================


size_t Excitation::GetDof() const noexcept
{
	return dof;
}
//============================================


size_t Excitation::GetNumExcitations() const noexcept
{
	return numOfExcitations;
}
//============================================
