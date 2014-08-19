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

	objectSimulationList.push_back(obj);
}
void GEConsole::OnSubscriberRemove(GEBase* obj)
{
	GEBase::OnSubscriberRemove(obj);
}







//Updates All Subscribers
void GEConsole::BaseTickUpdate(double deltaTime)
{

	for (std::list<GEBase*>::iterator it = objectSimulationList.begin(); it != objectSimulationList.end(); it++)
	{
		GEBase* obj = *it;
		obj->OnBaseTickUpdate(deltaTime);
	}
}







//Private
