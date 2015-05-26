#ifndef GE_BASE
#define GE_BASE

#include "GECLASSTYPES.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>




//a GEBase object is the base class for all classes in the engine, all objects are owned by the console
//objects can be subscribed to sub systems like the world or renderer.  only the console has permission to actually delete an object
//but the runtime code can call "Delete()" on an object and all subscriberers will remove the object from their containers and eventually
//the console will run garbage collection and free the memory...
class GEBase
{

public:
	GEBase(bool autoSubscribe = true);
	virtual ~GEBase(void);


	virtual GECLASSTYPES ClassType();
	virtual void EnableNetworking();

	//base tick from console system.
	virtual void OnBaseTickUpdate(double deltaTime);

	
	virtual void PackNetworkUpdate(std::stringstream &dataStream);
	virtual void UnpackNetworkUpdate(std::stringstream &dataStream);



	virtual bool SubscribeTo(GEBase* const obj);
	virtual void UnSubscribeFrom(GEBase* const obj);
	virtual void DetachSubscribers();

	unsigned int NumSubscriptions();

	virtual void OnSubscriberAdd(GEBase* obj);
	virtual void OnSubscriberRemove(GEBase* obj);
	virtual void OnSubscriptionRemoved(GEBase* sub);
	
	bool IsSubscribedTo(std::string nickName);
	GEBase* FindSubscriptionByName(const std::string &nick);
	GEBase* FindSubscriberByName(const std::string &nick);
	
	virtual void SetNickName(std::string name);
	virtual std::string NickName();

protected:

	virtual void UnSubscribeFromAll();




	std::map<std::string, GEBase*> subscribers;
	std::map<std::string, GEBase*> subscriptions;

	std::string nickName;//user defined nick name for easy finds from the console object.

	unsigned int networkId;//id for use in networking - identical objects across network will have identical networkId's
	bool isNetworked;


	GECLASSTYPES classType;


};

#endif