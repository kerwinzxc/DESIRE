#pragma once

#include "Engine/Physics/Collision.h"

#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include <vector>

class PhysicsComponent;

class RaycastCallbackBase : public b2RayCastCallback
{
protected:
	RaycastCallbackBase(int layerMask)
		: layerMask(layerMask)
	{

	}

	bool IsFilteredOut(const b2Fixture *fixture) const
	{
		const b2Filter& filterData = fixture->GetFilterData();
		return (filterData.categoryBits & layerMask) == 0;
	}

	int layerMask;
};

class RaycastClosestCallback : public RaycastCallbackBase
{
public:
	RaycastClosestCallback(int layerMask)
		: RaycastCallbackBase(layerMask)
	{

	}

	float32 ReportFixture(b2Fixture *fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
	{
		if(IsFilteredOut(fixture))
		{
			return -1;		// Filter out the fixture
		}

		collision = Collision(static_cast<PhysicsComponent*>(fixture->GetUserData()), Vector3(point.x, point.y, 0.0f), Vector3(normal.x, normal.y, 0.0f));
		return fraction;	// The ray will be clipped to the current intersection point
	}

	Collision collision;
};

class RaycastAnyCallback : public RaycastCallbackBase
{
public:
	RaycastAnyCallback(int layerMask)
		: RaycastCallbackBase(layerMask)
	{
	
	}

	float32 ReportFixture(b2Fixture *fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
	{
		if(IsFilteredOut(fixture))
		{
			return -1;		// Filter out the fixture
		}

		hasHit = true;
		return 0.0f;		// The raycast should be terminated
	}

	bool hasHit = false;
};

class RaycastAllCallback : public RaycastCallbackBase
{
public:
	RaycastAllCallback(int layerMask)
		: RaycastCallbackBase(layerMask)
	{

	}

	float32 ReportFixture(b2Fixture *fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override
	{
		if(IsFilteredOut(fixture))
		{
			return -1;		// Filter out the fixture
		}

		PhysicsComponent *component = static_cast<PhysicsComponent*>(fixture->GetUserData());
		collisions.emplace_back(component, Vector3(point.x, point.y, 0.0f), Vector3(normal.x, normal.y, 0.0f));
		return 1.0f;		// The raycast should continue as if no hit occurred
	}

	std::vector<Collision> collisions;
};
