#include "GEConsole.h"
#include <iostream>
#include <iterator>

GEConsole::GEConsole() : GEBase()
{
}


GEConsole::~GEConsole()
{
}


//Base tick 
void GEConsole::OnBaseTickUpdate(double deltaTime)
{
	GEBase::OnBaseTickUpdate(deltaTime);


	//Garbage Collect Subscriptions!
	std::map<std::string, GEBase*>::iterator it = subscribers.begin();
	while (it != subscribers.end())
	{
		GEBase* obj = it->second;
		if (obj->IsDeleted())
		{
			delete obj;
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
