#include "stdafx.h"
#include "ScriptObject.h"


ScriptObject::ScriptObject(NPP npp, NPClass* pClass) : mInstance(npp)
{
	_class = pClass;
	referenceCount = 0;
}

ScriptObject::~ScriptObject()
{
}

NPBool ScriptObject::init(NPWindow* aWindow)
{
	return true;
}
void ScriptObject::shut()
{
}
NPBool ScriptObject::isInitialized()
{
	return true;
}
//properties
char* ScriptObject::GetVersion()
{
	return "Version 1.0";
}

//implementing the methods
bool ScriptObject::Add(const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return true;
}