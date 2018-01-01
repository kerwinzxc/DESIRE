#include "stdafx.h"
#include "Component/Component.h"
#include "Scene/Object.h"

Component::Component(Object& object)
	: object(object)
{

}

Component::~Component()
{
	// Remove from object
	auto it = std::find(object.components.begin(), object.components.end(), this);
	if(it != object.components.end())
	{
		object.components.erase(it);
	}
}

void Component::OnGUI()
{

}

void Component::AddToObject()
{
	ASSERT(object.GetComponentByTypeID(GetTypeID()) == nullptr);
	object.components.push_back(this);
}
