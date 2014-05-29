#pragma once
#include "GEBase.h"
class GEEntityCamera;
class GEClient :
	public GEBase
{
public:
	GEClient();
	~GEClient();

	void SetCamera(GEEntityCamera* cam);
	GEEntityCamera* GetCamera();


private:
	GEEntityCamera *activeCamera;
};

