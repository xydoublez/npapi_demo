#pragma once
#include "stdafx.h"

//Interface
extern NPClass sNPClass;

//
// function signatures for scripting
//

NPObject* scriptableAllocate(NPP npp, NPClass* aClass);
void scriptableDeallocate(NPObject* npobj);
void scriptableInvalidate(NPObject* npobj);
bool scriptableHasMethod(NPObject* npobj, NPIdentifier name);
bool scriptableInvoke(NPObject* npobj, NPIdentifier name, const NPVariant* args, uint32_t argCount, NPVariant* result);
bool scriptableInvokeDefault(NPObject* npobj, const NPVariant* args, uint32_t argCount, NPVariant* result);
bool scriptableHasProperty(NPObject* npobj, NPIdentifier name);
bool scriptableGetProperty(NPObject* npobj, NPIdentifier name, NPVariant* result);
bool scriptableSetProperty(NPObject* npobj, NPIdentifier name, const NPVariant* value);
bool scriptableRemoveProperty(NPObject* npobj, NPIdentifier name);
bool scriptableEnumerate(NPObject* npobj, NPIdentifier** identifier, uint32_t* count);
bool scriptableConstruct(NPObject* npobj, const NPVariant* args, uint32_t argCount, NPVariant* result);

extern NPIdentifier npidUpdate;

extern char szBuffer[500];

extern void InitializeScriptObject();
