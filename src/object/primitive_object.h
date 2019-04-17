#ifndef __PRIMITIVE_OBJECT_H__
#define __PRIMITIVE_OBJECT_H__

#include <string>

#include "shape.h"
#include "../material/material.h"

namespace efie2d
{

class PrimitiveObj
{
private:
	ShapeType typeObj; ///< enum type shape
	Shape* ptrShape; ///< ptr to shape
	Material ptrMaterial; ///< ptr to material
public:
	PrimitiveObj();

	/**
	 * @brief      Ctor
	 *
	 * @param[in]  typeObj_      shape type
	 * @param      ptrShape_     ptr to generic shape
	 * @param      ptrMaterial_  ptr to material
	 */
	PrimitiveObj(ShapeType typeObj_, Shape* ptrShape_, Material* ptrMaterial_);

	~PrimitiveObj() = default;

	/**
	 * @brief      Gets the shape identifier.
	 *
	 * @return     The shape identifier.
	 */
	int GetShapeId() noexcept;

	/**
	 * @brief      Gets the material identifier.
	 *
	 * @return     The material identifier.
	 */
	int GetMaterialId() const noexcept;

	/**
	 * @brief      Gets the shape type.
	 *
	 * @return     The shape type.
	 */
	ShapeType GetShapeType() const noexcept;

	/**
	 * @brief      Gets the material.
	 *
	 * @return     The material.
	 */
	Material& GetMaterial() noexcept;

	/**
	 * @brief      Gets the shape ptr.
	 *
	 * @return     The shape.
	 */
	Shape* GetShape() noexcept;

    bool operator<(const PrimitiveObj& rhs) const;
};

} // namespace efie2d

#endif /* #ifndef __PRIMITIVE_OBJECT_H__ */