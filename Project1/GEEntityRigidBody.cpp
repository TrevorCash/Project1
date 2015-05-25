#include "GEEntityRigidBody.h"
#include "GEApp.h"
#include "GEWorld.h"
#include "GEMathHelpers.h"



GEEntityRigidBody::GEEntityRigidBody() : GEEntity()
{
	//when we create a GEEntityRigidBody we create an associated newtonBody.

	//default mass
	mass = 100.0;

	NewtonWorld* world = GEApp::World()->newtonWorld;

	PhysCol = NewtonCreateCompoundCollision(world, 0);
	
	dMatrix mat = GlmToNewt(GetTransform());
	
	NewtonCollision* defaultBoxCol = NewtonCreateBox(world, 1.0f, 1.0f, 1.0f, 0, &mat[0][0]);
	NewtonCollisionSetUserData(defaultBoxCol, (void*)this);

	NewtonCompoundCollisionBeginAddRemove(PhysCol);
	
		NewtonCompoundCollisionAddSubCollision(PhysCol, defaultBoxCol);
		NewtonDestroyCollision(defaultBoxCol);
	
	NewtonCompoundCollisionEndAddRemove(PhysCol);
	
	PhysBody = nullptr;
	RebuildBody();
}


GEEntityRigidBody::~GEEntityRigidBody()
{
	if (PhysBody)
	{
		NewtonBodySetUserData(PhysBody, nullptr);
		NewtonDestroyBody(PhysBody);
		PhysBody = nullptr;
	}
	if (PhysCol)
	{
		NewtonDestroyCollision(PhysCol);
		PhysCol = nullptr;
	}
}


GECLASSTYPE GEEntityRigidBody::ClassType()
{
	return GECLASSTYPE::EntityRigidBody;
}

void GEEntityRigidBody::Delete()
{
	GEEntity::Delete();
	
	if (PhysBody)
	{
		NewtonBodySetUserData(PhysBody, nullptr);
		NewtonDestroyBody(PhysBody);
		PhysBody = nullptr;
	}
	if (PhysCol)
	{
		NewtonDestroyCollision(PhysCol);
		PhysCol = nullptr;
	}
}

//base tick extended
void GEEntityRigidBody::OnBaseTickUpdate(double deltaTime)
{
	GEEntity::OnBaseTickUpdate(deltaTime);
}


//parenting extended
void GEEntityRigidBody::SetParent(GEEntity* p, bool maintainGlobalTrans)
{
	if (p != nullptr  && p->ClassType() != GECLASSTYPE::EntityRigidBody)
	{
		std::cout << "Cant Parent Rigid Body To Non Rigid Body!" << std::endl;
		return;
	}


	//were detaching from parent..
	if (p == nullptr && GetParent())
	{
		//restoration..
		RemoveCollisionFromRoot();
		RebuildBody();
	}

	//call entity parent ruetines.
	GEEntity::SetParent(p, maintainGlobalTrans);

	if (p == nullptr)
	{
	
	}
	else//were attaching to parent.. so we need to setup compound collision
	{
		AddCollisionToRoot();

		//now the root is taking over as body - so delete our's
		//we can recreate it later...
		NewtonDestroyBody(PhysBody);
		PhysBody = nullptr;
	}
}


//translation
void GEEntityRigidBody::SetPosition(glm::vec3 localPos)
{
	//update as before.
	GEEntity::SetPosition(localPos);
	
	//we need to update physics simulation as well.
	if (parent == nullptr)
	{
		dMatrix mat;
		NewtonBodyGetMatrix(PhysBody,&mat[0][0]);
		
		glm::mat4 localMat = NewtToGlm(mat);
		localMat[3][0] = localPos.x;
		localMat[3][1] = localPos.y;
		localMat[3][2] = localPos.z;

		NewtonBodySetMatrix(PhysBody, (float*)&GlmToNewt(localMat)[0]);
	}
	else
	{
		std::cout << "Not Supported Yet!";
	}
}

//scale
void GEEntityRigidBody::SetScale(glm::vec3 sc)
{
	GEEntity::SetScale(sc);
	if (parent == nullptr)
	{
		NewtonCollision* col = NewtonBodyGetCollision(PhysBody);
		NewtonCollisionSetScale(col, sc.x, sc.y, sc.z);
		
	}
	else
	{
		std::cout << "not supported yet!";
	}
}

//rotation
void GEEntityRigidBody::SetRotation(float angle, glm::vec3 axis)
{
	GEEntity::SetRotation(angle, axis);
	//std::cout << "Not Yet Supported" << std::endl;
	//if (!GetParent())
	//	NewtonBodySetMatrix(PhysBody, &GlmToNewt(GetTransform())[0][0]);
	//else
	//	std::cout << "Cant Rotate Rigid Body While It's Parented" << std::endl;
}

void GEEntityRigidBody::SetMass(float mass)
{
	this->mass = mass;
	//dNewtonCollision* col = PhysBody->GetCollision();
	//PhysBody->SetMassAndInertia(mass, col);
	NewtonBodySetMassProperties(PhysBody, mass, PhysCol);
}

float GEEntityRigidBody::GetMass()
{
	return mass;
}

void GEEntityRigidBody::SetFrozen(bool freeze)
{
	if (freeze)
		NewtonBodySetMassProperties(PhysBody, 0.0f, PhysCol);
	else
		NewtonBodySetMassProperties(PhysBody, mass, PhysCol);
}


//private:
void GEEntityRigidBody::RebuildBody()
{
	if (PhysBody != nullptr)
		NewtonDestroyBody(PhysBody);

	NewtonWorld* world = GEApp::World()->newtonWorld;
	
	
	dMatrix mat = GlmToNewt(GetTransform(true));
	
	//now create the rigid body.
	PhysBody = NewtonCreateDynamicBody(world, PhysCol, &mat[0][0]);
	NewtonBodySetUserData(PhysBody, (void*)this);

	NewtonBodySetMassProperties(PhysBody, mass, PhysCol);

	//assign callbacks
	NewtonBodySetForceAndTorqueCallback(PhysBody, GENewton_ApplyForceAndTorqueCallback);
	NewtonBodySetTransformCallback(PhysBody, GENewton_SetTransformCallback);
	NewtonBodySetDestructorCallback(PhysBody, GENewton_DestroyBodyCallback);

	//drag
	NewtonBodySetLinearDamping(PhysBody, 0.05f);
}


//adds this entity's collision to the root's compound.
void GEEntityRigidBody::AddCollisionToRoot()
{
	GEEntityRigidBody* rootEnt = (GEEntityRigidBody*)GetRoot();

	NewtonCompoundCollisionBeginAddRemove(rootEnt->PhysCol);

	//loop through all elementary collisions in this coumpound and add it to the root.
	void* currNode = NewtonCompoundCollisionGetFirstNode(PhysCol);
	while (currNode != nullptr)
	{
		NewtonCollision* ThisElement = NewtonCompoundCollisionGetCollisionFromNode(PhysCol, currNode);
		
		NewtonCollision* CpyOfThisElement = NewtonCollisionCreateInstance(ThisElement);
			
		NewtonCollisionSetMatrix(CpyOfThisElement, (float*)&GlmToNewt(GetTransform(rootEnt))[0][0]);
			
		NewtonCompoundCollisionAddSubCollision(rootEnt->PhysCol, CpyOfThisElement);

		NewtonDestroyCollision(CpyOfThisElement);

		currNode = NewtonCompoundCollisionGetNextNode(PhysCol, currNode);
	}

	NewtonCompoundCollisionEndAddRemove(rootEnt->PhysCol);

	rootEnt->RebuildBody();
}

//remove the collisions in root that were from this body..
void GEEntityRigidBody::RemoveCollisionFromRoot()
{
	////locate the top of the tree...
	GEEntityRigidBody* rootEnt = (GEEntityRigidBody*)GetRoot();

	NewtonCompoundCollisionBeginAddRemove(rootEnt->PhysCol);

	void* currNode = NewtonCompoundCollisionGetFirstNode(rootEnt->PhysCol);
	while (currNode != nullptr)
	{
		NewtonCollision* curSubCol = NewtonCompoundCollisionGetCollisionFromNode(rootEnt->PhysCol, currNode);
		
		if ((GEEntityRigidBody*)NewtonCollisionGetUserData(curSubCol) == this)
		{
			NewtonCompoundCollisionRemoveSubCollision(rootEnt->PhysCol, currNode);
		}
		std::cout << curSubCol << std::endl;
		currNode = NewtonCompoundCollisionGetNextNode(rootEnt->PhysCol, currNode);
	}
	
	NewtonCompoundCollisionEndAddRemove(rootEnt->PhysCol);

	rootEnt->RebuildBody();
}