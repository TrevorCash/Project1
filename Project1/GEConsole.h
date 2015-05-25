#pragma once
#include "GEBase.h"
#include <list>
#include <map>

//The console has a list of all active base class objects.
class GEConsole
{
public:
	GEConsole();
	virtual ~GEConsole();

	void GarbageCollect();
	
	//deletes all objects owed by this console.
	void DeleteAll();

	void AddObject(GEBase* obj);

protected:

	std::map<unsigned int, GEBase*> objectMap;
};

