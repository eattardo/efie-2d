#ifndef POSTPROCESSING_FUN_H
#define POSTPROCESSING_FUN_H


#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <armadillo>
#include <complex_bessel.h>
#include "../src/mesh/mesh.h"
#include "../src/material/dielectric_parameters.h"
#include "../src/utils/stubs.h"
#include "../src/utils/physical_constants.h"

using namespace efie2d;

// Expected results in dB = -1.8429
// Expected results of field at the center: |.| = 0.78, Phi = -94.82

/**
 * @brief      Calculates the scattering cross section analitically
 *			   Assuming that the background is always free space
 *
 * @param[in]  Etot  Total electric field (one column)
 * @param[in]  mesh  The mesh reference
 * @param[in]  chi   The contrast reference
 * @param[in]  phi   The angle of incidence
 *
 * @return     The scattering cross section (linear)
 */
double computeScatteringCrossSection(const arma::cx_mat &Einc, const arma::cx_mat &Etot, const Mesh &mesh, const DielectricParameters &dielectricParams, const double phi)
{
	const std::complex<double> j(0.0,1.0);
	const double an = mesh.GetAn();
	const std::complex<double> kb = dielectricParams.kb;
	const std::complex<double> kb_an = kb * an;
	std::complex<double> cc = sp_bessel::besselJ(1, kb_an);
	// Start looping over the cells and compute the scattering cross section
	std::complex<double> sigma_tm(0.0,0.0);
	for (auto const& it : mesh.cells)
	{
		double xn = it.second.x;
		double yn = it.second.y;
		std::complex<double> ce = std::exp(+j*kb*(xn*std::cos(phi) + yn*std::sin(phi)));
		auto itChi = dielectricParams.chi.find(it.first);
		std::complex<double> chi = itChi->second;
		auto etot = Etot(it.first, 0);
		auto einc = Einc(it.first, 0);
		sigma_tm += chi * etot * cc * ce;
	}
	const std::complex<double> sigma_ = sigma_tm*std::conj(sigma_tm);
	double sigma = sigma_.real() * pi * pi * kb.real() * an;
	return sigma;
}


#endif // POSTPROCESSING_FUN_H