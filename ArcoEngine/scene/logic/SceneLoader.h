#pragma once
#include <vector>
#include <string>

class CSceneLoader
{
public:
	CSceneLoader(void);
	~CSceneLoader(void)		{ }

	void LoadXML(std::string filename);

};
