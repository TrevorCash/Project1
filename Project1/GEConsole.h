#pragma once
#include "GEBase.h"
#include <list>
#include <map>

//The console serves as a subscription every GEBase Object Should Be Subscribed Too!
//Any Object Subscribed To the Console is memory managed
//The Console Is the Only Class That Is Allowed To Instantiate and Delete Game Engine Objects!

class GEConsole : public GEBase
{
public:
	GEConsole();
	virtual ~GEConsole();

};

