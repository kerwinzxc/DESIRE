#pragma once

#include "Box2D/Dynamics/b2WorldCallbacks.h"

class Collision;

class ContactListener : public b2ContactListener
{
public:
	ContactListener();
	~ContactListener() override;

	void BeginContact(b2Contact *contact) override;
	void EndContact(b2Contact *contact) override;

	void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
	void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;

private:
	static void FillCollisionFromContact(Collision& collision, const b2Contact *contact);
};
