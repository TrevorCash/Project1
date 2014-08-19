#include "GEConsole.h"
#include <iostream>
#include <iterator>

GEConsole::GEConsole() : GEBase()
{
}


GEConsole::~GEConsole()
{
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




//Updates All Subscribers
void GEConsole::BaseTickUpdate(double deltaTime)
{

	for (std::map<std::string, GEBase*>::iterator it = subscribers.begin(); it != subscribers.end(); it++)
	{
		GEBase* obj = it->second;
		obj->OnBaseTickUpdate(deltaTime);
	}
}







//Private
