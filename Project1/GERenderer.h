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
	virtual ~GERenderer(void);
	
	void LoadRenderingAssets();
	void FreeRenderingAssets();
	void Initialize();
	void Render(GEClient* client, GEWorld* world, float interpolation);
	
	std::vector<GEModelData*>& ModelData();

private:


	GEContext* context;

	std::vector<GEShaderProgram*> shaderProgramList;
	std::vector<GEShader*> shaderList;
	std::vector<GEEntityRenderable*> entityList;

	GEModelLoader modelLoader;
	std::vector<GEModelData*> modelDataList;
	
	void DrawRenderable(GEEntityRenderable* entity);
};

#endif