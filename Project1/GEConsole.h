#pragma once
#include "GEBase.h"
#include <list>
#include <map>

//The console serves as a subscription every GEBase Object Should Be Subscribed Too!
//Any Object Subscribed To the Console is memory managed
//The Console Is the Only Class That Is Allowed To Instantiate and Delete Game Engine Objects!

class GEConsole : public GEBase
{
public:
	GEConsole();
	~GEConsole();


	//subscription system
	virtual void SubscribeTo(GEBase* const obj);
	virtual void UnSubscribeFrom(GEBase* const obj);

	virtual void OnSubscriberAdd(GEBase* obj);
	virtual void OnSubscriberRemove(GEBase* obj);

	virtual void OnBaseTickUpdate(double deltaTime);

private:

};

