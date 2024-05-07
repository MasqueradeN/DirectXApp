#include <d3d11.h>
#include <cmath>
//#include "../Constants.h"
#include "SceneLoader.h"
#include "../../tools/pugixml.hpp"

CSceneLoader::CSceneLoader()
{

}

void CSceneLoader::LoadXML(std::string filename)
{
	pugi::xml_document doc;
	std::string pathname("data/");
	pathname += filename;
	pugi::xml_parse_result result = doc.load_file(pathname.c_str());
	pugi::xml_node primer = doc.first_child();
}

