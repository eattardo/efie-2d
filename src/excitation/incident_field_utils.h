#ifndef INCIDENT_FIELD_UTILS__H__
#define INCIDENT_FIELD_UTILS__H__

#include "..\mesh\mesh.h"
#include "..\material\dielectric_parameters.h"
#include "..\preprocessing\input_file.h"
/**
 * @brief      Creates a planewave excitation.
 *
 * @param[in]  inputFile         The input file
 * @param      mesh2d            The mesh 2 d
 * @param      dielectricParams  The dielectric parameters
 *
 * @return     Created Einc
 */
arma::cx_mat CreatePlanewaveExcitation(const InputFile &inputFile, Mesh &mesh2d,
                                       DielectricParameters &dielectricParams)
{
  // Return immediately if it is not a plw
	if (inputFile.numPlws == 0 || inputFile.numPts != 0)
	{
		message("A planewave excitation is required");
    exit(1);
	}
  // Create planewave excitations
  size_t numOfExcitations = inputFile.numPlws;
  double startPhi = Deg2Rad(inputFile.startPhi);
  double endPhi = Deg2Rad(inputFile.endPhi);
  arma::vec phiInc = arma::linspace(startPhi, endPhi, numOfExcitations);
  // create the planewave obj
  Planewave plw(mesh2d, numOfExcitations);
  // set the excitation
  plw.ComputeEinc(mesh2d, dielectricParams.kb, phiInc);
  // Is this copy needed?
  arma::cx_mat Einc = plw.Einc;
  return Einc;
}
//============================================


#endif /* #ifndef INCIDENT_FIELD_UTILS__H__ */