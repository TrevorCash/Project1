#include "EasyInput.h"

bool KeyDown(int keycode)
{
	return GEApp::globalGameEngineInstance->Context()->KeyDown(keycode);
}

bool KeyHit(int keycode)
{
	return GEApp::globalGameEngineInstance->Context()->KeyHit(keycode);
}
glm::dvec2 MouseVel()
{
	return GEApp::globalGameEngineInstance->Context()->GetMouseVel();
}