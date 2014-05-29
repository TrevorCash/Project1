#pragma once
#include "GEEntity.h"
class GEClient;
class GEEntityCamera :
	public GEEntity
{
public:
	GEEntityCamera();
	virtual ~GEEntityCamera();

	glm::vec3 vel;
	glm::vec3 acceleration;
	float yaw;
	float pitch;

	virtual void OnBaseTickUpdate(double deltaTime);

};

