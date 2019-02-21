//kk: thats is really my sample class
#pragma once

class ScriptObject : public NPObject //to be scriptable
{
public:
	ScriptObject(NPP npp, NPClass* pClass);
	~ScriptObject();
	//interface inheritance
	NPBool init(NPWindow* aWindow);
	void shut();
	NPBool isInitialized();

private:
	NPP mInstance;

public:
	//Methods
	bool Add(const NPVariant* args, uint32_t argCount, NPVariant* result);
	//property
	char* GetVersion();
};
