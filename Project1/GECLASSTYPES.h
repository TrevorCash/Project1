//All Class Types should be listed Here
enum GECLASSBITS
{
	GECLASSBIT_Base = 1,
	GECLASSBIT_Console = 2,
	GECLASSBIT_Entity = 4,
	GECLASSBIT_EntityRenderable = 8,
	GECLASSBIT_EntityRigidBody = 16,
	GECLASSBIT_MeshData = 32,
	GECLASSBIT_ModelData = 64
};

enum GECLASSTYPES
{
	GECLASS_Base = (GECLASSBIT_Base),
	GECLASS_Console = (GECLASSBIT_Base | GECLASSBIT_Console),
	GECLASS_Entity = (GECLASSBIT_Base | GECLASSBIT_Entity),
	GECLASS_EntityRenderable = (GECLASSBIT_Base | GECLASSBIT_Entity | GECLASSBIT_EntityRenderable),
	GECLASS_EntityRigidBody = (GECLASSBIT_Base | GECLASSBIT_Entity | GECLASSBIT_EntityRigidBody),
	GECLASS_MeshData = (GECLASSBIT_Base | GECLASSBIT_MeshData),
	GECLASS_ModelData = (GECLASSBIT_Base | GECLASSBIT_ModelData)
};