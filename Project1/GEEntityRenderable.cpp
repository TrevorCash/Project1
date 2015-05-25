#include "GEEntityRenderable.h"
#include "GEApp.h"
#include "GERenderer.h"
#include <iostream>

GEEntityRenderable::GEEntityRenderable(bool autoSubscribe) : GEEntity(autoSubscribe)
{
	classType = GECLASS_EntityRenderable;

	color = glm::vec4(1, 1, 1, 1);

	if (autoSubscribe)
	{
		SubscribeTo(GEApp::Renderer());
	}
}


GEEntityRenderable::~GEEntityRenderable()
{
	UnSubscribeFrom((GEBase*)GEApp::GameEngine()->GetRenderer());
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

