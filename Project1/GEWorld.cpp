
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

GEWorld::GEWorld(void) : GEBase()
{
	gravity = -9.81;
	InitializeNewton();
}


GEWorld::~GEWorld(void)
{
	NewtonDestroy(newtonWorld);
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


	GEEntityRigidBody* rigid1 = new GEEntityRigidBody();
	

	GEEntityRenderable* a = new GEEntityRenderable();
	a->modelData = GEApp::GameEngine()->GetRenderer()->ModelData()[0];

	GEEntityRenderable* b = new GEEntityRenderable();
	b->modelData = GEApp::GameEngine()->GetRenderer()->ModelData()[0];

	GEEntityRenderable* c = new GEEntityRenderable();
	c->modelData = GEApp::GameEngine()->GetRenderer()->ModelData()[0];


	b->MoveBy(glm::vec3(5, 0, 0));
	c->MoveBy(glm::vec3(5, 5, 0));
	rigid1->SetNickName("bob");
	a->SetParent(rigid1);
	b->SetParent(rigid1);
	c->SetParent(rigid1);



	GEEntityRigidBody* prevBody = nullptr;
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 2; i++)
		{
			////do some testing with physics parenting!
			GEEntityRigidBody* BodyA = new GEEntityRigidBody();
			BodyA->SetPosition(glm::ballRand(2.2f) + glm::vec3(0, 5*j, 0));
			BodyA->SetRotation(45, glm::vec3(1, 0, 0));

			GEEntityRenderable* VisBodyA = new GEEntityRenderable();
			VisBodyA->modelData = GEApp::GameEngine()->Renderer()->ModelData()[0];
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


//Updates the Logic In the world, and updates subscribers
void GEWorld::BaseTickUpdate(double deltaTime)
{
	//Let Newton Do The Multi-Threaded Simulation Update.
	NewtonUpdateAsync(newtonWorld, deltaTime);
	
	//Blocking Main Thread Till Finished.
	NewtonWaitForUpdateToFinish(newtonWorld);

	if (KeyHit(GLFW_KEY_DELETE))
	{
		GEApp::GameEngine()->Console()->FindSubscriberByName("bob")->UnSubscribeFromAll();
	}
	if (KeyHit(GLFW_KEY_P))
	{
		delete (GEEntity*)GEApp::GameEngine()->Console()->FindSubscriberByName("bob");
	}

	for (std::map<std::string, GEBase*>::iterator it = subscribers.begin(); it != subscribers.end(); it++)
	{
		GEBase* obj = it->second;
		obj->OnBaseTickUpdate(deltaTime);
	}
	
}


//subscription behalvior
void GEWorld::OnSubscriberAdd(GEBase* obj)
{
	GEBase::OnSubscriberAdd(obj);
	//TODO Throw Exception if not based on GEEntity
}


void GEWorld::OnSubscriberRemove(GEBase* obj)
{
	GEBase::OnSubscriberRemove(obj);

}





//Newton Dynamics Callbacks
///////////////////////////////////////////////////////////////////////////////////////////////////
void GENewton_ApplyForceAndTorqueCallback(const NewtonBody* body, dFloat timestep, int threadIndex)
{
	if (NewtonBodyGetUserData(body) == nullptr)
		return;

	dFloat Ixx;
	dFloat Iyy;
	dFloat Izz;
	dFloat mass;

	// for this tutorial the only external force in the Gravity
	NewtonBodyGetMassMatrix(body, &mass, &Ixx, &Iyy, &Izz);

	//dVector gravityForce(0.0f, mass * GEApp::GameEngine()->GetWorld()->gravity, 0.0f, 1.0f);

	GEEntity* cam = (GEEntity*) GEApp::GameEngine()->Console()->FindSubscriberByName("cam");
	glm::vec3 disp = ((GEEntity*)NewtonBodyGetUserData(body))->GetPosition() - cam->GetPosition() - cam->GetForward()*50.0f;
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











