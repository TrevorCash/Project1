
#include "GENetworkManager.h"
#include "GEApp.h"
#include "GEConsole.h"
#include "GEWorld.h"
#include "GERenderer.h"
#include "GEClient.h"
#include "GEEntityRenderable.h"
#include "GEEntityCamera.h"
#include "GEModelData.h"
#include "EasyInput.h"
#include "GEPhysicsHeaders.h"
#include "glm\gtc\type_ptr.hpp"
#include "GEMathHelpers.h"


#include <iostream>
#include <vector>

GEWorld::GEWorld(void) : gravity(-9.81)
{
	InitializeNewton();
}


GEWorld::~GEWorld(void)
{
	RemoveAllEntities();
}

void GEWorld::Initialize()
{
	////make the scene.

	//make cordinate legend at origin
	GEEntityRenderable* legend = new GEEntityRenderable();
	legend->modelData = GEApp::globalGameEngineInstance->Renderer()->ModelData()[2];
	legend->SetColor(glm::linearRand(glm::vec4(0.0f), glm::vec4(1.0f)));

	//make camera
	GEEntityCamera* camera = new GEEntityCamera();
	GEApp::Client()->SetCamera(camera);
	camera->SetPosition(glm::vec3(0, 10, 30));
	camera->SetNickName("cam");

	//make a floor
	GEEntityRigidBody* floor = new GEEntityRigidBody();
	GEEntityRenderable* floorVis = new GEEntityRenderable();
	floorVis->modelData = GEApp::globalGameEngineInstance->Renderer()->ModelData()[1];
	floorVis->SetParent(floor);
	floor->SetPosition(glm::vec3(0, -101.0, 0));
	floor->SetScale(glm::vec3(200, 200, 200));
	floor->SetFrozen(true);
	floor->SetNickName("mainfloor");

	//make a wall
	GEEntityRigidBody* floor2 = new GEEntityRigidBody();
	GEEntityRenderable* floor2Vis = new GEEntityRenderable();
	floor2Vis->modelData = GEApp::globalGameEngineInstance->Renderer()->ModelData()[1];
	floor2Vis->SetParent(floor2);
	floor2->SetPosition(glm::vec3(120, 0, 0));
	floor2->SetScale(glm::vec3(200, 400, 200));
	floor2->SetFrozen(true);
	
	//make a wall
	GEEntityRigidBody* floor3 = new GEEntityRigidBody();
	GEEntityRenderable* floor3Vis = new GEEntityRenderable();
	floor3Vis->modelData = GEApp::globalGameEngineInstance->Renderer()->ModelData()[1];
	floor3Vis->SetParent(floor3);
	floor3->SetPosition(glm::vec3(-120, 0, 0));
	floor3->SetScale(glm::vec3(200, 400, 200));
	floor3->SetFrozen(true);

	//make a wall
	GEEntityRigidBody* floor4 = new GEEntityRigidBody();
	GEEntityRenderable* floor4Vis = new GEEntityRenderable();
	floor4Vis->modelData = GEApp::globalGameEngineInstance->Renderer()->ModelData()[1];
	floor4Vis->SetParent(floor4);
	floor4->SetPosition(glm::vec3(0, 0, 120));
	floor4->SetScale(glm::vec3(200, 400, 200));
	floor4->SetFrozen(true);

	//make a wall
	GEEntityRigidBody* floor5 = new GEEntityRigidBody();
	GEEntityRenderable* floor5Vis = new GEEntityRenderable();
	floor5Vis->modelData = GEApp::globalGameEngineInstance->Renderer()->ModelData()[1];
	floor5Vis->SetParent(floor5);
	floor5->SetPosition(glm::vec3(0, 0, -120));
	floor5->SetScale(glm::vec3(200, 400, 200));
	floor5->SetFrozen(true);

	
	GEEntityRigidBody* prevBody = nullptr;
	for (int j = 0; j < 1500; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			////do some testing with physics parenting!
			GEEntityRigidBody* BodyA = new GEEntityRigidBody();
			BodyA->SetPosition(glm::ballRand(2.2f) + glm::vec3(0, 5*j, 0));
			BodyA->SetRotation(45, glm::vec3(1, 0, 0));

			GEEntityRenderable* VisBodyA = new GEEntityRenderable();
			VisBodyA->modelData = GEApp::GameEngine()->Renderer()->ModelData()[1];
			VisBodyA->SetParent(BodyA, false);
			VisBodyA->SetColor(glm::linearRand(glm::vec4(1), glm::vec4(0)));
			if (prevBody)
				BodyA->SetParent(prevBody);
			prevBody = BodyA;
		}

		prevBody = nullptr;
	}
}

void GEWorld::InitializeNewton()
{
	newtonWorld = NewtonCreate();

	NewtonSetThreadsCount(newtonWorld, 4);


}


//Updates the Logic In the world
void GEWorld::BaseTickUpdate(double deltaTime)
{
	NewtonUpdateAsync(newtonWorld, deltaTime);
	NewtonWaitForUpdateToFinish(newtonWorld);
	if (KeyHit(GLFW_KEY_DELETE))
	{
		GEApp::GameEngine()->Console()->FindObjectByNickName("mainfloor")->Delete();
	}
	if (KeyHit(GLFW_KEY_P))
	{
		
	}
}

void GEWorld::AddEntity(GEEntity* entity)
{
	entityList.push_back(entity);
	entity->IncreaseSubscriptions();
}

//marks all objects to be deleted and removed objects references from the worlds list.
void GEWorld::RemoveAllEntities()
{
	for (std::list<GEEntity*>::iterator it = entityList.begin(); it != entityList.end(); it++)
	{
		GEEntity* ent = *it;
		ent->Delete();
		ent->DecreaseSubscriptions();
	}
	entityList.clear();
}


//Newton Dynamics Callbacks
void GENewton_ApplyForceAndTorqueCallback(const NewtonBody* body, dFloat timestep, int threadIndex)
{
	dFloat Ixx;
	dFloat Iyy;
	dFloat Izz;
	dFloat mass;

	// for this tutorial the only external force in the Gravity
	NewtonBodyGetMassMatrix(body, &mass, &Ixx, &Iyy, &Izz);

	//dVector gravityForce(0.0f, mass * GEApp::GameEngine()->GetWorld()->gravity, 0.0f, 1.0f);

	GEEntity* cam = (GEEntity*) GEApp::GameEngine()->Console()->FindObjectByNickName("cam");
	glm::vec3 disp = ((GEEntity*)NewtonBodyGetUserData(body))->GetPosition() - cam->GetPosition() - cam->GetForward()*100.0f;
	disp *= -5.0;

	double gravL = 10000.0/disp.length();
	glm::vec3 grav = glm::normalize(disp)*(float)gravL;

	dVector gravityForce((float)grav.x, (float)grav.y, (float)grav.z, 1.0f);



	NewtonBodySetForce(body, &gravityForce[0]);
}


void GENewton_SetTransformCallback(const NewtonBody* body, const dFloat* matrix, int threadIndex)
{
	//access user data in body.
	GEEntity* ent = (GEEntity*)NewtonBodyGetUserData(body);
	
	if (ent == nullptr) 
		return;
	
	ent->SetPosition(glm::vec3(matrix[12], matrix[13], matrix[14]));

	glm::quat orientation;
	dMatrix newtMat(matrix);

	orientation = glm::quat_cast(NewtToGlm(newtMat));
	ent->SetOrientation(orientation);
}
void GENewton_DestroyBodyCallback(const NewtonBody* body)
{
	//do nothing.
}











