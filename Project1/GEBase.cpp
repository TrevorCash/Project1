#include "GEBase.h"
#include "GEApp.h"
#include "GEConsole.h"
#include "GENetworkManager.h"
#include <iostream>
#include <sstream>
#include <string>

//public:
GEBase::GEBase(void)
{
	deleted = false;
	isNetworked = false;
	
	//nicknames default to address values..
	UINT64 val = UINT64(this);
	nickName = std::to_string(val);
}


GEBase::~GEBase(void)
{
	
}


GECLASSTYPE GEBase::ClassType()
{
	return GECLASSTYPE::Base;
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

//subscription system
void GEBase::SubscribeTo(GEBase* const obj)
{
	if (obj == this)
		return;

	obj->subscribers.insert(std::pair<std::string,GEBase*>(this->nickName, this));
	this->subscriptions.push_back(obj);
	obj->OnSubscriberAdd(this);
}
void GEBase::UnSubscribeFrom(GEBase* const obj)
{
	obj->subscribers.erase(this->nickName);
	obj->OnSubscriberRemove(this);
}
void GEBase::UnSubscribeFromAll()
{
	for (GEBase* subscript : subscriptions){
		UnSubscribeFrom(subscript);
	}
	subscriptions.clear();
}

//Subscribers should not be able have multiple entries into a subscription.
void GEBase::OnSubscriberAdd(GEBase* obj)
{
	
}
void GEBase::OnSubscriberRemove(GEBase* obj)
{

}

GEBase* GEBase::FindSubscriberByName(const std::string &nick)
{
	if (!subscribers.count(nickName))
		return nullptr;

	std::map<std::string, GEBase*>::iterator it;
	it = subscribers.find(nickName);

	if (it == subscribers.end())
	{
		std::cout << "GEBase: FindObjectByName - name not found" << std::endl;
		return nullptr;
	}
	return it->second;
}




void GEBase::SetNickName(std::string name)
{
	nickName = name;
	RefreshSubscriptions();
}

std::string GEBase::NickName()
{
	return nickName;
}



//Private:
void GEBase::RefreshSubscriptions()
{
	std::vector<GEBase*> oldSubscriptions = subscriptions;
	UnSubscribeFromAll();
	for (GEBase* sub : oldSubscriptions)
		SubscribeTo(sub);
}