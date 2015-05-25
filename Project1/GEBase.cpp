#include "GEBase.h"
#include "GEApp.h"
#include "GEConsole.h"
#include "GENetworkManager.h"
#include <iostream>
#include <sstream>
#include <string>

//public:
GEBase::GEBase(void)
{
	isFree = false;
	isNetworked = false;
	
	//nicknames and id's default to address values..
	UINT64 val = UINT64(this);
	nickName = std::to_string(val);
	uniqueID = nickName;

	//all base class object pointers are added to console
	GEApp::Console()->AddObject(this);
	
}


GEBase::~GEBase(void)
{
}


//notifies objects that have references of this object that the memory is about to be freed.
void GEBase::Free()
{
	isFree = false;
}

GECLASSTYPE GEBase::ClassType()
{
	return GECLASSTYPE::Base;
}


void GEBase::EnableNetworking()
{
	if (isNetworked == false)
		GEApp::GameEngine()->GetNetwork()->AddObject(this);
	else
		std::cout << "Object Already Networked!";
}

void GEBase::PackNetworkUpdate(std::stringstream &dataStream)
{
	//baseclass PackNewtorkUpdate
	dataStream << networkId;
}
void GEBase::UnpackNetworkUpdate(std::stringstream &dataStream)
{
	dataStream >> networkId;
}


void GEBase::OnBaseTickUpdate(double deltaTime)
{
}



//Resets The Nick name (Object Identifier)
void GEBase::SetNickName(std::string name)
{
	nickName = name;
}

//returns the object identifier
std::string GEBase::NickName()
{
	return nickName;
}


