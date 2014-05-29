#include "GEClient.h"
#include "GEEntityCamera.h"


GEClient::GEClient() : GEBase(),
	activeCamera(nullptr)
{
}
GEClient::~GEClient()
{
}



void GEClient::SetCamera(GEEntityCamera* cam)
{
	activeCamera = cam;
}
GEEntityCamera* GEClient::GetCamera()
{
	return activeCamera;
}


