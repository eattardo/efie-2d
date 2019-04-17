#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <map>
#include "../mesh/point2d.h"

namespace efie2d
{

/**
 * @brief      Enum: Circle or Rectangle
 */
enum ShapeType { Circ, Rec };

/**
 * @brief      Base shape class
 *			   Declare as public the member
 */
class Shape
{
public:
	int id; ///< id of the shape object

	/**
	 * @brief      copy operator
	 *
	 * @param[in]  sh    Shape obj reference
	 *
	 * @return     reference
	 */
	Shape& operator=(const Shape& sh)
	{
		id = sh.id;
		return *this;
	}
	//============================================

	/**
	 * @brief      Gets the identifier.
	 *
	 * @return     The identifier.
	 */
	int GetId()
	{
		return id;
	}
	//============================================

	inline bool operator<(const Shape& rhs) const
	{
		return (id < rhs.id);
	}
	//============================================

	// declare a pure virtual function
	virtual ShapeType GetType() = 0;
};


/**
 * @brief      Rectangle object
 *
 * Definition of the struct for handling a rectangle object.
 */
class Rectangle : public Shape
{
public:
	Point2d pMin; ///< Point2d of min of rectangle
	Point2d pMax; ///< point of max of rectangle

	Rectangle() {};

	/**
	 * @brief      Ctor from a Rectangle pointer
	 *
	 * @param      ptrRec  The pointer record
	 */
	Rectangle(Rectangle* ptrRec)
	{
		Shape::id = ptrRec->id;
		pMin = ptrRec->pMin;
		pMax = ptrRec->pMax;
	}

	Rectangle& operator=(const Rectangle& rec)
	{
		Shape::operator=(rec);
		pMin = rec.pMin;
		pMax = rec.pMax;
  	return *this;
	}

	/**
	 * @brief      Gets the type of the shape object
	 *
	 * @return     The type.
	 */
	ShapeType GetType()
	{
		return Rec;
	}
};


/**
 * @brief      Circle object
 *
 * Definition of the struct for handling a circle object.
 */
class Circle : public Shape
{
public:
	Point2d center; ///< Point2d of center of the circle
	double radius; ///< radius of the circle

	// Default ctor
	Circle() : radius(0.0) {}

	/**
	 * @brief      Ctor from a circle pointer
	 *
	 * @param      ptrCirc  The pointer circ
	 */
	Circle(Circle* ptrCirc)
	{
		Shape::id = ptrCirc->id;
		center = ptrCirc->center;
		radius = ptrCirc->radius;
	}

	Circle& operator=(const Circle& circ)
	{
		Shape::operator=(circ);
		center = circ.center;
		radius = circ.radius;
  	return *this;
	}

	/**
	 * @brief      Gets the shape of the id
	 *
	 * @return     The type.
	 */
	ShapeType GetType()
	{
		return Circ;
	}
};

} // namespace efied2d
#endif //__SHAPE_H__
