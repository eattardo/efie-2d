#ifndef __POINT2D_H__
#define __POINT2D_H__

#include <iostream>
#include <set>
#include <cmath>       /* sqrt */

namespace efie2d
{

/**
 * @brief      Point 2d
 */
struct Point2d
{
	double x; ///< x-coord
	double y; ///< y-coord

	Point2d() : x(0.0), y(0.0) {} //empty ctor
	Point2d(const double x_, const double y_) : x(x_), y(y_) {} //ctor from (x,y)

	// Copy operator
	//
	// @param[in]  a     Point to be copied
	//
  inline void operator=(const Point2d& a)
  {
    x = a.x;
    y = a.y;
  }
};


/**
 * @brief      Calculates the distance between two points
 *
 * @param[in]  pointA  The point a
 * @param[in]  pointB  The point b
 *
 * @return     The distance.
 */
inline double computeDistance(const Point2d& pointA,
					   const Point2d& pointB)
{
	double dx = pointA.x - pointB.x;
	double dy = pointA.y - pointB.y;
	return (std::sqrt(dx*dx + dy*dy));
}


inline double computeDistance(const double x, const double y,
					   const Point2d& pointA)
{
	double dx = x - pointA.x;
	double dy = y - pointA.y;
	return (std::sqrt(dx*dx + dy*dy));
}


/* Operator<< (to use std:cout << Point2d <<)
 *
 * @param      out   Output stream
 * @param[in]  a     the Point2d to be printed
 *
 * @return     Output stream
 */
inline std::ostream& operator<<(std::ostream &out, const Point2d& a)
{
  out << "(" << a.x << ", " << a.y << ")";
  return out;
}


} // namespace efied2d

#endif //__POINT2D_H__
