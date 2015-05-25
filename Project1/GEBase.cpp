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

	//All Base Class Objects Subscribe to the console!!
	if (GEApp::GameEngine()->GetConsole() != nullptr)
	{

		GEConsole* console = GEApp::GameEngine()->GetConsole();

		console->subscribers.insert(std::pair<std::string, GEBase*>(this->nickName, this));
		this->subscriptions.insert(std::pair<std::string, GEBase*>(console->nickName, console));
		console->OnSubscriberAdd(this);
	}
}


GEBase::~GEBase(void)
{
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



//subscription system
void GEBase::SubscribeTo(GEBase* const obj)
{
	//Dont allow subscribing to yourself..
	if (obj == this)
		return;

	//Dont allow double subscriptions
	if (IsSubscribedTo(obj->nickName))
		return;
	
	obj->subscribers.insert(std::pair<std::string,GEBase*>(this->nickName, this));
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
}
//Unsubscribes from all except the console
void GEBase::UnSubscribeFromAll()
{
	std::map<std::string, GEBase*>::iterator it = subscriptions.begin();
	while (it != subscriptions.end())
	{
		GEBase* sub = it->second;
		
		if (sub != (GEBase*)GEApp::GameEngine()->GetConsole())
		{
			subscriptions.erase(it++);
			sub->subscribers.erase(this->nickName);
		}
		else
			it++;
	}

}
//all objects currently subscribed to this are un-subscribed
void GEBase::DetachSubscribers()
{
	///TODO SOMETHINGS WRONG HERE ??>>>>>>
	for (auto it = subscribers.begin(); it != subscribers.end(); it++)
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

	std::map<std::string, GEBase*> oldSubscriptions = subscriptions;
	
	//unsubscribe from everything but the console
	UnSubscribeFromAll();

	//as well as the console
	GEConsole* console = GEApp::GameEngine()->GetConsole();

	console->subscribers.erase(name);
	console->OnSubscriberRemove(this);

	nickName = name;

	//Resubscribe to console
	console->subscribers.insert(std::pair<std::string, GEBase*>(this->nickName, this));
	console->OnSubscriberAdd(this);

	//and everyone else
	for (auto pair : oldSubscriptions)
		SubscribeTo(pair.second);

}

std::string GEBase::NickName()
{
	return nickName;
}


