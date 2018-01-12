#include "stdafx.h"
#include "Script/ScriptSystem.h"
#include "Script/NativeScriptComponent.h"
#include "Scene/Object.h"

ScriptSystem::ScriptSystem()
{

}

ScriptSystem::~ScriptSystem()
{

}

void ScriptSystem::RegisterScript(HashedString scriptName, ScriptFactory_t factory)
{
	ASSERT(factory != nullptr);

	scriptFactories.Insert(scriptName, factory);
}

void ScriptSystem::CreateScriptComponentOnObject(Object& object, const char *scriptName)
{
	// Try to create as a native script 
	HashedString scriptNameHash = HashedString::CreateFromDynamicString(scriptName);
	ScriptFactory_t *scriptFactory = scriptFactories.Find(scriptNameHash);
	if(scriptFactory != nullptr)
	{
		object.AddComponent<NativeScriptComponent>((*scriptFactory)());
		return;
	}

	// Try to create from file
	CreateScriptComponentOnObject_Internal(object, scriptName);
}

void ScriptSystem::OnScriptComponentCreate(ScriptComponent *component)
{
	scriptComponents.push_back(component);
}

void ScriptSystem::OnScriptComponentDestroy(ScriptComponent *component)
{
	auto it = std::find(scriptComponents.begin(), scriptComponents.end(), component);
	if(it != scriptComponents.end())
	{
		scriptComponents.erase(it);
	}
}

void ScriptSystem::Update()
{
	for(ScriptComponent *scriptComponent : scriptComponents)
	{
		scriptComponent->CallByType(ScriptComponent::EBuiltinFuncType::UPDATE);
	}
}