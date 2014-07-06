#include "GEBase.h"
#include "GEApp.h"
#include "GEConsole.h"
#include "GENetworkManager.h"
#include <iostream>
#include <sstream>
#include <string>


GEObjectPool<GEBase> GEBase::pool = GEObjectPool<GEBase>(1000);


GEBase::GEBase(void)
{
	Initialize();
}


GEBase::~GEBase(void)
{
}


GECLASSTYPE GEBase::ClassType()
{
	return GECLASSTYPE::Base;
}

void GEBase::Initialize()
{
	deleted = false;
	subscriptions = 0;
	isNetworked = false;
}





void GEBase::AddToSimulation()
{
	GEApp::GameEngine()->Console()->AddToSimulation(this);
}


void GEBase::EnableNetworking()
{
	if (isNetworked == false)
		GEApp::GameEngine()->GetNetwork()->AddObject(this);
	else
		std::cout << "Object Already Networked!";
}

void GEBase::PackNetworkUpdate(std::stringstream &dataStream)
{
	//baseclass PackNewtorkUpdate
	dataStream << networkId;
}
void GEBase::UnpackNetworkUpdate(std::stringstream &dataStream)
{
	dataStream >> networkId;
}


void GEBase::OnBaseTickUpdate(double deltaTime)
{
}



//subscriptions
void GEBase::IncreaseSubscriptions()
{
	subscriptions++;
}
void GEBase::DecreaseSubscriptions()
{
	subscriptions--;
}
int GEBase::NumSubscriptions()
{
	return subscriptions;
}




void GEBase::SetNickName(std::string name)
{
	nickName = name;
	bool success = GEApp::GameEngine()->Console()->AddToNickNames(this);
	if (!success)
		std::cout << "Unable To Add NickName to console for object: " << this << std::endl;
}

std::string GEBase::NickName()
{
	return nickName;
}




//marks the object as ready to be freed - the console frees the object when garbage collection
//occurs
void GEBase::Delete()
{
	deleted = true;
}

bool GEBase::IsDeleted()
{
	return deleted;
}
bool GEBase::IsObject()
{
	return !deleted;
}
GEBase* GEBase::Create()
{
	unsigned long int idx;
	GEBase* pNewObject = GEBase::pool.CreateObject(idx);
	pNewObject->poolIndx = idx;
	pNewObject->Initialize();
	return pNewObject;
}



