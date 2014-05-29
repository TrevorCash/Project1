#pragma once
#include "GEBase.h"
#include <list>
#include <map>

//The Console Owns All Objects and is responsible for the simple garbage collection.
class GEConsole
{
public:
	GEConsole();
	~GEConsole();

	void CollectGarbage();
	unsigned int GetUnfreedObjectCount(bool verbose = true);

	void BaseTickUpdate(double deltaTime);
	void AddToSimulation(GEBase* object);
	bool AddToNickNames(GEBase* object);
	GEBase* FindObjectByNickName(std::string nickName);


private:
	std::list<GEBase*> objectSimulationList;
	void CleanSimulationList();

	unsigned int deletedObjCount;


	std::map<std::string, GEBase*> objectsByName;
};

