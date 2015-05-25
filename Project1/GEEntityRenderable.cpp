#include "GEEntityRenderable.h"
#include "GEApp.h"
#include "GERenderer.h"
#include <iostream>

GEEntityRenderable::GEEntityRenderable() : GEEntity()
{
	color = glm::vec4(1, 1, 1, 1);

	SubscribeTo((GEBase*)GEApp::GameEngine()->GetRenderer());
}


GEEntityRenderable::~GEEntityRenderable()
{
	UnSubscribeFrom((GEBase*)GEApp::GameEngine()->GetRenderer());
}




GECLASSTYPE GEEntityRenderable::ClassType()
{
	return GECLASSTYPE::EntityRenderable;
}

void GEEntityRenderable::OnRenderUpdate()
{

}

void GEEntityRenderable::OnBaseTickUpdate(double deltaTime)
{
	GEEntity::OnBaseTickUpdate(deltaTime);

}

void GEEntityRenderable::SetColor(glm::vec4 c)
{
	color = c;
}
glm::vec4 GEEntityRenderable::GetColor()
{
	return color;
}

