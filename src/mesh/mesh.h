/* Definition class mesh for the EFIE 2D
   Mesh is assumed always quadrilateral.
 */
#ifndef __MESH_H__
#define __MESH_H__

#include <map>
#include <vector>

#include "point2d.h"
#include "../object/primitive_object.h"
#include "../object/shape.h"

// Start namespace efie2d
namespace efie2d
{
	class Mesh
	{
	private:
		int backgroundId; ///< background id
		size_t numOfCells; ///< number of cells of the mesh
    double an;    ///< radius of the circle that envelops the cell
                  ///< equal for all cells (set as resolution/2)
	public:
		std::map<int,Point2d> cells; ///< cells of the mesh (an id is associated)

  /**
  * @brief      Constructs the Mesh class.
  */
	Mesh();
	//============================================


	/**
   * @brief      Destroys the Mesh class (empty).
   */
  ~Mesh() = default;
  //============================================

  /**
 * @brief      Sets the background id.
 *
 * @param[in]  backgroundId_  The background id
 */
  void SetBackgroundId(const int backgroundID) noexcept;
  //============================================

  /**
 * @brief      Sets the number cells.
 *
 * @param[in]  numOfCells_  The number of cells
 */
  void SetNumCells(const size_t numOfCells) noexcept;
  //============================================


  /**
   * @brief      Sets radius of the cell
   */
  void SetAn(const double resolution) noexcept;
  //============================================


  /**
 * @brief      Gets the background id.
 *
 * @return     The background id.
 */
  int GetBackgroundId() const noexcept;
  //============================================

  /**
 * @brief      Gets the number cells.
 *
 * @return     The number cells.
 */
  size_t GetNumCells() const noexcept;
  //============================================


  /**
   * @brief      Gets the coordinate cell at cell with id equal to i.
   *
   * @param[in]  i       cell i
   * @param[in,out]      center  The center
   */
  Point2d GetCoordCellAt(const int i);
  //============================================


  /**
   * @brief      Gets the radius of the circle
   *             that envelops the cell.
   * @return     an
   */
  double GetAn() const noexcept;


  /**
   * @brief      Generate the mesh
   *
   * @param[in]  resolution  The resolution of the mesh
   * @param      vPrObj      The primitive objects vector
   *
   * @return     error
   */
  int GenerateMesh(const double resolution, std::vector<PrimitiveObj>& vPrObj);


  /**
   * @brief      Creates a mesh from background circle.
   *
   * @param      ptrCirc     The pointer to the circle object
   * @param[in]  resolution  The resolution of the mesh
   *
   * @return     error
   */
  int CreateMeshFromBackgroundCircle(Circle* ptrCirc, const double resolution);


  /**
   * @brief      Creates a mesh from background rectangle.
   *
   * @param      ptrRec      The pointer to the rectangle object
   * @param[in]  resolution  The resolution of the mesh
   *
   * @return     The resolution of the mesh
   */
  int CreateMeshFromBackgroundRectangle(Rectangle* ptrRec, const double resolution);


  // Overload of the ostream for printing the mesh cells
  //
  // @param[in]           std::ostream
  // @param[in]           Mesh reference
  //
  // @return              std::ostream
  //
  friend std::ostream& operator<<(std::ostream&, const Mesh&);

  // Not used functions
  Mesh& operator=(const Mesh&) = delete;
}; // end class mesh

} // namespace efie2d

#endif //__MESH_H__
