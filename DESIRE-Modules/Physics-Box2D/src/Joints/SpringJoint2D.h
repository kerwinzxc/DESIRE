#pragma once

#include "Joints/AnchoredJoint2D.h"

#include "Box2D/Dynamics/Joints/b2DistanceJoint.h"

class SpringJoint2D : public AnchoredJoint2D
{
public:
	SpringJoint2D();
	~SpringJoint2D() override;

	float GetDampingRatio() const;
	void SetDampingRatio(float value);

	float GetFrequency() const;
	void SetFrequency(float value);

	float GetDistance() const;
	void SetDistance(float value);

	void OnJointDestroyed() override;

private:
	b2Joint* CreateJoint() override;

	b2Joint* GetJoint() const override;
	b2JointDef& GetJointDef() override;
	const b2JointDef& GetJointDef() const override;

	b2DistanceJointDef jointDef;
	b2DistanceJoint *joint = nullptr;
};
