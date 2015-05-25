#include "GEMeshData.h"


GEMeshData::GEMeshData() : GEBase(false)
{
	classType = GECLASS_MeshData;

	vertices = nullptr;
	numVertices = 0;

	normals = nullptr;
	numNormals = 0;

	indices = nullptr;
	numIndices = 0;
}


GEMeshData::~GEMeshData()
{
	if (vertices != nullptr)
	{
		delete[] vertices;
	}
	if (normals != nullptr)
	{
		delete[] normals;
	}
	if (indices != nullptr)
	{
		delete[] indices;
	}
}
