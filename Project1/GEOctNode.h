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

	GEOctNode* AddEntity(GEEntity* ent);
	void RemoveEntity(GEEntity* ent);


private:

	GEOctNode* GenerateNodeAtPos(glm::vec3 pos, int maxLevels);
	
	std::list<GEEntity*> entityList;
	
	const GEOctNode* parent;
	GEOctNode* nodes[8];
};

#endif