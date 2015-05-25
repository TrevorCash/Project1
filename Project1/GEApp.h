#ifndef GE_APP
#define GE_APP

class GEConsole;
class GENetworkManager;
class GEContext;
class GEWorld;
class GERenderer;
class GEClient;
class GEMemoryManager;


class GEApp
{
public:
	static GEApp* globalGameEngineInstance;
	static GEApp* GameEngine(){ return globalGameEngineInstance; }
	static GEConsole* Console(){ return globalGameEngineInstance->pConsole; }
	static GEMemoryManager* MemoryManager(){ return globalGameEngineInstance->pMemoryManager; }
	static GEWorld* World(){ return globalGameEngineInstance->pWorld; }
	static GERenderer* Renderer(){ return globalGameEngineInstance->pRenderer; }
	static GEClient* Client(){ return globalGameEngineInstance->pClient; }
	static GEContext* Context(){ return globalGameEngineInstance->pContext; }
public:
	GEApp(void);
	~GEApp(void);

	void Run();
	void Initialize();
	void PrintEngineSpecs();


	//"global" access to major parts of engine.
	inline GENetworkManager* GetNetwork()		{ return pNetStatus; }
	inline GERenderer* GetRenderer()			{ return pRenderer; }
	inline GEContext* GetContext()			{ return pContext; }
	inline GEClient* GetClient()				{ return pClient; }
	inline GEWorld* GetWorld()				{ return pWorld; }
	inline GEConsole* GetConsole()			{ return pConsole; }
	inline GEMemoryManager* GetMemoryManager() { return pMemoryManager; }


private:
	
	double appTime;

	GEConsole* pConsole;

	GEMemoryManager* pMemoryManager;

	GENetworkManager* pNetStatus;

	GERenderer* pRenderer;

	GEContext* pContext;

	GEClient* pClient;

	GEWorld* pWorld;
};

#endif