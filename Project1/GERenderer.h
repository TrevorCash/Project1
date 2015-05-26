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

class GERenderer : public GEBase
{
public:
	GERenderer(GEContext* pContext);
	virtual ~GERenderer(void);
	
	void Render(GEClient* client, GEWorld* world, float interpolation);
	void LoadRenderingAssets();
	void Initialize();
	
	void AddRenderableEntity(GEEntityRenderable* ent);
	
	std::vector<GEModelData*>& ModelData();
	
private:


	GEContext* context;

	std::vector<GEShaderProgram*> shaderProgramList;
	std::vector<GEShader*> shaderList;
	GEModelLoader* modelLoader;
	std::vector<GEModelData*> modelDataList;
	
	std::vector<GEEntityRenderable*> renderableList;


	void DrawRenderable(GEEntityRenderable* entity);

};

#endif