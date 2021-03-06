#ifndef GE_RENDERER
#define GE_RENDERER

#include "gebase.h"
#include "GEModelData.h"
#include "GEModelLoader.h"
#include <vector>


class GEWorld;
class GEContext;
class GEClient;
class GEShader;
class GEShaderProgram;
class GEEntityRenderable;

class GERenderer
{
public:
	GERenderer(GEContext* pContext);
	~GERenderer(void);

	void AddEntity(GEEntityRenderable* ent);
	void RemoveAllEntities();
	
	void Render(GEClient* client, GEWorld* world, float interpolation);
	
	std::vector<GEModelData*>& ModelData();

private:
	void LoadRenderingAssets();
	void FreeRenderingAssets();
	void Initialize();

	GEContext* context;

	std::vector<GEShaderProgram*> shaderProgramList;
	std::vector<GEShader*> shaderList;


	GEModelLoader modelLoader;
	std::vector<GEModelData*> modelDataList;
	
	
	//entity managment
	std::list<GEEntityRenderable*> entityList;
	
	void DrawRenderable(GEEntityRenderable* entity);
};

#endif