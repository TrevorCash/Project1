#ifndef GE_BASE
#define GE_BASE

#include <string>
#include <iostream>

enum GECLASSTYPE
{
	Base = 1, Entity, EntityRenderable, EntityRigidBody, MeshData, ModelData
};



//a GEBase object is the base class for all classes in the engine, all objects are owned by the console
//objects can be subscribed to sub systems like the world or renderer.  only the console has permission to actually delete an object
//but the runtime code can call "Delete()" on an object and all subscriberers will remove the object from their containers and finally
//the console will run garbage collection and free the memory...
class GEBase
{

public:
	GEBase(void);
	virtual ~GEBase(void);


	virtual GECLASSTYPE ClassType();

	virtual void AddToSimulation();
	virtual void EnableNetworking();

	//base tick from console system.
	virtual void OnBaseTickUpdate(double deltaTime);

	
	virtual void PackNetworkUpdate(std::stringstream &dataStream);
	virtual void UnpackNetworkUpdate(std::stringstream &dataStream);


	virtual void Delete();//marks the object for deletion next time the console tries to update it.
	bool IsDeleted();//if the object is marked for deletion.
	bool IsObject();//is it a valid object (not deleted)

	virtual void IncreaseSubscriptions();
	virtual void DecreaseSubscriptions();
	int NumSubscriptions();

	virtual void SetNickName(std::string name);
	virtual std::string NickName();



protected:


private:
	bool deleted;
	int subscriptions;//how many "services" the object is subscribed to. a service is like a renderer or world.. 
	std::string nickName;//user defined nick name for easy finds from the console object.
	unsigned int networkId;//id for use in networking - identical objects across network will have identical networkId's
	bool isNetworked;
};

#endif