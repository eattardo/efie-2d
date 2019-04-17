/* Implementation of the class MaterialObj */
#include <iostream>
#include "material.h"
#include "../utils/physical_constants.h"

using namespace efie2d;

// Default constructor
Material::Material()
{
	id = 0;
	epsr = 1.0;
	sigma = 0.0;
	epsrc = std::complex<double>(1.0,0.0);
}
//============================================


Material::Material(const int id_,
					 				 const double epsr_,
					 				 const double sigma_,
					 				 const double freq)
{
  SetId(id_);
  // Set the material parameters
  SetEpsrc(epsr_, sigma_, freq);
}
//============================================


Material& Material::operator=(const Material& mat)
{
	id = mat.GetId();
	epsr = mat.GetEpsr();
	sigma = mat.GetSigma();
	epsrc = mat.GetComplexEpsr();
	return *this;
}
//============================================

Material& Material::operator=(const Material* ptrMat)
{

	id = ptrMat->GetId();
	epsr = ptrMat->GetEpsr();
	sigma = ptrMat->GetSigma();
	epsrc = ptrMat->GetComplexEpsr();
	return *this;
}




void Material::SetId(const int id_)
{
	id = id_;
}
//============================================


void Material::SetEpsrc( const double epsr_,
							const double sigma_,
							const double freq)
{
		// Set permittivity and conductivity
		epsr  = epsr_;
		sigma = sigma_;

		double w = 2*pi*freq;
	  // check for zero angular frequency
    if (w < 1e-6)
    {
    	std::cout << "Angular Frequency is zero" << std::endl;
    	exit(1);
    }
    else
    {
    	// relative complex permittivity: epsr - j sigma/(w*eps0)
			epsrc = std::complex<double>(epsr, -sigma/(w*eps0));
		}
	}
	//============================================


	double Material::GetEpsr() const noexcept
	{
		return epsr;
	}
	//============================================


	double Material::GetSigma() const noexcept
	{
		return sigma;
	}
	//============================================


	std::complex<double> Material::GetComplexEpsr() const noexcept
	{
		return epsrc;
	}


  int Material::GetId() const noexcept
  {
    return id;
  }
  //============================================


	Material* Material::GetMaterialFromId(const int id_)
	{
		if (id == id_)
			return this;
		else
			return nullptr;
	}
  //============================================