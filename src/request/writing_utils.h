#ifndef __WRITING_UTILS_H__
#define __WRITING_UTILS_H__

#include <iomanip>      // std::setprecision
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
#include <fstream>      // std::ofstream
#include <armadillo>
#include <complex_bessel.h>
#include "../src/mesh/mesh.h"
#include "../solver/solver.h"
#include "../src/material/dielectric_parameters.h"
#include "../src/utils/stubs.h"
#include "../src/utils/physical_constants.h"

using namespace efie2d;


/**
 * @brief      Writes the (epsr, sigma) from Chi on file
 *
 * @param[in]  filename          The filename
 * @param[in]  dielectricParams  The dielectric parameters struct
 * @param[in]  mesh              The mesh objects
 */
void writeEpsrSigmaFile(const char* filename, DielectricParameters &dielectricParams,
				  const Mesh &mesh, const double w) noexcept
{
	// check that chi is same size mesh.cells
	if (dielectricParams.GetChi().size() != mesh.cells.size())
	{
		message("Chi does not match the cells size");
		exit(1);
	}

	std::ofstream outFile;
	outFile.open(filename);

	for (auto const& itChi : dielectricParams.GetChi())
	{
		int id = itChi.first;
		std::complex<double> tmpCmplx = dielectricParams.GetEpsrcBackground() * (itChi.second + 1.0);
		double epsr = tmpCmplx.real();
		double sigma = -tmpCmplx.imag() * w * eps0;
		double x = mesh.cells.at(id).x;
		double y = mesh.cells.at(id).y;
		outFile << std::fixed << std::setprecision(10) << x << "\t" <<
			std::fixed << std::setprecision(10) << y << "\t" <<
			std::fixed << std::setprecision(10) << epsr << "\t" <<
			std::fixed << std::setprecision(10) << sigma << std::endl;
	}
	outFile.close();
}
//============================================


/**
 * @brief      Writes the contrast on source file
 *
 * @param[in]  filename          The filename
 * @param[in]  dielectricParams  The dielectric parameters struct
 * @param[in]  mesh              The mesh objects
 */
void writeChiFile(const char* filename, DielectricParameters &dielectricParams,
				  const Mesh &mesh) noexcept
{
	// check that chi is same size mesh.cells
	if (dielectricParams.GetChi().size() != mesh.cells.size())
	{
		message("Chi does not match the cells size");
		exit(1);
	}

	std::ofstream outFile;
	outFile.open(filename);

	for (auto const& itChi : dielectricParams.GetChi())
	{
		int id = itChi.first;
		double realChi = itChi.second.real();
		double imagChi = itChi.second.imag();
		double x = mesh.cells.at(id).x;
		double y = mesh.cells.at(id).y;
		outFile << std::fixed << std::setprecision(10) << x << "\t" <<
			std::fixed << std::setprecision(10) << y << "\t" <<
			std::fixed << std::setprecision(10) << realChi << "\t" <<
			std::fixed << std::setprecision(10) << imagChi << std::endl;
	}
	outFile.close();
}
//============================================


/**
 * @brief      Writes the solution Etot on file ready to be plotted with Octave.
 *             File format is: x-cell | y-cell | Real(Etot) | Imag(Etot)
 *
 * @param[in]  filename  The filename
 * @param[in]  Etot      The Etot (col of the solution field)
 * @param[in]  mesh      The mesh reference
 */
void writeEtotfile(const char* filename, const arma::cx_vec &Etot,
									const Mesh &mesh) noexcept
{
	std::ofstream outFile;
	outFile.open(filename);

	// Get the number of cells of the mesh
	arma::mat EtotReal = arma::real(Etot);
	arma::mat EtotImag = arma::imag(Etot);

	// Iterate over the celss
	for (auto const& it : mesh.cells)
	{
		outFile << std::fixed << std::setprecision(10) << it.second.x << "\t" <<
			std::fixed << std::setprecision(10) << it.second.y << "\t" <<
			std::fixed << std::setprecision(10) << EtotReal(it.first) << "\t" <<
			std::fixed << std::setprecision(10) << EtotImag(it.first) << std::endl;
	}
	outFile.close();
}
//============================================


/**
 * @brief      Writes the total E-field on file after extracting on a line
 *             parallel to x = a (flag=1), or parallel to y = a (flag=2)
 *
 * @param[in]  flag      The flag indicates where we want to plot the field on
 *                       the line (1: line parallel to x=a, 2 y=a)
 * @param[in]  filename  The filename
 * @param[in]  Etot      The Etot i-th col
 * @param[in]  mesh      The mesh
 * @param[in]  a         x, or y == a (for selecting the line)
 */
void writeEtotLine(const int flag, const char *filename,
									 const arma::cx_vec &Etot, const Mesh &mesh, const double a) noexcept
{
	double dmin = 1e20; // set to a huge number
	// get the radius of the mesh cell
	double an = mesh.GetAn();

	// Strem for opening file
	std::ofstream outFile;
	outFile.open(filename);

	// Get the number of cells of the mesh
	arma::mat EtotReal = arma::real(Etot);
	arma::mat EtotImag = arma::imag(Etot);
	if (flag==2) // along y=a, x-all
	{
		// Iterate over the cells to find the closest one with y almost a
		for (auto const& it : mesh.cells)
		{
			// take this cell
			double d = it.second.y - a; d = std::sqrt(d*d);
			dmin = std::min(dmin, d);
		}
		// Iterate over the cells to find the closest one with y almost a
		for (auto const& it : mesh.cells)
		{
			// It is possible that we have cells with same x but +y0 and -y0
			// Select only the positive
			if (it.second.y > 0.0)
			{
				if (it.second.y - dmin < 1e-6)
				{
						outFile << std::fixed << std::setprecision(10) << it.second.x << "\t" <<
						std::fixed << std::setprecision(10) << it.second.y << "\t" <<
						std::fixed << std::setprecision(10) << EtotReal(it.first) << "\t" <<
						std::fixed << std::setprecision(10) << EtotImag(it.first) << std::endl;
				  }
				}
		} // for mesh.cells
	} // flag==1
	else if (flag==1) // along x=a, y-all
	{
		std::cerr<<"No plot on x for the moment\n";
	} // flag==1
}
//============================================


#endif /* #ifndef __WRITING_UTILS_H__ */