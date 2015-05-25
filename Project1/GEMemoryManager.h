#ifndef GE_MEMORY_MANAGER
#define GE_MEMORY_MANAGER

#include "GEBase.h"

#include <map>


class GEMemoryManager
{
public:
	GEMemoryManager();
	~GEMemoryManager();

	void AddObjectToCan(GEBase* obj);
	void DeleteObjectNow(GEBase* obj);

	void GarbageCollectAll();

	std::map<GEBase*, GEBase*> garbageCan;


};

#endif