#ifndef GE_WORLD
#define GE_WORLD


#include "gebase.h"
#include "GEEntityRigidBody.h"
#include "newton.h"
#include <vector>

#define WORLDTICKMUL 60.0


class GEWorld
{
public:
	GEWorld(void);
	~GEWorld(void);

	void Initialize();
	void InitializeNewton();
	virtual void BaseTickUpdate(double deltaTime);

	void AddEntity(GEEntity* entity);
	void RemoveAllEntities();

	double gravity;
	NewtonWorld* newtonWorld;

private:

	std::list<GEEntity*> entityList;//list of entities.

};

//Newton Dynamics Callbacks
void GENewton_ApplyForceAndTorqueCallback(const NewtonBody* body, dFloat timestep, int threadIndex);
void GENewton_SetTransformCallback(const NewtonBody* body, const dFloat* matrix, int threadIndex);
void GENewton_DestroyBodyCallback(const NewtonBody* body);


#endif