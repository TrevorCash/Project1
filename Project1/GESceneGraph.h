#ifndef GE_SCENE_GRAPH_H
#define GE_SCENE_GRAPH_H

#include "GEBase.h"
#include "GEEntity.h"
#include "GEOctNode.h"

class GESceneGraph :
	public GEBase
{
public:
	GESceneGraph();
	~GESceneGraph();

	void AddEntity(GEEntity* ent);

private:

	GEOctNode* rootNode;

};

#endif