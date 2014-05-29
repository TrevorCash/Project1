#include <list>
#include <algorithm>
#include <iostream>

#include "GEApp.h"
#include "GEWorld.h"
#include "GEEntity.h"
#include "glm\gtc\matrix_transform.hpp"
#include "EasyInput.h"


GEEntity::GEEntity(void) : GEBase()
{

	pos = glm::vec3(0, 0, 0);
	lastPos = pos;

	orientation = glm::quat(1, 0, 0, 0);
	lastOrientation = orientation;

	
	scale = glm::vec3(1, 1, 1);
	lastScale = scale;

	parent = nullptr;

	AddToSimulation();
	AddToWorld();
}

GEEntity::~GEEntity(void)
{

}

GECLASSTYPE GEEntity::ClassType()
{
	return GECLASSTYPE::Entity;
}

//adds this entity to the world (scene graph)
void GEEntity::AddToWorld()
{
	GEApp::GameEngine()->World()->AddEntity(this);
}

//if we delete a top node - delete the children as well.
void GEEntity::Delete()
{
	for (children_it it = children.begin(); it != children.end(); ++it)
	{
		it->first->Delete();
	}
	
	GEBase::Delete();
}

//subscriptions extended to propigate down to children
void GEEntity::IncreaseSubscriptions()
{
	GEBase::IncreaseSubscriptions();
	for (children_it it = children.begin(); it != children.end(); ++it)
	{
		it->first->IncreaseSubscriptions();
	}
}
void GEEntity::DecreaseSubscriptions()
{
	GEBase::DecreaseSubscriptions();
	for (children_it it = children.begin(); it != children.end(); ++it)
	{
		it->first->DecreaseSubscriptions();
	}
}


void GEEntity::OnBaseTickUpdate(double deltaTime)
{
	GEBase::OnBaseTickUpdate(deltaTime);

	lastPos = pos;
	lastScale = scale;
	lastOrientation = orientation;//store old orientation for interpolation in render pipline.
}


void GEEntity::SetParent(GEEntity* p, bool maintainGlobalTrans)
{
	if (p == nullptr)
	{
		//we may be detaching.
		if (parent)
		{
			//remove child links on parent
			parent->children.erase(this);
			if (maintainGlobalTrans)
			{
				pos = GetPosition(true);
				scale = GetScale(true);
				orientation = GetRotationQuat(true);
			}
			parent = nullptr;
		}
		else
		{
			//do nothing.
		}
	}
	else//were parenting..
	{
		//make sure were unparented first...
		SetParent(nullptr);
		
		//maintain global transformation
		//this only works for uniform scaling...
		if (maintainGlobalTrans)
		{
			glm::mat4 localMat = glm::inverse(p->GetTransform(true)) * GetTransform(true);

			//extract position
			pos = glm::vec3(localMat[3][0], localMat[3][1], localMat[3][2]);

			//extract scale
			double scaleX = glm::length(glm::vec3(localMat[0][0], localMat[0][1], localMat[0][2]));
			double scaleY = glm::length(glm::vec3(localMat[1][0], localMat[1][1], localMat[1][2]));
			double scaleZ = glm::length(glm::vec3(localMat[2][0], localMat[2][1], localMat[2][2]));
			scale = glm::vec3(scaleX, scaleY, scaleZ);

			//orientation is just undoing parent global rotation.
			orientation =  glm::normalize(glm::inverse(p->GetRotationQuat(true)) * orientation);
		}

		
		parent = p;
		parent->children.insert(std::pair<GEEntity*, GEEntity*>(this, this));
	}
}

GEEntity* GEEntity::GetParent()
{
	return parent;
}

//returns the highest ancestor in the parent-child tree.
//Note: is there is no parent's at all it will return this.
GEEntity* GEEntity::GetRoot()
{
	if (GetParent() == nullptr) 
		return this;

	return GetParent()->GetRoot();
}

//core movement method to all entities, any function
//that moves an entity in any way should use this as its core
//to allow for graph updates.
void GEEntity::SetPosition(glm::vec3 localPos)
{
	pos = localPos;
}

glm::vec3 GEEntity::GetPosition(bool asGlobal)
{
	if (asGlobal == false || !parent)
		return pos;
	else
	{
		//global
		glm::vec4 point(pos, 1.0f);
		glm::vec4 globPoint =  parent->GetTransform(true) * point;
		return glm::vec3(globPoint);
	}

}
void GEEntity::MoveBy(glm::vec3 deltaPos)
{
	SetPosition(GetPosition() + deltaPos);
}




void GEEntity::SetScale(glm::vec3 sc)
{
	scale = sc;
}
glm::vec3 GEEntity::GetScale(bool asGlobal)
{
	if (asGlobal == false || !parent)
		return scale;
	else
	{
		return parent->GetScale(asGlobal) * scale;
	}
}


void GEEntity::SetRotation(float angle, glm::vec3 axis)
{
	orientation = glm::rotate(glm::quat(1, 0, 0, 0), angle, axis);
	orientation = glm::normalize(orientation);
}

void GEEntity::SetOrientation(glm::quat orient)
{
	orientation = glm::normalize(orient);

}
void GEEntity::RotateBy(float angle, glm::vec3 axis)
{
	orientation = glm::rotate(orientation, angle, axis);
	orientation = glm::normalize(orientation);
}

glm::quat GEEntity::GetRotationQuat(bool asGlobal)
{
	if (asGlobal == false || !parent)
		return orientation;
	else
	{
		return glm::normalize(parent->GetRotationQuat(asGlobal) * orientation);
	}
}
glm::mat4 GEEntity::GetRotationMat()
{
	return glm::mat4_cast(orientation);
}

glm::vec3 GEEntity::GetForward()
{
	const float& x = orientation.x;
	const float& y = orientation.y;
	const float& z = orientation.z;
	const float& w = orientation.w;

	return glm::normalize(glm::vec3(-2 * (x * z + w * y),
		-2 * (y * z - w * x),
		-1 + 2 * (x * x + y * y)));

}
glm::vec3 GEEntity::GetUp()
{
	const float& x = orientation.x;
	const float& y = orientation.y;
	const float& z = orientation.z;
	const float& w = orientation.w;

	return glm::normalize(glm::vec3(2.0f * (x * y - w * z),
		1 - 2.0f * (x * x + z * z),
		2.0f * (y * z + w * x)));
}
glm::vec3 GEEntity::GetRight()
{
	const float& x = orientation.x;
	const float& y = orientation.y;
	const float& z = orientation.z;
	const float& w = orientation.w;

	return glm::normalize(glm::vec3(1 - 2.0f * (y * y + z * z),
		2.0f * (x * y + w * z),
		2.0f * (x * z - w * y)));
}


glm::mat4 GEEntity::GetTransform(bool global)
{
	
	glm::mat4 localMat;
	localMat = glm::mat4(1.0f);
	localMat = glm::translate(localMat, pos);
	localMat *= glm::mat4_cast(orientation);
	localMat = glm::scale(localMat, scale);

	if (global == false)
		return localMat;//return local transform by default.
	else
	{
		//return global transform
		if (parent != nullptr)
		{
			return parent->GetTransform(true) * localMat;	
		}
		else
			return localMat;
	}
}

//returns the transform in the reference Entity's space...
glm::mat4 GEEntity::GetTransform(GEEntity* referenceEntity)
{
	return glm::inverse(referenceEntity->GetTransform(true)) * GetTransform(true);
}

////to be used by renderer only - returns an interpolated transform...
glm::mat4 GEEntity::GetInterpolatedTransform(const float interpolation, bool global)
{
	glm::quat slerpedOrientation = glm::slerp(lastOrientation, orientation, interpolation);
	glm::vec3 interpolatedPos = lastPos + (pos - lastPos)*interpolation;
	glm::vec3 interpolatedScale = lastScale + (scale - lastScale)*interpolation;

	glm::mat4 interpolatedTransform(1.0f);

	interpolatedTransform = glm::translate(interpolatedTransform, interpolatedPos);
	interpolatedTransform = interpolatedTransform  * glm::mat4_cast(slerpedOrientation);
	interpolatedTransform = glm::scale(interpolatedTransform, interpolatedScale);

	if (global == false)
		return interpolatedTransform;
	else
	{
		if (parent != nullptr)
		{
			return  parent->GetInterpolatedTransform(interpolation, true) * interpolatedTransform;
		}
		else
			return interpolatedTransform;
	}
}
