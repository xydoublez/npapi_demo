#include "stdafx.h"
#include "ScriptAccess.h"
#include "ScriptObject.h"
#include "NPString.h"

#define ARRAY_LENGTH(a) (sizeof(a)/sizeof(a[0]))

extern void* NPN_MemAlloc(LPCTSTR psz);

NPIdentifier npidUpdate;
NPClass sNPClass = {0};

char szBuffer[500];


//implementing the script interface
bool Get(NPObject* npobj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	//::MessageBox( 0, "Get", "Codeproject Plugin", MB_OK );
	CNPString arg = args[0].value.stringValue;

	if( !arg.Compare("test") )
	{
		LPCTSTR pszNonce = "test";

		char *s = (char*) NPN_MemAlloc(pszNonce);

		STRINGZ_TO_NPVARIANT( s, *result);

		return true;
	}
	else if( !arg.Compare("OS_Version") )
	{
		LPCTSTR pszNonce = "OS";

		void *s = NPN_MemAlloc(pszNonce);

		STRINGZ_TO_NPVARIANT( pszNonce, *result);

		return true;
	}

#ifdef _DEBUG		
		sprintf( szBuffer, "Get %s nicht gefunden",arg );

		::MessageBox( 0, szBuffer, "Codeproject Plugin Fehler", MB_OK );
#endif

	return false;
}

typedef bool (* FP_ScriptableFunction)(NPObject* npobj, const NPVariant* args, uint32_t argCount, NPVariant* result);

static NPNetscapeFuncs* sBrowserFuncs = NULL;

bool bInit = false;

void InitializeScriptObject()
{
	if( bInit ) return;
	bInit = true;
	//::MessageBox( 0, "InitializeScriptObject()", "Codeproject Plugin", MB_OK );

	sNPClass.structVersion =  NP_CLASS_STRUCT_VERSION;
	sNPClass.allocate =       (NPAllocateFunctionPtr)scriptableAllocate;
	sNPClass.deallocate =     (NPDeallocateFunctionPtr)scriptableDeallocate;
	sNPClass.invalidate =     (NPInvalidateFunctionPtr)scriptableInvalidate;
	sNPClass.hasMethod =      (NPHasMethodFunctionPtr)scriptableHasMethod;
	sNPClass.invoke =         (NPInvokeFunctionPtr)scriptableInvoke;
	sNPClass.invokeDefault =  (NPInvokeDefaultFunctionPtr)scriptableInvokeDefault;
	sNPClass.hasProperty =    (NPHasPropertyFunctionPtr)scriptableHasProperty;
	sNPClass.getProperty =    (NPGetPropertyFunctionPtr)scriptableGetProperty;
	sNPClass.setProperty =    (NPSetPropertyFunctionPtr)scriptableSetProperty;
	sNPClass.removeProperty = (NPRemovePropertyFunctionPtr)scriptableRemoveProperty;
	sNPClass.enumerate =      (NPEnumerationFunctionPtr)scriptableEnumerate;
	sNPClass.construct =      (NPConstructFunctionPtr)scriptableConstruct;
}

//
// npruntime object functions
//

NPObject* scriptableAllocate(NPP npp, NPClass* aClass)
{
	ScriptObject* object = (ScriptObject*) NPN_MemAlloc(sizeof(ScriptObject));

	if (object)
		memset(object, 0, sizeof(ScriptObject));

	return object;
}
void scriptableDeallocate(NPObject* npobj)
{
	if( npobj->referenceCount = 0 )
		NPN_MemFree(npobj);
}
void scriptableInvalidate(NPObject* npobj)
{
}
bool scriptableHasMethod(NPObject* npobj, NPIdentifier name)
{
		char *pname = NPN_UTF8FromIdentifier(name);

		if( !strcmp( pname, "function" ) )
		{
			sprintf( szBuffer, "scriptableHasMethod() %s", pname );
			::MessageBox( 0, szBuffer, "Codeproject Plugin", MB_OK );
			return true;
		}

		return false;
}
bool scriptableInvoke(NPObject* npobj, NPIdentifier name, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
		char *pname = NPN_UTF8FromIdentifier(name);

		ScriptObject *pScript = (ScriptObject*) npobj;

		if( !strcmp( pname, "Add" ) )
		{
			return pScript->Add(args, argCount, result);
		}
#ifdef _DEBUG		
		{
			sprintf( szBuffer, "Funktion %s not found in scriptableInvoke() ? %s", pname );
			::MessageBox( 0, szBuffer, "Codeproject Plugin Fehler", MB_OK );
		}
#endif

		return false;
}
bool scriptableInvokeDefault(NPObject* npobj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return false;
}
bool scriptableHasProperty(NPObject* npobj, NPIdentifier name)
{
	char *pProp = NPN_UTF8FromIdentifier(name);

	//sprintf( szBuffer, "scriptableHasProperty() ? %s", pProp );
	//::MessageBox( 0, szBuffer, "Codeproject Plugin", MB_OK );

	if( !strcmp( "Version", pProp ) ) return true;
	
	return false;
}
bool scriptableGetProperty(NPObject* npobj, NPIdentifier name, NPVariant* result)
{
	ScriptObject *pScriptObject = (ScriptObject*) npobj;
	char *pProp = NPN_UTF8FromIdentifier(name);

	if( !strcmp( "OperatingSystem", pProp ) )
	{
		char *p = (char*) NPN_MemAlloc( pScriptObject->GetVersion() );
		STRINGZ_TO_NPVARIANT( p, *result);
		return true;
	}

#ifdef _DEBUG
	sprintf( szBuffer, "scriptableGetProperty() ? %s", pProp );
	::MessageBox( 0, szBuffer, "Codeproject Plugin Fehler", MB_OK );
#endif

	return false;
}
bool scriptableSetProperty(NPObject* npobj, NPIdentifier name, const NPVariant* value)
{
	return false;
}
bool scriptableRemoveProperty(NPObject* npobj, NPIdentifier name)
{
	return false;
}
bool scriptableEnumerate(NPObject* npobj, NPIdentifier** identifier, uint32_t* count)
{
	return false;
}
bool scriptableConstruct(NPObject* npobj, const NPVariant* args, uint32_t argCount, NPVariant* result)
{
	return false;
}

