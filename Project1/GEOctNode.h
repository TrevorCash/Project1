#ifndef GE_OCT_NODE
#define GE_OCT_NODE
#include "GEBase.h"
#include "GEEntity.h"
#include "glm\glm.hpp"



class GEOctNode :
	public GEBase
{
public:
	GEOctNode(const GEOctNode* parent);
	~GEOctNode();

	void AddEntity(GEEntity* ent);
	void RemoveEntity(GEEntity* ent);

	GEOctNode* GrowUpTowardsPoint(glm::vec3 point);
	void GrowDown();


private:

	GEOctNode* GenerateNodeAtPos(glm::vec3 pos, int maxLevels);
	
	std::list<GEEntity*> entityList;
	
	const GEOctNode* parent;
	GEOctNode* nodes[8];
};

#endif