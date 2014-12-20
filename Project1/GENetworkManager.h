#ifndef GE_NETWORK_MANAGER
#define GE_NETWORK_MANAGER

#include "enet\enet.h"
#include <vector>
#include <queue>


#include "GEBase.h"




class GENetworkManager : public GEBase
{
public:
	GENetworkManager();
	~GENetworkManager();

	bool IsServer();

	void ConfigureAsHost(int port);
	void ConfigureAsClient();
	bool ConnectToHost(char* serverName);

	void AddObject(GEBase* obj);

	void Update();
private:

	void UpdateServer();
	void UpdateClient();

	bool isServer;
	ENetHost* connection;

	//all objects that are networked..
	std::vector<GEBase*> objects;

	//update queue, objects that need data transmitted.
	std::queue<GEBase*> updateQueue;
};

#endif