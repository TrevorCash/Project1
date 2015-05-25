#include "GEConsole.h"
#include <iostream>
#include <iterator>

GEConsole::GEConsole()
{
}


GEConsole::~GEConsole()
{
}


void GEConsole::GarbageCollect()
{
	for (auto obj = objectMap.begin(); obj != objectMap.end(); obj++)
	{
		if (((GEBase*)obj->second)->isFreed())
			delete obj->second;

		objectMap.erase(obj);
	}

}


//deletes all objects owed by this console.
void GEConsole::DeleteAll()
{
	for (auto obj = objectMap.begin(); obj != objectMap.end(); obj++)
	{
		delete obj->second;
	}

	objectMap.clear();
}


void GEConsole::AddObject(GEBase* obj)
{
	objectMap.insert(std::pair<unsigned int, GEBase*>(obj->UniqueId(), obj));
}





//Private
