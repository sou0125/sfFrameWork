#include "Component.h"
#include "sf.h"

bool sf::Component::IsValid() const
{
	return actorRef.IsValid();
}

void sf::Component::Set(const Actor* other)
{
	actorRef = other;
}

DirectX::XMVECTOR sf::Component::WorldVector(float x, float y, float z) const
{
	// ��]�s����\�z
	DirectX::XMMATRIX rotationMatrix = actorRef.Target()->transform.GetRotationMatrix();

	// ������x�N�g�����v�Z
	DirectX::XMVECTOR upVector = DirectX::XMVectorSet(x, y, z, 0.0f); // ���[���h��Ԃł̏����
	upVector = DirectX::XMVector3TransformNormal(upVector, rotationMatrix); // ��]�s���K�p

	return upVector;
}

Vector3 sf::Component::LookAt(Vector3 target) const
{
	Vector3 p = actorRef.Target()->transform.GetPosition();
	float dirX = target.x - p.x;
	float dirY = target.y - p.y;
	float dirZ = target.z - p.z;

	// �����x�N�g���̒������v�Z (�K�v�Ȃ琳�K��)
	double length = std::sqrt(dirX * dirX + dirY * dirY + dirZ * dirZ);

	// �s�b�` (�㉺��])
	double pitch = std::atan2(dirY, std::sqrt(dirX * dirX + dirZ * dirZ));

	// ���[ (������])
	double yaw = std::atan2(dirX, dirZ);

	return Vector3(DirectX::XMConvertToDegrees(-pitch), DirectX::XMConvertToDegrees(yaw), 0.0f);
}
