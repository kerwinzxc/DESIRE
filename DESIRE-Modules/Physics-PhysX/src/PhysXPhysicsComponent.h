#pragma once

#include "Engine/Component/PhysicsComponent.h"

namespace physx
{
	class PxRigidBody;
	class PxRigidDynamic;
}

class PhysXPhysicsComponent : public PhysicsComponent
{
public:
	PhysXPhysicsComponent(Object& object);
	~PhysXPhysicsComponent();

	// Collision
	void SetCollisionLayer(EPhysicsCollisionLayer collisionLayer) override;

	void SetCollisionDetectionMode(ECollisionDetectionMode mode) override;
	ECollisionDetectionMode GetCollisionDetectionMode() const override;

	std::vector<PhysicsComponent*> GetActiveCollidingComponents() const override;

	void SetBodyType(EBodyType bodyType);
	EBodyType GetBodyType() const;

	void SetTrigger(bool value) override;
	bool IsTrigger() const override;

	// Mass manipulation
	void SetMass(float mass) override;
	float GetMass() const override;
	Vector3 GetCenterOfMass() const override;

	// Damping
	void SetLinearDamping(float value) override;
	float GetLinearDamping() const override;
	void SetAngularDamping(float value) override;
	float GetAngularDamping() const override;

	// Velocity
	void SetLinearVelocity(const Vector3& linearVelocity) override;
	Vector3 GetLinearVelocity() const override;
	void SetAngularVelocity(const Vector3& angularVelocity) override;
	Vector3 GetAngularVelocity() const override;

	// Forces
	void AddForce(const Vector3& force, EForceMode mode) override;
	void AddForceAtPosition(const Vector3& force, const Vector3& position, EForceMode mode) override;
	void AddTorque(const Vector3& torque, EForceMode mode) override;

	bool IsSleeping() const override;

	void UpdateGameObjectTransform() const override;
	void SetTransformFromGameObject() override;

	void SetEnabled(bool value) override;

private:
	physx::PxRigidBody *body = nullptr;
	physx::PxRigidDynamic *dynamicBody = nullptr;
};
