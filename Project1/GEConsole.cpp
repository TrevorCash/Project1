#include "GEConsole.h"
#include <iostream>
#include <iterator>

GEConsole::GEConsole() : GEBase()
{
}


GEConsole::~GEConsole()
{
	for (auto it = subscribers.begin(); it != subscribers.end();)
	{
		it->second->Delete();
		it++;
	}
	GarbageCollectAll();
}


//Base tick 
void GEConsole::OnBaseTickUpdate(double deltaTime)
{
	GEBase::OnBaseTickUpdate(deltaTime);

	GarbageCollectAll();
}


//Does Imediate Garbage Collection
void GEConsole::GarbageCollectAll()
{
	//Garbage Collect Subscriptions!
	for (auto it = subscribers.cbegin(); it != subscribers.cend() /* not hoisted */; /* no increment */)
	{
		GEBase* obj = it->second;
		if (obj->IsDeleted())
		{
			obj->subscriptions.erase(this->NickName());
			subscribers.erase(it++);
			delete obj;
			
		}
		else
		{
			++it;
		}
	}
}









//subscriptions overrides
void GEConsole::SubscribeTo(GEBase* const obj)
{
	GEBase::SubscribeTo(obj);
}
void GEConsole::UnSubscribeFrom(GEBase* const obj)
{
	GEBase::UnSubscribeFrom(obj);
}

void GEConsole::OnSubscriberAdd(GEBase* obj)
{
	GEBase::OnSubscriberAdd(obj);
}
void GEConsole::OnSubscriberRemove(GEBase* obj)
{
	GEBase::OnSubscriberRemove(obj);
}














//Private
