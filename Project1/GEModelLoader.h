#pragma once
#include "GEBase.h"
#include "GEModelData.h"


#include <iostream>

class GEModelLoader
{
public:
	GEModelLoader();
	~GEModelLoader();

	bool LoadIntoModel(GEModelData* mesh, std::string filename);


private:


};

