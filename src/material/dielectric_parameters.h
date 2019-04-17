#ifndef __DIELECTRIC_PARAMETERS_H__
#define __DIELECTRIC_PARAMETERS_H__

#include <complex>
#include <map>
#include "../src/geometry/geometry.h"

/* For a given frequency specified by an id
 * we are going to precompute the dielectric parameters
 * required for the forward solution.
*/
namespace efie2d
{

/**
 * @brief      Struct that holds info about the dielectric parameters
 */
class DielectricParameters
{
private:
	std::map<int,std::complex<double>> chi; ///< contrast
	std::complex<double> kb; ///< complex wavenumber of backgound
	std::complex<double> epsrcBackground; ///< complex relative permittivity of backgound
public:
	// Default ctor with init list
	DielectricParameters() : kb({0.0, 0.0}), epsrcBackground({1.0, 0.0}) {}


	/**
	 * @brief      Gets the contrast map
	 *
	 * @return     The reference to the map
	 */
	std::map<int,std::complex<double>>& GetChi() noexcept;

	/**
	 * @brief      Gets the wavenumber of the background
	 *
	 * @return     The kilobytes.
	 */
	std::complex<double> GetKb() noexcept;


	/**
	 * @brief      Gets the epsrc background.
	 *
	 * @return     The epsrc background.
	 */
	std::complex<double> GetEpsrcBackground() noexcept;

/**
 * @brief      Sets the dielectric parameters.
 *
 * @param[in]  w     angular frequency
 * @param      mesh  Mesh reference
 */
	void SetDielectricParameters(const double w, Geometry& geo);
};


} // namespace efie2d


#endif /* #ifndef __DIELECTRIC_PARAMETERS_H__ */