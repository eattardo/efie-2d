/* Implementation of the class Frequency */
#include "frequency.h"
#include "../utils/physical_constants.h"

using namespace efie2d;

Frequency::Frequency(const double f_)
{
	SetFrequency(f_);
}
//============================================


void Frequency::SetFrequency(const double f_)
{
	f = f_;
	w = 2*pi*f; // set angular frequency
}
//============================================


double Frequency::GetFrequency() const noexcept
{
	return f;
}
//============================================


double Frequency::GetOmega() const noexcept
{
	return w;
}
//============================================






