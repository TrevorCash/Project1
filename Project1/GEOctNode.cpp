#include "GEOctNode.h"


GEOctNode::GEOctNode(const GEOctNode* parent) : GEBase()
{
	this->parent = parent;
	*nodes = {nullptr};

}


GEOctNode::~GEOctNode()
{
}



GEOctNode* GEOctNode::GrowUpTowardsPoint(glm::vec3 point)
{
//	if (parent != nullptr)
//	{
//	
//		GEOctNode* newParent = new GEOctNode(nullptr);
//		newParent->nodes[]
//	
//	}
//
}

void GEOctNode::GrowDown()
{

}
