#ifndef GE_OBJECT_POOL
#define GE_OBJECT_POOL

#include <vector>
#include <list>


template <class ObjectType>
class GEObjectPool
{

public:

	GEObjectPool(unsigned long int initialSize)
	{
		pool.resize(initialSize);
		currentIndx = 0;
		usedObjects = 0;
	}
	~GEObjectPool(){};

	ObjectType* CreateObject(unsigned long int &indx)
	{
		while (pool[currentIndx].IsDeleted())
		{
			currentIndx++;
			if (currentIndx > pool.size() - 1)
				currentIndx = 0;
		}
		usedObjects++;
		indx = currentIndx;
		return &pool[currentIndx];
	}

	bool DeleteObject(unsigned long int objIndx)
	{
		pool[currentIndx].Delete();
		usedObjects--;
		currentIndx = objIndx;
	}

protected:
	
	std::vector<ObjectType> pool;
	unsigned long int currentIndx;
	unsigned long int usedObjects;
};




#endif
