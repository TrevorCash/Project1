#include "GESceneGraph.h"


GESceneGraph::GESceneGraph() : GEBase()
{
}


GESceneGraph::~GESceneGraph()
{
}


void GESceneGraph::AddEntity(GEEntity* ent)
{
	//do insertion here.
	ent->IncreaseSubscriptions();
}

void GESceneGraph::RemoveEntity(GEEntity* ent)
{
	//do removable here
	ent->DecreaseSubscriptions();
}