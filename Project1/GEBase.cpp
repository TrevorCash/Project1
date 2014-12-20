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

	if (GEApp::GameEngine()->GetConsole() != nullptr)
		SubscribeTo((GEBase*)GEApp::GameEngine()->GetConsole());
}


GEBase::~GEBase(void)
{
	SendHardDeletionWarningToSubscriptions();
}


GECLASSTYPE GEBase::ClassType()
{
	return GECLASSTYPE::Base;
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
	UnSubscribeFromAll();
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
	this->subscriptions.insert(std::pair<std::string, GEBase*>(obj->nickName, obj));
	obj->OnSubscriberAdd(this);
}
void GEBase::UnSubscribeFrom(GEBase* const obj)
{
	if (obj == this)
	{
		return;
	}
	obj->subscribers.erase(this->nickName);
	obj->OnSubscriberRemove(this);
	subscriptions.erase(obj->nickName);
}
void GEBase::UnSubscribeFromAll()
{
	std::map<std::string, GEBase*>::iterator it = subscriptions.begin();
	while (it != subscriptions.end())
	{
		GEBase* sub = it->second;
		it++;
		UnSubscribeFrom(sub);
	}

	subscriptions.clear();
}
//called direct from destructor, notifies all subscriptions of a hard delete!
void GEBase::SendHardDeletionWarningToSubscriptions()
{
	std::map<std::string, GEBase*>::iterator it = subscriptions.begin();
	while (it != subscriptions.end())
	{
		GEBase* sub = it->second;
		it++;
		sub->OnHardDeletionWarningFromSubscriber(sub);
	}
}

//Subscribers should not be able have multiple entries into a subscription.
void GEBase::OnSubscriberAdd(GEBase* obj)
{

}
void GEBase::OnSubscriberRemove(GEBase* obj)
{

}
void GEBase::OnSubscriptionRemoved(GEBase* sub)
{

}
void GEBase::OnHardDeletionWarningFromSubscriber(GEBase* obj)
{
	//obj is about to be hard deleted!
	//default behalvior is to remove from our subscriber list:
	obj->UnSubscribeFrom(this);
}



bool GEBase::IsSubscribedTo(std::string nickName)
{
	if (FindSubscriberByName(nickName))
		return true;
	else
		return false;
}

GEBase* GEBase::FindSubscriberByName(const std::string &nick)
{
	std::map<std::string, GEBase*>::iterator it;
	it = subscribers.find(nick);

	if (it == subscribers.end())
	{
		std::cout << "GEBase: FindObjectByName - name not found" << std::endl;
		return nullptr;
	}
	return it->second;
}




void GEBase::SetNickName(std::string name)
{

	std::map<std::string, GEBase*> oldSubscriptions = subscriptions;
	UnSubscribeFromAll();
	
	nickName = name;
	
	for (auto pair : oldSubscriptions)
		SubscribeTo(pair.second);

}

std::string GEBase::NickName()
{
	return nickName;
}


