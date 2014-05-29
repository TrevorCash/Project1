#include "GENetworkManager.h"
#include <iostream>
#include <sstream>
#include <string>

GENetworkManager::GENetworkManager()
{
	if (enet_initialize() != 0)
	{
		std::cout << "Unable To Initialize Enet.";
	}
}


GENetworkManager::~GENetworkManager()
{
	if (IsServer())
	{
		enet_host_destroy(connection);
	}
	
	enet_deinitialize();
}

bool GENetworkManager::IsServer()
{
	return isServer; 
}

void GENetworkManager::ConfigureAsHost(int port)
{
	ENetAddress address;

	address.port = port;
	enet_address_set_host(&address, "localhost");
	

	connection = enet_host_create(&address /* the address to bind the server host to */,
						32      /* allow up to 32 clients and/or outgoing connections */,
						1      /* allow up to 2 channels to be used, 0 and 1 */,
						0      /* assume any amount of incoming bandwidth */,
						0      /* assume any amount of outgoing bandwidth */);

	if (connection == nullptr)
	{
		std::cout << "Unable To Configure Newtork As Host" << std::endl;
		return;
	}
	isServer = true;

}
void GENetworkManager::ConfigureAsClient()
{
	connection = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		1 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* unlimited bandwidth */,
		0 /* unlimited bandwidthh */);

	if (connection == nullptr)
	{
		std::cout << "Unable To Configure Newtork As Client" << std::endl;
		return;
	}
	isServer = false;
}

bool GENetworkManager::ConnectToHost(char* serverName)
{
	ENetAddress address;
	ENetEvent event;
	ENetPeer *peer;

	address.port = 1234;
	enet_address_set_host(&address, serverName);
	
	
	/* Initiate the connection, allocating the two channels 0 and 1. */
	peer = enet_host_connect(connection, &address, 2, 0);
	if (peer == nullptr)
	{
		std::cout << "No available peers for initiating an ENet connection" << std::endl;
		return false;
	}

	
	/* Wait up to 5 seconds for the connection attempt to succeed. */
	if (enet_host_service(connection, &event, 1000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connection Successfull" << std::endl;
		return true;
	}
	else
	{
		/* Either the 5 seconds are up or a disconnect event was */
		/* received. Reset the peer in the event the 5 seconds   */
		/* had run out without any significant event.            */
		//enet_peer_reset(peer);
		//puts("Connection to some.server.net:1234 failed.");
		enet_peer_reset(peer);
		std::cout << "Connection Timed Out...." << std::endl;
		return false;
	}
	
}

void GENetworkManager::AddObject(GEBase* obj)
{
	objects.push_back(obj);
	updateQueue.push(obj);
}










void GENetworkManager::Update()
{
	//std::cout << "Updating Newtork." << std::endl;
	if (IsServer())
		UpdateServer();
	else
		UpdateClient();
}


//private------------------------------------------------------------------
void GENetworkManager::UpdateServer()
{
	ENetEvent event;
	
	//send out object update in queue!
	GEBase* obj = updateQueue.front();
	updateQueue.pop();

	std::stringstream stream(std::ios::in | std::ios::out);
	obj->PackNetworkUpdate(stream);
	std::string buff;
	stream >> buff;
	
	ENetPacket * packet = enet_packet_create(buff.data(),
		buff.length(),
		ENET_PACKET_FLAG_RELIABLE);



	// processing incoming events:
	if(enet_host_service(connection, &event, 0) > 0) 
	{
		std::cout << "Recieved Incomeing Event.." << std::endl;
		switch (event.type) 
		{
			case ENET_EVENT_TYPE_CONNECT: 
			{
				std::cout << "A new connected has been established" << std::endl;
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE:
			{
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				break;
			}				
		}
	}


}
void GENetworkManager::UpdateClient()
{
	ENetEvent event;
	// processing incoming events:
	if (enet_host_service(connection, &event, 0) > 0)
	{
		std::cout << "Recieved Incomeing Event.." << std::endl;
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
			{
				std::cout << "A new connected has been established" << std::endl;
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE:
			{
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT:
			{
				break;
			}
		}
	}
}