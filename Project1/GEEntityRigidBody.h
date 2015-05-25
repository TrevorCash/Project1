#ifndef GE_ENTITY_RIGID_BODY
#define GE_ENTITY_RIGID_BODY

#include "GEEntity.h"
#include "GEPhysicsHeaders.h"


class GEEntityRigidBody :
	public GEEntity
{
public:
	GEEntityRigidBody();
	virtual ~GEEntityRigidBody();

	virtual GECLASSTYPE ClassType();

	//delete extended
	virtual void Delete();

	//base tick extended
	virtual void OnBaseTickUpdate(double deltaTime);

	//parent child node relations.
	virtual void SetParent(GEEntity* p, bool maintainGlobalTrans = true);

	//translation
	virtual void SetPosition(glm::vec3 localPos);

	//scale
	virtual void SetScale(glm::vec3 sc);

	//rotation
	virtual void GEEntityRigidBody::SetRotation(float angle, glm::vec3 axis);

	virtual void SetMass(float mass);
	virtual float GetMass();

	//freezes the rigid body
	virtual void SetFrozen(bool freeze);

	
	//newton body
	NewtonBody* PhysBody;

	//newton compound collision
	NewtonCollision* PhysCol;

private:
	void RebuildBody();
	void AddCollisionToRoot();
	void RemoveCollisionFromRoot();

	float mass;
};

#endif