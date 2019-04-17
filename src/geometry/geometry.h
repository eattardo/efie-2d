#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <vector>
#include "../object/shape.h"
#include "../object/primitive_object.h"
#include "../material/material.h"
#include "../mesh/mesh.h"

namespace efie2d
{


	class Geometry
	{
	private:
		Mesh mesh2d; ///< mehs obj
		std::vector<PrimitiveObj> vObj; ///< primitive obj vector
	public:

		/**
     * @brief    Empty ctor.
     */
    Geometry() {};

		/**
     * @brief    Ctor.
     *
     * @param[in]  resolution  The resolution of the mesh
     * @param      vRec        vector of rectangles
     * @param      vCirc       vector of circles
     * @param      vMat        vector of materials
     * @param      geo2Mat     map of (obj->mat)
     */
    Geometry(const double resolution, std::vector<Rectangle>& vRec, std::vector<Circle>& vCirc,
      std::vector<Material>& vMat, std::map<int, int>& geo2Mat);

		~Geometry() = default;

		/**
     * @brief      Adds primitive objects.
     *
     * @param      vRec        vector of rectangles
     * @param      vCirc       vector of circles
     * @param      vMat        vector of materials
     * @param      geo2Mat     map of (obj->mat)
     */
    void AddPrimitiveObjects(std::vector<Rectangle>& vRec, std::vector<Circle>& vCirc,
			std::vector<Material>& vMat, std::map<int, int>& geo2Mat);

		/**
     * @brief      Gets the mesh.
     *
     * @return     The mesh.
     */
    Mesh& GetMesh() noexcept;

		/**
     * @brief      Gets the primitive object vector.
     *
     * @return     The primitive object vector.
     */
    std::vector<PrimitiveObj>& GetPrimitiveObjVec();
	};

} // namespace efie2d


#endif /* #ifndef __GEOMETRY_H__ */