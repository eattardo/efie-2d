#ifndef __KERNEL_H__
#define __KERNEL_H__

#include <armadillo>
#include "../mesh/mesh.h"
#include "../material/dielectric_parameters.h"

namespace efie2d
{

// Base abstract class for representing different IE kernels
class Kernel
{
protected:
  size_t dof; ///< number of unknowns (DoF) in the matrix
public:

  // Public for quick access
  arma::cx_mat Zmat;  ///< complex<double> impedance matrix


  /**
   * @brief      Constructs the kernel object
   */
  Kernel(Mesh &mesh);


  /**
   * @brief      Destroys the kernel object
   */
  ~Kernel();


  /**
   * @brief      Assemble the whole impedance matrix
   */
  virtual void AssembleZmat(DielectricParameters &dielectricParams, Mesh &mesh) = 0; // pure virtual


  /**
   * @brief      Assemble only the i-th row of the impedance matrix
   *
   * @param[in]  irow  The i-th row of the matrix
   * @param[in]  freq  The frequency object
   * @param[in]  mesh  The mesh object
   */
  virtual void AssembleZmatRow( const int irow, DielectricParameters &dielectricParams, Mesh &mesh) = 0;  // virtual


  /**
   * @brief      Saves the impedance matrix on file
   *
   * @param[in]  filename  The filename
   */
  void SaveZmatFile(const char* filename) const noexcept;


  /**
   * @brief      Gets the dof.
   *
   * @return     The DoF (number of rows or cols)
   */
  size_t GetDoF() const noexcept;
}; // end abstract class

} // namespace efie2d
#endif /* #ifndef __KERNEL_H__ */
