#include "GEConsole.h"
#include <iostream>
#include <iterator>

GEConsole::GEConsole()
{
	deletedObjCount = 0;
}


GEConsole::~GEConsole()
{
	for (GEBase* obj : objectSimulationList)
		delete obj;
}

//parses through all objects owned by console and actaully free's memory
//of "deleted" objects.
void GEConsole::CollectGarbage()
{
	for (std::list<GEBase*>::iterator it = objectSimulationList.begin(); it != objectSimulationList.end(); it++)
	{
		GEBase* obj = *it;
		if (obj->IsDeleted() && obj->NumSubscriptions() <= 0)
		{
			std::list<GEBase*>::iterator erasableIt = it;
			std::advance(it, 1);
			objectSimulationList.erase(erasableIt);
			delete obj;
		}
	}
}

//returns how many objects are currently marked as deleted, but are still not freed
//call after collectgarbage to see the most recent state.
unsigned int GEConsole::GetUnfreedObjectCount(bool verbose)
{
	unsigned int unfreedCnt = 0;
	for (std::list<GEBase*>::iterator it = objectSimulationList.begin(); it != objectSimulationList.end(); it++)
	{
		GEBase* obj = *it;
		if (obj->IsDeleted())
		{
			if (verbose)
			{
				std::cout << "Object Not Freed: " << obj->NickName();
				std::cout << "---NumSubscriptions: " << obj->NumSubscriptions() << std::endl;
			}
				
				
			unfreedCnt++;
		}
	}
	return unfreedCnt;
}


//Updates All Objects In the Engine..
void GEConsole::BaseTickUpdate(double deltaTime)
{
	//for now collect garbage every base tick
	CollectGarbage();
	for (std::list<GEBase*>::iterator it = objectSimulationList.begin(); it != objectSimulationList.end(); it++)
	{
		GEBase* obj = *it;
		if (!obj->IsDeleted())
			obj->OnBaseTickUpdate(deltaTime);
	}
}

//Adds an Object to the engine (done in object's contructor)
void GEConsole::AddToSimulation(GEBase* object)
{
	objectSimulationList.push_back((GEBase*)object);
}

//tries to add a nickname - pointer pair, returns success
bool GEConsole::AddToNickNames(GEBase* object)
{
	if (object->NickName().empty())
		return false;
	
	if (objectsByName.count(object->NickName()))
		return true;
	
	objectsByName.insert(std::pair<std::string, GEBase*>(object->NickName(), (GEBase*)object));

	return true;
}

GEBase* GEConsole::FindObjectByNickName(std::string nickName)
{
	if (!objectsByName.count(nickName))
		return nullptr;

	std::map<std::string, GEBase*>::iterator it;
	it = objectsByName.find(nickName);
	if (it == objectsByName.end())
	{
		std::cout << "GEConsole: FindObjectByName - name not found" << std::endl;
		return nullptr;
	}
	return it->second;
}




//Private
