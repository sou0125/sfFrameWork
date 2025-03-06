#include "SphereCollider.h"
#include "BoxCollider.h"

bool sf::col::SphereCollider::CheckHitCollider(ICollider* other, HitInfo& info)
{
	bool hitFg = false;

	if (typeid(*other) == typeid(SphereCollider))
	{
		hitFg = dxHit::GetCollisionInfo(this->Get(), static_cast<SphereCollider*>(other)->Get(), info);
	}
	else if (typeid(*other) == typeid(BoneSphereCollider))
	{
		hitFg = dxHit::GetCollisionInfo(this->Get(), static_cast<BoneSphereCollider*>(other)->Get(), info);
	}
	else if (typeid(*other) == typeid(BoxCollider))
	{
		hitFg = dxHit::GetCollisionInfo(this->Get(), static_cast<BoxCollider*>(other)->Get(), info);
	}

	return hitFg;
}

void sf::col::SphereCollider::DebugDraw()
{
	if (!call)return;

	std::vector<Vector3> v = GetVertices();

	std::vector<unsigned int> indices;

	for (int lat = 0; lat < latitudeSegments; ++lat) {
		for (int lon = 0; lon < longitudeSegments; ++lon) {
			// ���݂̒��_�C���f�b�N�X
			int current = lat * (longitudeSegments + 1) + lon;
			int next = current + 1;
			int nextLat = current + (longitudeSegments + 1);

			// �o�x�����̐� (������)
			indices.push_back(current);
			indices.push_back(next);

			// �ܓx�����̐� (������)
			if (lat < latitudeSegments - 1) {
				indices.push_back(current);
				indices.push_back(nextLat);
			}
		}
	}

	DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0, 1, 0, 1);
	if (!hitList.empty())
	{
		color = DirectX::XMFLOAT4(1, 0, 0, 1);
	}

	for (int i = 0; i < indices.size() - 1; i++)
	{
		sf::debug::Debug::DrawLine(v[indices[i]], v[indices[i + 1]], color);
		i++;
	}
}

std::vector<Vector3> sf::col::SphereCollider::GetVertices() const
{
	Vector3 center = GetCenter();

	std::vector<Vector3> vertices;

	// �ܓx�ƌo�x�̊p�x�X�e�b�v
	float latStep = DirectX::XM_PI / latitudeSegments;
	float lonStep = DirectX::XM_2PI / longitudeSegments;

	// ���̒��_�𐶐�
	for (int lat = 0; lat <= latitudeSegments; ++lat) {
		float theta = -DirectX::XM_PIDIV2 + lat * latStep; // �ܓx (-��/2 �` ��/2)
		float y = radius * sinf(theta);           // Y���W

		for (int lon = 0; lon <= longitudeSegments; ++lon) {
			float phi = lon * lonStep;            // �o�x (0 �` 2��)
			float x = radius * cosf(theta) * cosf(phi); // X���W
			float z = radius * cosf(theta) * sinf(phi); // Z���W

			// ���S���W�����Z���ă��[���h���W�ɕϊ�
			Vector3 position = {
				center.x + x,
				center.y + y,
				center.z + z
			};

			vertices.push_back({ position });
		}
	}

	return vertices;
}

Vector3 sf::col::SphereCollider::GetCenter() const
{
	return actorRef.Target()->transform.GetPosition() + offset;
}

DirectX::BoundingSphere sf::col::SphereCollider::Get() const
{
	DirectX::BoundingSphere ret;

	ret.Center = GetCenter();
	ret.Radius = radius;

	return ret;
}

void sf::col::BoneSphereCollider::SetBone(sf::motion::MotionBone* _bone)
{
	bone = _bone;
}

Vector3 sf::col::BoneSphereCollider::GetCenter() const
{
	//�A�N�^�[�̍s��
	DirectX::XMMATRIX actorMtx = actorRef.Target()->transform.Matrix();

	//�Ώۂ̃{�[���̍s��
	DirectX::XMMATRIX boneMtx = bone->GetBoneMatrix();

	//���̂̃��[���h�ϊ��s��
	DirectX::XMMATRIX worldMatrix = boneMtx * actorMtx;


	// �ʒu�ƃI�t�Z�b�g��K�p
	DirectX::XMVECTOR position
		= DirectX::XMVector3Transform(
			DirectX::XMVectorSet(offset.x, offset.y, offset.z, 1.0f),
			worldMatrix
		);

	Vector3 ret = Vector3(
		DirectX::XMVectorGetX(position),
		DirectX::XMVectorGetY(position),
		DirectX::XMVectorGetZ(position)
	);

	return ret;
}


