#ifndef EFIE2D_TYPES_H
#define EFIE2D_TYPES_H
// Definition of alias for datatype used in EFIE2D

#include <complex>
#include "../src/mesh/point2d.h"
#include "../src/mesh/primitive_objects.h"
#include "../src/material/material.h"
#include "../src/solver/frequency.h"

using chi_t  = std::map<int,std::complex<double>>; // contrast container datatype
using cell_t = std::map<int,Point2d>; // cell container datatype
using rectangle_t = std::map<int,Rectangle>; // rect container datatype
using circle_t = std::map<int,Circle>; // circ container datatype
using frequency_t = std::map<int, Frequency > ; // frequency container datatype
using material_t = std::map<int,Material>; // material container datatype

#endif /* #ifndef EFIE2D_TYPES_H */
