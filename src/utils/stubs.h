#ifndef __STUBS_H__
#define __STUBS_H__

#include "efie2d_version.h" // automatically generated inlcude file
#include "physical_constants.h"
#include <armadillo>

namespace efie2d
{

/**
 * @brief      Util fun to print the usage of the main
 *
 * @param[in]  argv0  The argv 0
 */
inline void printUsageAndExit(const char* argv0)
{
	std::cerr
		<< "Usage  : " << argv0 << " [options]\n"
		<< "App options:\n"
		<< "  -h  | --help                               Print this usage message\n"
		<< "  -in  | --input <*.input file>               Specify INPUT file\n"
		<< std::endl;

	exit(1);
}
//=========================================================================================


/**
 * @brief      Prints the logo
 */
inline void printLogo()
{
	std::system("cls");
	std::cout << "*****************************************************************************************\n";
	std::cout << "*                                                                                        *\n";
	std::cout << "*                                                                                        *\n";
	std::cout << "*                                      EFIE2D                                            *\n";
	std::cout << "*                                  Elia. A. Attardo                                      *\n";
	std::cout << "*                                                                                        *\n";
	std::cout << "*                               Version: " << GIT_TAG << "-" << GIT_COMMIT_HASH << "                                     *\n";
	std::cout << "*                                                                                        *\n";
	std::cout << "******************************************************************************************\n";
}
//=========================================================================================.



/**
 * @brief      Print a message to the std::cout
 *
 * @param[in]  s     { parameter_description }
 */
inline void message(const char* s)
{
    puts(s);
    fflush(stdout);
}
//============================================

/**
 * @brief      Parses the input arguments
 *
 * @param[in]  argc           The main's argc
 * @param      argv           The main's argv
 * @param      inputFilename  The input filename
 */
inline void parseInput(const int argc, char** argv, std::string& inputFilename)
{
	// parse arguments
	for (int i = 1; i < argc; ++i)
	{
		std::string arg(argv[i]);
		if (arg == "-h" || arg == "--help")
		{
			printUsageAndExit(argv[0]);
		}
		else if ((arg == "-in" || arg == "--input") && i + 1 < argc)
		{
			inputFilename = argv[++i];
		}
		else
		{
			std::cerr << "Bad options: '" << arg << "'" << std::endl;
			printUsageAndExit(argv[0]);
		}
	}

}
//==========================================================================================

/**
 * @brief      Convert from degree to radiant
 *
 * @param[in]  degree  The angle in degrees
 *
 * @return     The angle in radiant
 */
inline double Deg2Rad(const double degree)
{
	return degree * pi / 180.0;
}
//============================================


/**
 * @brief      Convert from rad to degrees
 *
 * @param[in]  rad   The angle in radiant
 *
 * @return     Angle in degree
 */
inline double Rad2Deg(const double rad)
{
	return rad * 180.0 / pi;
}
//============================================


/**
 * @brief      Calculates the frobenius normalize.
 *
 * @param[in]  Zmat  The zmat
 *
 * @return     The frobenius normalize.
 */
inline double ComputeFrobeniusNorm(const arma::cx_mat &Zmat)
{
	size_t numRows = Zmat.n_rows;
	size_t numCols = Zmat.n_cols;
	double FrobNorm = 0.0;
	for (size_t i = 0; i < numRows; i++)
	{
		for (size_t j = 0; j < numCols; j++)
		{
			FrobNorm += Zmat(i,j).real()*Zmat(i,j).real() + Zmat(i,j).imag()*Zmat(i,j).imag();
		}
	}
	FrobNorm = std::sqrt(FrobNorm);
	return FrobNorm;
}
//============================================

} // namespace efie2d

#endif /* #ifndef __STUBS_H__ */
