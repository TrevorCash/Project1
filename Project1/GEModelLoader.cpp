#include "GEModelLoader.h"
#include "GEMeshData.h"
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <algorithm>
#include <string>


GEModelLoader::GEModelLoader() : GEBase()
{
}


GEModelLoader::~GEModelLoader()
{
}

//loads external model into GEModelData Structure. as of now only assimp is used..
bool GEModelLoader::LoadIntoModel(GEModelData* model, std::string filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate);

	for (unsigned int m = 0; m < scene->mNumMeshes; m++)
	{
		GEMeshData* mesh = new GEMeshData();
		mesh->SubscribeTo(model);
		model->meshDataList.push_back(mesh);

		const aiMesh* pAiMesh = scene->mMeshes[m];
		
		//fill vertices;
		mesh->vertices = new float[4 * pAiMesh->mNumVertices];
		mesh->numVertices = pAiMesh->mNumVertices;
		for (unsigned int v = 0; v < pAiMesh->mNumVertices; v++)
		{
			mesh->vertices[v * 4 + 0] = pAiMesh->mVertices[v].x;
			mesh->vertices[v * 4 + 1] = pAiMesh->mVertices[v].y;
			mesh->vertices[v * 4 + 2] = pAiMesh->mVertices[v].z;
			mesh->vertices[v * 4 + 3] = 1.0f;//w
		}

		//fill normals;
		mesh->normals = new float[3 * pAiMesh->mNumVertices];
		mesh->numNormals = pAiMesh->mNumVertices;
		for (unsigned int n = 0; n < pAiMesh->mNumVertices; n++)
		{
			mesh->normals[n * 3 + 0] = pAiMesh->mNormals[n].x;
			mesh->normals[n * 3 + 1] = pAiMesh->mNormals[n].y;
			mesh->normals[n * 3 + 2] = pAiMesh->mNormals[n].z;
		}


		//fill indices
		mesh->indices = new unsigned int[pAiMesh->mNumFaces*3];
		mesh->numIndices = pAiMesh->mNumFaces*3;
		for (unsigned int f = 0; f < pAiMesh->mNumFaces; f++)
		{
			if (pAiMesh->mFaces[f].mNumIndices < 3)
			{
				std::cout << "GEModelLoader: face found with less than 3 indices!!";
				assert(EXIT_FAILURE);
			}

			mesh->indices[f * 3 + 0] = pAiMesh->mFaces[f].mIndices[0];
			mesh->indices[f * 3 + 1] = pAiMesh->mFaces[f].mIndices[1];
			mesh->indices[f * 3 + 2] = pAiMesh->mFaces[f].mIndices[2];
			
		}

	}
	
	importer.FreeScene();
	return true;
}


//////////////////////////////////////////////////////////////////////////
//Private