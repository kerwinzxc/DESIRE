#pragma once

#include "Engine/Script/ScriptSystem.h"

class AngelScriptStringFactory;
class String;
class asIScriptEngine;
class asIScriptModule;
class asIScriptContext;
class asIScriptFunction;
struct asSMessageInfo;

class AngelScriptSystem : public ScriptSystem
{
public:
	AngelScriptSystem();
	~AngelScriptSystem() override;

private:
	void CreateScriptComponentOnObject_Internal(Object& object, const char *scriptName) override;

	static asIScriptModule* CompileScript(const char *scriptName, asIScriptEngine *engine);
	asIScriptContext* CreateScriptContext();

	bool IsBreakpoint(const char *scriptSection, int line, asIScriptFunction *function) const;

	// Callbacks
	static void PrintCallback(const String& message);
	static void MessageCallback(const asSMessageInfo *msg, void *thisPtr);
	static asIScriptContext* RequestContextCallback(asIScriptEngine *engine, void *thisPtr);
	static void ReturnContextCallback(asIScriptEngine *engine, asIScriptContext *ctx, void *thisPtr);
	void ExceptionCallback(asIScriptContext *ctx);
	void LineCallback(asIScriptContext *ctx);		// The line callback function is called by the VM for each statement that is executed

	asIScriptEngine *engine = nullptr;
	std::vector<asIScriptContext*> contextPool;
	std::unique_ptr<AngelScriptStringFactory> stringFactory;
};
