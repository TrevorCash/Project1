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



//a GEBase object is the base class for all classes in the engine, all objects are accessable via the console at least.
class GEBase
{

public:
	GEBase(void);
	virtual ~GEBase(void);


	//notifies objects that have references of this object that the memory is about to be freed.
	virtual void Free();
	virtual bool isFreed(){ return isFree; }


	virtual GECLASSTYPE ClassType();
	virtual void EnableNetworking();

	//base tick from console system.
	virtual void OnBaseTickUpdate(double deltaTime);

	
	virtual void PackNetworkUpdate(std::stringstream &dataStream);
	virtual void UnpackNetworkUpdate(std::stringstream &dataStream);


	virtual void SetNickName(std::string name);
	virtual std::string NickName();
	unsigned int UniqueId();

protected:


private:

	bool isFree;
	unsigned int uniqueID;//unique id that is not user changable (used for maps)
	std::string nickName;//user defined nick name for easy finds from the console object.

	unsigned int networkId;//id for use in networking - identical objects across network will have identical networkId's
	bool isNetworked;




};

#endif