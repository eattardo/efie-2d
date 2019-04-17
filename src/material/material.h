#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <complex>

namespace efie2d
{

/**
 * @brief      Material object
 *
 * Definition of the class for handling a material object.
 */
class Material
{
private:
	int id; ///< id of the material
	double epsr; ///< relative permittivity
	double sigma; ///< conductivity S/m
public:
	std::complex<double> epsrc; ///< complex relative permittivity (public for quick access)


	/**
	 * @brief      Constructs the Material class.
	 */
	Material();


	/**
	 * @brief      Ctor of the obj material
	 *
	 * @param[in]  id_     The identifier
	 * @param[in]  epsr_   The epsr
	 * @param[in]  sigma_  The sigma
	 * @param[in]  freq    The frequency
	 */
	Material( const int id_,
					  const double epsr_,
					  const double sigma_,
					  const double freq);

	/**
	 * @brief      Destroys Material object
	 */
	~Material() = default;


	Material& operator=(const Material& mat);

	Material& operator=(const Material* ptrMat);

	/**
	 * @brief      Sets all identifiers
	 *
	 * @param[in]  id_  The id of the obj for which this mat is defined
	 */
	void SetId(const int id_);


	/**
	 * @brief      Sets the complex relative permittivity
	 *
	 * @param[in]  epsr_   The relative permittivity
	 * @param[in]  sigma_  The conductivity
	 * @param[in]  freq    Freq for the material
	 */
	void SetEpsrc( const double epsr_,
								const double sigma_,
								const double freq);


	/**
	 * @brief      Gets the relative permittivity
	 *
	 * @return     The epsr.
	 */
	double GetEpsr() const noexcept;


	/**
	 * @brief      Gets the conductivity
	 *
	 * @return     The sigma.
	 */
	double GetSigma() const noexcept;



	/**
	 * @brief      Gets the complex epsrc = epsr - j*sigma/(w*eps0)
	 *
	 * @return     The complex epsr.
	 */
	std::complex<double> GetComplexEpsr() const noexcept;

/**
	 * @brief      Gets the id of the primitive obj
	 *
	 * @return     The sigma.
	 */
	int GetId() const noexcept;


	Material* GetMaterialFromId(const int id_);
};

} // namespace efied2d

#endif //__MATERIAL_H__
