#include "GEEntityRenderable.h"
#include "GEApp.h"
#include "GERenderer.h"
#include <iostream>

GEEntityRenderable::GEEntityRenderable() : GEEntity()
{
	color = glm::vec4(1, 1, 1, 1);

	GEApp::Renderer()->AddEntity(this);
		
}


GEEntityRenderable::~GEEntityRenderable()
{
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

