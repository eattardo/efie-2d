#ifndef __MODEL_H__
#define __MODEL_H__

#include <string>
#include "../geometry/geometry.h"
#include "../mesh/mesh.h"
#include "../excitation/excitation.h"
#include "../material/dielectric_parameters.h"
#include "../src/json_reader/json_reader.h"

namespace efie2d
{
	class Model
	{
	private:
		Geometry* ptrGeo; ///< ptr to the Geometry
		DielectricParameters* ptrDielParams; ///< pointer to the Dielectric parameters
		Excitation* ptrEinc; ///< ptr to the electric incident field
	public:

		/**
		 * @brief      Constructs the object.
		 */
		Model();


		/**
		 * @brief      Constructs the object from the jsonObj
		 *
		 * @param      jsonObj  The json object
		 */
		Model(JsonReader& jsonObj);

		~Model() = default;

		/**
		 * @brief      Gets the pointer geometry.
		 *
		 * @return     The pointer geometry.
		 */
		Geometry* GetPtrGeometry() noexcept;

		/**
		 * @brief      Gets the pointer excitation.
		 *
		 * @return     The pointer excitation.
		 */
		Excitation* GetPtrExcitation() noexcept;

		/**
		 * @brief      Gets the pointer dielectric parameters.
		 *
		 * @return     The pointer dielectric parameters.
		 */
		DielectricParameters* GetPtrDielectricParams() noexcept;

		/**
		 * @brief      Gets the pointer mesh.
		 *
		 * @return     The pointer mesh.
		 */
		Mesh* GetPtrMesh() noexcept;
	};
} // namespace efie2d


#endif /* #ifndef __MODEL_H__ */