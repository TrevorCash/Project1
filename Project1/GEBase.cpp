#include "GEBase.h"
#include "GEApp.h"
#include "GEConsole.h"
#include "GENetworkManager.h"
#include "GEMemoryManager.h"
#include <iostream>
#include <sstream>
#include <string>


//public:
GEBase::GEBase(bool autoSubscribe)
{
	classType = GECLASS_Base;


	isNetworked = false;
	
	//nicknames default to address values..
	UINT64 val = UINT64(this);
	nickName = std::to_string(val);

	if (autoSubscribe)
	{
		SubscribeTo(GEApp::Console());
	}

}


GEBase::~GEBase(void)
{
}


GECLASSTYPES GEBase::ClassType()
{
	return classType;
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



//subscription system
void GEBase::SubscribeTo(GEBase* const obj)
{
	//Dont allow subscribing to yourself..
	if (obj == this)
		return;

	//Dont allow double subscriptions
	if (IsSubscribedTo(obj->nickName))
		return;
	
	obj->subscribers.insert(std::pair<std::string, GEBase*>(this->nickName, this));
	this->subscriptions.insert(std::pair<std::string, GEBase*>(obj->nickName, obj));
	obj->OnSubscriberAdd(this);
}
void GEBase::UnSubscribeFrom(GEBase* const obj)
{
	if (obj == this)
		return;

	obj->subscribers.erase(this->nickName);
	obj->OnSubscriberRemove(this);
	subscriptions.erase(obj->nickName);

	////////////////////////////////////////
	//if we have unsubscribed from our last subscription,
	//that mean we can delete this object when possible
	//notify the memory manager that we need garbage collected!

	if(NumSubscriptions() <= 0)
	{
		DetachSubscribers();
		GEApp::MemoryManager()->AddObjectToCan(this);
	}
}
//Unsubscribes from all DOES NOT Trigger garbage collection!
void GEBase::UnSubscribeFromAll()
{
	std::map<std::string, GEBase*>::iterator it = subscriptions.begin();
	while (it != subscriptions.end())
	{
		GEBase* sub = it->second;
		
		subscriptions.erase(it++);
		sub->subscribers.erase(this->nickName);
	}

}
//all objects currently subscribed to this are un-subscribed
void GEBase::DetachSubscribers()
{
	auto oldSubscribers = subscribers;
	for (auto it = oldSubscribers.begin(); it != oldSubscribers.end(); it++)
	{
		it->second->UnSubscribeFrom(this);
	}
}

unsigned int GEBase::NumSubscriptions()
{
	return subscriptions.size();
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



//Resets The Nick name (Object Identifier)
//requires to be re-subscribed to all.
void GEBase::SetNickName(std::string name)
{
	//save old subscriptions
	std::map<std::string, GEBase*> oldSubscriptions = subscriptions;
	
	//unsubscribe
	UnSubscribeFromAll();

	//change nickname
	nickName = name;

	///resubscribe.
	for (auto pair : oldSubscriptions)
		SubscribeTo(pair.second);

}

std::string GEBase::NickName()
{
	return nickName;
}


