#include "GEOctNode.h"


GEOctNode::GEOctNode(const GEOctNode* parent) : GEBase()
{
	this->parent = parent;
	*nodes = {nullptr};

}


GEOctNode::~GEOctNode()
{
}
