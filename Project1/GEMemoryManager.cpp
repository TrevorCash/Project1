#include "GEMemoryManager.h"


GEMemoryManager::GEMemoryManager()
{
}


GEMemoryManager::~GEMemoryManager()
{
}




void GEMemoryManager::AddObjectToCan(GEBase* obj)
{
	auto pair = garbageCan.insert(std::pair<GEBase*, GEBase*>(obj, obj));
	if (pair.second == false)
		std::cout << "GEMemoryManager: Object Already In Can!";
}
void GEMemoryManager::DeleteObjectNow(GEBase* obj)
{
	//TODO Not Yet Implemented
}


//deletes all items in trash can and returns the memory to the heap.
void GEMemoryManager::GarbageCollectAll()
{
	for (auto it = garbageCan.begin(); it != garbageCan.end(); it++)
	{
		delete it->first;
	}
	garbageCan.clear();
}
