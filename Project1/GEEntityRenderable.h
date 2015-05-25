#pragma once
#include "GEEntity.h"
#include "LowLevelGraphics.h"

class GEModelData;
class GEEntityRenderable :
	public GEEntity
{
public:

	GEEntityRenderable(bool autoSubscribe = true);
	virtual ~GEEntityRenderable();



	virtual void OnRenderUpdate();
	virtual void OnBaseTickUpdate(double deltaTime);
	//virtual glm::mat4 GetInterpolatedTransform(const float interpolation, bool global);


	virtual void SetColor(glm::vec4 c);
	virtual glm::vec4 GetColor();

	GEModelData *modelData;
	glm::vec4 color;

	
};

