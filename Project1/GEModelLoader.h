#pragma once
#include "GEBase.h"
#include "GEModelData.h"


#include <iostream>

class GEModelLoader :
	public GEBase
{
public:
	GEModelLoader();
	~GEModelLoader();

	bool LoadIntoModel(GEModelData* mesh, std::string filename);


private:


};

