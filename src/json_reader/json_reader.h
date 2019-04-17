#ifndef __JSON_READER_H__
#define __JSON_READER_H__

#include <map>
#include <vector>
#include <string>
#include "../object/shape.h"
#include "../material/material.h"
#include "../model/frequency.h"
#include "../../../json-develop/single_include/nlohmann/json.hpp"

namespace efie2d
{

class JsonReader
{
public:
	bool has_been_read; ///< flag that indicates that the json fiel hase been read
	std::string inputFilename; ///< string with the filename
	nlohmann::json json_efie2d; ///< json c++ object
	std::vector<Rectangle> vRec; ///< vec of rectanlges
	std::vector<Circle> vCirc; ///< vec of circles
	std::vector<Material> vMat; ///< vec for storing materials
	std::map<int,int> geo2Mat; ///< map that indicates for the i-th object which j-th material is associated
	double resolution; ///< resolution in m
	Frequency freq; ///< vec of frequency
	// Excitation
	double startPhi; ///< start phi angle
	double endPhi; ///< end phi angle

	/**
	 * @brief      Constructs the object.
	 */
	JsonReader() { has_been_read = false; };

	/**
	 * @brief      Constructs with the inputFilename
	 *
	 * @param      inputFilename_  The input filename
	 */
	JsonReader(std::string& inputFilename_);

	~JsonReader() = default;

	/**
	 * @brief      Reads the JSON file
	 */
	void ReadInput();


};

} // namespace efied2d

#endif /* #ifndef __JSON_READER_H__ */
