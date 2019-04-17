#include "json_reader.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>      // std::ifstream
#include <string>
#include <iomanip>

using namespace efie2d;

/**
 * @brief      Check that all fields are set fot the JSON file
 *
 * @param[in]  json_efie2d object reference
 */
void check_json_efie2d(const nlohmann::json& json_efie2d,
					             const std::string& filename)
{
  // Start by checking the key (and eventually duplicate keys)
  auto it_geo = json_efie2d.find("geometry");
  if (it_geo == json_efie2d.end())
  {
    std::cout << "Cannot find \"geometry\" key in the JSON file: "<< filename << std::endl;
    exit(1);
  }
  auto it_solver = json_efie2d.find("solver");
  if (it_solver == json_efie2d.end())
  {
    std::cout << "Cannot find \"solver\" key in the JSON file: "<< filename << std::endl;
    exit(1);
  }
  auto it_material = json_efie2d.find("material");
  if (it_material == json_efie2d.end())
  {
    std::cout << "Cannot find \"material\" key in the JSON file: "<< filename << std::endl;
    exit(1);
  }
  auto it_excitation = json_efie2d.find("excitation");
  if (it_excitation == json_efie2d.end())
  {
    std::cout << "Cannot find \"excitation\" key in the JSON file: "<< filename << std::endl;
    exit(1);
  }
  // <todo> (attardo): This can be extended to check the fields as we expect!!!
}
//=========================================================================================


JsonReader::JsonReader(std::string& inputFilename_)
{
	has_been_read = false;
	inputFilename = inputFilename_;

	// Start creating the json file
  std::ifstream file;
  // Start reading the input file
  file.open(inputFilename.c_str());
  if (file.fail())
  {
   std::cout << "Could not open file: "<< inputFilename << std::endl;
   exit(1);
  }

  // create the JSON file
  file >> json_efie2d;
  check_json_efie2d(json_efie2d, inputFilename); //check json file

  // create all data from the json file
  ReadInput();
  has_been_read = true;
}
//============================================


void JsonReader::ReadInput()
{
	if (has_been_read) return;
	
	Circle aCirc;
	Rectangle aRec;
	Material aMat;

	size_t numObjs = 0;
  // Circle
  auto jsonGeo = json_efie2d.find("geometry");
  auto jsonCirc = jsonGeo->find("circle");
  if (jsonCirc != jsonGeo->end())
  {
	  auto circle = json_efie2d["geometry"]["circle"];
	  if (circle.is_array())
    {
       numObjs += circle.size();
      for (size_t i = 0; i <  circle.size(); ++i)
      {
        int id = circle[i]["id"];
        int id_mat = circle[i]["id_mat"];
        std::vector<double> tmp_vec = circle[i]["center"];
        aCirc.center.x = tmp_vec[0]; aCirc.center.y = tmp_vec[1];
        double radius = circle[i]["radius"];
        aCirc.radius = radius;
        aCirc.id = id;
        vCirc.push_back(aCirc);
        geo2Mat.insert(std::pair<int,int>(id, id_mat));
      }
    }
    else
    {
       numObjs ++;
      int id = circle["id"];
      int id_mat = circle["id_mat"];
      std::vector<double> tmp_vec = circle["center"];
      aCirc.center.x = tmp_vec[0]; aCirc.center.y = tmp_vec[1];
      double radius = circle["radius"];
      aCirc.radius = radius;
      aCirc.id = id;
      vCirc.push_back(aCirc);
      geo2Mat.insert(std::pair<int,int>(id, id_mat));
    }
  }

  // Rectangle
  auto jsonRec = jsonGeo->find("rectangle");
  if (jsonRec != jsonGeo->end())
  {
    auto rectangle = json_efie2d["geometry"]["rectangle"];
    if (rectangle.is_array())
    {
       numObjs += rectangle.size();
      for (size_t i = 0; i <  rectangle.size(); ++i)
      {
        int id = rectangle[i]["id"];
        int id_mat = rectangle[i]["id_mat"];
        std::vector<double> tmp_vec = rectangle[i]["pmin"];
        aRec.pMin.x = tmp_vec[0]; aRec.pMin.y = tmp_vec[1];
        std::vector<double> tmp_vec2 = rectangle[i]["pmax"];
        aRec.pMax.x = tmp_vec2[0]; aRec.pMax.y = tmp_vec2[1];
        aRec.id = id;
        vRec.push_back(aRec);
	      geo2Mat.insert(std::pair<int,int>(id, id_mat));
      }
    }
    else
    {
       numObjs ++;
      int id = rectangle["id"];
      int id_mat = rectangle["id_mat"];
      std::vector<double> tmp_vec = rectangle["pmin"];
      aRec.pMin.x = tmp_vec[0]; aRec.pMin.y = tmp_vec[1];
      std::vector<double> tmp_vec2 = rectangle["pmax"];
      aRec.pMax.x = tmp_vec2[0]; aRec.pMax.y = tmp_vec2[1];
      aRec.id = id;
      vRec.push_back(aRec);
	    geo2Mat.insert(std::pair<int,int>(id, id_mat));
    }
  }
  if ( numObjs==0)
  {
   std::cout << "Could not find any objects in the JSON file"<<std::endl;
   exit(1);
  }
  //============================================

  // Read frequency and material
  resolution = json_efie2d["solver"]["resolution"];
  int numFreq = 0;
  int idFreq;
  auto frequency = json_efie2d["solver"]["frequency"];
  if (frequency!=nullptr)
  {
    if (frequency.is_array())
    {
      std::cout << "EFIE2D supports only single frequency"<<std::endl;
   		exit(1);
    }
    else
    {
      numFreq ++;
      idFreq = frequency["id"];
      freq.SetFrequency(frequency["val"]);
    }
  }
  if (numFreq==0)
  {
    std::cout << "Could not find any frequency"<< std::endl;
    exit(1);
  }

	// Material
  auto material = json_efie2d["material"];
  size_t numMat = 0;
  if (material!=nullptr)
  {
    if (material.is_array())
    {
      numMat += material.size();
      for (size_t i = 0; i < material.size(); ++i)
      {
        int id = material[i]["id"];
        int id_freq = material[i]["id_freq"];
        if (id_freq != idFreq)
        {
        	std::cout << "Material only defined for a single frequency"<< std::endl;
    			exit(1);
        }
        aMat.SetId(id);
        double epsr = material[i]["epsr"];
        double sigma = material[i]["sigma"];
        aMat.SetEpsrc(epsr, sigma, freq.GetFrequency());
        vMat.push_back(aMat);
      }
    }
    else
    {
      numMat ++;
      int id = material["id"];
      int id_freq = material["id_freq"];
      if (id_freq != idFreq)
      {
      	std::cout << "Material only defined for a single frequency"<< std::endl;
  			exit(1);
      }
      aMat.SetId(id);
      double epsr = material["epsr"];
      double sigma = material["sigma"];
      aMat.SetEpsrc(epsr, sigma, freq.GetFrequency());
      vMat.push_back(aMat);
    }
  }
  if (numMat==0)
  {
    std::cout << "Could not find any material"<< std::endl;
    exit(1);
  }
  //============================================

   // Excitation
  auto planewave = json_efie2d["excitation"]["planewave"];
  if (planewave.is_array())
  {
    std::cout << "Only one planewave loop is supported"<< std::endl;
    exit(1);
  }
  startPhi = planewave["start_phi"];
  endPhi = planewave["end_phi"];
}
//============================================



