#pragma once
#include "GEBase.h"
#include <list>
#include <map>

//The Console is the subscription to all GEBase derived objects. (ie all GEBase derived object subscribe to the console)
class GEConsole : GEBase
{
public:
	GEConsole();
	~GEConsole();


	//subscription system
	virtual void SubscribeTo(GEBase* const obj);
	virtual void UnSubscribeFrom(GEBase* const obj);

	virtual void OnSubscriberAdd(GEBase* obj);
	virtual void OnSubscriberRemove(GEBase* obj);

	void BaseTickUpdate(double deltaTime);

private:
	std::list<GEBase*> objectSimulationList;


};

