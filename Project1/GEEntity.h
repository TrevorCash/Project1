#pragma once
#include <list>
#include <map>

#include "gebase.h"
#include "glm\glm.hpp"
#include "glm\gtc\quaternion.hpp"



class GEEntity :
	public GEBase
{
public:
	GEEntity(void);
	virtual ~GEEntity(void);


	virtual GECLASSTYPE ClassType();

	virtual void AddToWorld();

	//delete extended
	virtual void Delete();

	//subscriptions extended
	void IncreaseSubscriptions();
	void DecreaseSubscriptions();

	//base tick extended
	virtual void OnBaseTickUpdate(double deltaTime);

	//parent child node relations.
	virtual void SetParent(GEEntity* p, bool maintainGlobalTrans = true);
	virtual GEEntity* GetParent();
	virtual GEEntity* GetRoot();

	//translation
	virtual void SetPosition(glm::vec3 localPos);
	virtual glm::vec3 GetPosition(bool asGlobal = false);
	virtual void MoveBy(glm::vec3 deltaPos);
	
	//scale
	virtual void SetScale(glm::vec3 sc);
	virtual glm::vec3 GetScale(bool asGlobal = false);
	
	//orientation.
	virtual void SetRotation(float angle, glm::vec3 axis);
	virtual void SetOrientation(glm::quat orientation);
	virtual void RotateBy(float angle, glm::vec3 axis);
	virtual glm::quat GetRotationQuat(bool asGlobal = false);
	virtual glm::mat4 GetRotationMat();
	virtual glm::vec3 GetForward();
	virtual glm::vec3 GetUp();
	virtual glm::vec3 GetRight();

	//transformations
	virtual glm::mat4 GetTransform(bool global = false);
	virtual glm::mat4 GetTransform(GEEntity* referenceEntity);
	virtual glm::mat4 GetInterpolatedTransform(const float interpolation, bool global);

protected:

	glm::vec3 pos;
	glm::quat orientation;
	glm::vec3 scale;
	glm::vec3 lastPos;
	glm::vec3 lastScale;
	glm::quat lastOrientation;

	GEEntity* parent;//physical parent
	//std::list<GEEntity*> children;//physical children.
	
	typedef std::map<GEEntity*, GEEntity*> children_map;
	typedef children_map::iterator children_it;
	children_map children;
};

