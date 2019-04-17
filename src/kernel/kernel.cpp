#include "kernel.h"
#include "../src/utils/stubs.h"

using namespace efie2d;

// Define only the ctor of the class
Kernel::Kernel(Mesh &mesh)
{
	// set the number of unknowns (or rows)
	dof = mesh.cells.size();
	// Square matrix
	Zmat.zeros(dof, dof); // allocate the memory and set to zero
}
//============================================



// Dtor of the Kernel class.Only set dof = 0
Kernel::~Kernel()
{
	dof = 0;
}


void Kernel::SaveZmatFile(const char* filename) const noexcept
{
	// we disable the writing on file if the matrix is bigger than
	// 500 x 500 elements
	if (Zmat.n_rows < 500)
		Zmat.save(filename, arma::arma_ascii);
}
//============================================


size_t Kernel::GetDoF() const noexcept
{
	return dof;
}
//============================================
