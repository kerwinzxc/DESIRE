#pragma once

#include "Engine/Core/Factory.h"
#include "Engine/Core/HashedStringMap.h"

#include <vector>

class IScript;
class ScriptComponent;
class Object;

class ScriptSystem
{
public:
	ScriptSystem();
	virtual ~ScriptSystem();

	void Update();

	void RegisterScript(HashedString scriptName, Factory<IScript>::Func_t factory);
	void CreateScriptComponentOnObject(Object& object, const char *scriptName);

	void OnScriptComponentCreated(ScriptComponent *component);
	void OnScriptComponentDestroyed(ScriptComponent *component);

private:
	virtual void CreateScriptComponentOnObject_Internal(Object& object, const char *scriptName) = 0;

	std::vector<ScriptComponent*> scriptComponents;
	HashedStringMap<Factory<IScript>::Func_t> scriptFactories;
};

#define REGISTER_NATIVE_SCRIPT(SCRIPT)	Modules::ScriptSystem->RegisterScript(HashedString(#SCRIPT), &Factory<IScript>::Create<SCRIPT>)
