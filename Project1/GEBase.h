#ifndef GE_BASE
#define GE_BASE

#include <string>
#include <iostream>
#include <map>
#include <vector>

enum GECLASSTYPE
{
	Base = 1, 
	Entity, 
	EntityRenderable, 
	EntityRigidBody, 
	MeshData,
	ModelData
};



//a GEBase object is the base class for all classes in the engine, all objects are owned by the console
//objects can be subscribed to sub systems like the world or renderer.  only the console has permission to actually delete an object
//but the runtime code can call "Delete()" on an object and all subscriberers will remove the object from their containers and eventually
//the console will run garbage collection and free the memory...
class GEBase
{

public:
	GEBase(void);
	virtual ~GEBase(void);


	virtual GECLASSTYPE ClassType();
	virtual void EnableNetworking();

	//base tick from console system.
	virtual void OnBaseTickUpdate(double deltaTime);

	
	virtual void PackNetworkUpdate(std::stringstream &dataStream);
	virtual void UnpackNetworkUpdate(std::stringstream &dataStream);


	//subscription system
	//////////////////////
	virtual void SubscribeTo(GEBase* const obj);
	virtual void UnSubscribeFrom(GEBase* const obj);
	virtual void UnSubscribeFromAll();
	virtual void DetachSubscribers();

	unsigned int NumSubscriptions();


public:
	virtual void OnSubscriberAdd(GEBase* obj);
	virtual void OnSubscriberRemove(GEBase* obj);
	virtual void OnSubscriptionRemoved(GEBase* sub);

	bool IsSubscribedTo(std::string nickName);


	GEBase* FindSubscriberByName(const std::string &nick);
	
	std::map<std::string, GEBase*> subscribers;
	std::map<std::string, GEBase*> subscriptions;
	//////////////////////

	virtual void SetNickName(std::string name);
	virtual std::string NickName();

protected:


private:

	bool deleted;
	std::string nickName;//user defined nick name for easy finds from the console object.

	unsigned int networkId;//id for use in networking - identical objects across network will have identical networkId's
	bool isNetworked;





};

#endif