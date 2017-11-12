#include "stdafx.h"
#include "Scene/Transform.h"

Transform::Transform()
	: position(0.0f)
	, rotation(0.0f, 0.0f, 0.0f, 1.0f)
	, scale(1.0f)
	, worldMatrix(Matrix4::Identity())
	, parentWorldMatrix(nullptr)
	, owner(nullptr)
	, flags(IS_IDENTITY)
{

}

Transform::~Transform()
{

}

void Transform::SetParent(const Transform *parent)
{
	parentWorldMatrix = (parent != nullptr) ? &parent->worldMatrix : nullptr;
	flags |= WORLD_MATRIX_DIRTY;
}

void Transform::ResetToIdentity()
{
	position = Vector3(0.0f);
	rotation = Quat(0.0f, 0.0f, 0.0f, 1.0f);
	scale = Vector3(1.0f);
	flags = IS_IDENTITY | POSITION_CHANGED | ROTATION_CHANGED | SCALE_CHANGED;
}

void Transform::SetPosition(const Vector3& newPosition)
{
	position = newPosition;
	flags |= POSITION_CHANGED;
	flags &= ~IS_IDENTITY;
}

void Transform::SetRotation(const Quat& newRotation)
{
	rotation = newRotation;
	flags |= ROTATION_CHANGED;
	flags &= ~IS_IDENTITY;
}

void Transform::SetScale(const Vector3& newScale)
{
	scale = newScale;
	flags |= SCALE_CHANGED;
	flags &= ~IS_IDENTITY;
}

uint8_t Transform::GetFlags() const
{
	return flags;
}

Matrix4 Transform::ConstructLocalMatrix() const
{
	Matrix4 mat = Matrix4(rotation, position);
	mat.AppendScale(scale);
	return mat;
}

const Matrix4& Transform::GetWorldMatrix() const
{
	return worldMatrix;
}

Vector3 Transform::GetWorldPosition() const
{
	return worldMatrix.GetTranslation();
}

void Transform::UpdateWorldMatrix()
{
	if(flags & IS_IDENTITY)
	{
		if(parentWorldMatrix != nullptr)
		{
			worldMatrix = *parentWorldMatrix;
		}
		else
		{
			worldMatrix = Matrix4::Identity();
		}
	}
	else
	{
		worldMatrix = ConstructLocalMatrix();

		if(parentWorldMatrix != nullptr)
		{
			worldMatrix *= *parentWorldMatrix;
		}
	}

	flags &= ~WORLD_MATRIX_DIRTY;
}
