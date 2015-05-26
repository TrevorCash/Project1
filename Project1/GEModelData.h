#pragma once
#include "gebase.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "LowLevelGraphics.h"
#include "GETriangle.h"
#include "GEMeshData.h"

#include <assimp\scene.h>
#include <vector>
#include <unordered_set>

class GEModelData : public GEBase
{
public:
	GEModelData(void);
	virtual ~GEModelData(void);
	
	void BindGraphics();//generates graphics buffers for use in rendering.
	void UnBindGraphics();//releases associated bound graphcis buffers.

	bool graphicsBound;
	std::vector<GEMeshData*> meshDataList;
	
};

