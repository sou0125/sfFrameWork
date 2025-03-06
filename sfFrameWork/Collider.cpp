#include "Collider.h"

std::vector<sf::ref::Ref<sf::col::ICollider>> sf::col::ICollider::cols;
std::mutex sf::col::ICollider::mtx;
std::mutex sf::col::ICollider::deleteMtx;
std::vector<sf::ref::Ref<sf::col::ICollider>> sf::col::ICollider::deleteCols;

sf::col::ICollider::ICollider()
{
	{
		//std::lock_guard<std::mutex> guard(mtx);
		//cols.push_back(this);
	}
}

sf::col::ICollider::~ICollider()
{
	{
		std::lock_guard<std::mutex> guard(deleteMtx);
		Remove();
	}
}

void sf::col::ICollider::Activate()
{
	{
		std::lock_guard<std::mutex> guard(mtx);
		cols.push_back(this);
	}
#if DrawCollider
	debugCommand.Bind(std::bind(&ICollider::DebugDraw, this));
#endif
}

void sf::col::ICollider::DeActivate()
{
	{
		std::lock_guard<std::mutex> guard(deleteMtx);
		Remove();
	}

#if DrawCollider
	debugCommand.UnBind();
#endif
}

void sf::col::ICollider::DeleteColliders()
{
	while (!deleteCols.empty())
	{
		ref::Ref<ICollider> ref = deleteCols.back();
		deleteCols.pop_back();

		auto it = std::find_if(cols.begin(), cols.end(), [ref](ref::Ref<ICollider> v)
			{
				return v == ref;
			});

		{
			std::lock_guard<std::mutex> guard(mtx);
			if (it != cols.end())
			{
				cols.erase(it);
			}
		}
	}
}

void sf::col::ICollider::Check(ICollider* other)
{
	HitInfo info;

	bool hitFg = CheckHitCollider(other, info);

	//�����蔻��̕ω��������
	if (hitFg != this->FindHitList(other))
	{
		if (call && other->call)
			if (hitFg)
			{
				this->AddHitList(other);
				other->AddHitList(this);

				info.a = this;
				info.b = other;
				this->onCollisionEnter(info);

				info.a = other;
				info.b = this;
				other->onCollisionEnter(info);
			}
			else
			{
				this->RemoveHitList(other);
				other->RemoveHitList(this);

				info.a = this;
				info.b = other;
				this->onCollisionExit(info);

				info.a = other;
				info.b = this;
				other->onCollisionExit(info);
			}
	}
}

void sf::col::ICollider::AddHitList(ICollider* other)
{
	hitList.push_back(other);
}

void sf::col::ICollider::RemoveHitList(ICollider* other)
{
	auto it = std::find(hitList.begin(), hitList.end(), other);

	if (it != hitList.end())
	{
		hitList.erase(it);
	}
}

bool sf::col::ICollider::FindHitList(ICollider* other)
{
	auto it = std::find(hitList.begin(), hitList.end(), other);

	return (it != hitList.end());
}

void sf::col::ICollider::Remove()
{
	deleteCols.push_back(this);

	for (auto& i : hitList) {
		//�A�N�^�[�����݂����
		if (i.IsValid())
			i.Target()->RemoveHitList(this);
	}
	return;
	{
		auto it = std::find(cols.begin(), cols.end(), this);

		if (it != cols.end())
		{
			cols.erase(it);
		}
	}
}

bool sf::col::dxHit::GetCollisionInfo(const BoundingSphere& sphere, const BoundingBox& box, HitInfo& hitInfo)
{
	// ���̒��S
	XMVECTOR sphereCenter = XMLoadFloat3(&sphere.Center);

	// AABB �̍ŏ��E�ő���W���v�Z
	XMVECTOR boxCenter = XMLoadFloat3(&box.Center);
	XMVECTOR boxExtents = XMLoadFloat3(&box.Extents);

	XMVECTOR boxMin = XMVectorSubtract(boxCenter, boxExtents);
	XMVECTOR boxMax = XMVectorAdd(boxCenter, boxExtents);

	// �ŋߐړ_���v�Z
	XMVECTOR closestPoint = XMVectorClamp(sphereCenter, boxMin, boxMax);

	// �ŋߐړ_�Ƌ��̒��S�̋������v�Z
	XMVECTOR delta = XMVectorSubtract(closestPoint, sphereCenter);
	float distSquared = XMVectorGetX(XMVector3LengthSq(delta));

	// �Փ˂��Ă��邩�m�F
	if (distSquared <= (sphere.Radius * sphere.Radius)) {
		// �Փ˂��Ă���ꍇ�A�ŋߐړ_���Փ˓_�ƂȂ�
		DirectX::XMFLOAT3 p = hitInfo.hitPoint;
		XMStoreFloat3(&p, closestPoint);
		hitInfo.distance = sqrtf(distSquared);

		//�␳�l�����߂�ɂ͂��̌v�Z���K�v
		hitInfo.distance = (1 - hitInfo.distance) - sphere.Radius;
		//hitInfo.distance = -hitInfo.distance + sphere.Radius;

		return true;
	}

	// �Փ˂��Ă��Ȃ��ꍇ
	hitInfo.hitPoint = Vector3(0.0f, 0.0f, 0.0f);
	hitInfo.distance = -1.0f; // �Փ˂��Ă��Ȃ��ꍇ�� -1.0f �Ƃ���

	return false;
}

bool sf::col::dxHit::GetCollisionInfo(const BoundingSphere& sphere1, const BoundingSphere& sphere2, HitInfo& hitInfo)
{
	// ���̒��S���W��ǂݍ���
	XMVECTOR center1 = XMLoadFloat3(&sphere1.Center);
	XMVECTOR center2 = XMLoadFloat3(&sphere2.Center);

	// ���S�Ԃ̃x�N�g���Ƌ������v�Z
	XMVECTOR delta = XMVectorSubtract(center2, center1);
	float distSquared = XMVectorGetX(XMVector3LengthSq(delta));

	// 2�̋��̔��a�̍��v���v�Z
	float radiusSum = sphere1.Radius + sphere2.Radius;

	// �Փ˂��Ă��邩�ǂ����̔���
	if (distSquared <= (radiusSum * radiusSum)) {
		// �Փ˂��Ă���ꍇ�A�Փ˓_�Ƌ������v�Z
		float distance = std::sqrt(distSquared);

		// �Փ˓_�̌v�Z
		XMVECTOR hitPoint = XMVectorAdd(center1, XMVectorScale(delta, sphere1.Radius / radiusSum));

		// `HitInfo` �̍X�V
		DirectX::XMFLOAT3 p = hitInfo.hitPoint;
		XMStoreFloat3(&p, hitPoint);
		hitInfo.distance = distance;

		return true;
	}

	// �Փ˂��Ă��Ȃ��ꍇ
	hitInfo.hitPoint = Vector3(0.0f, 0.0f, 0.0f);
	hitInfo.distance = -1.0f;

	return false;
}

sf::col::LayerMask::LayerMask(unsigned int masks)
{
	Set(masks);
}

void sf::col::LayerMask::Set(unsigned int masks)
{
	layer = masks;
}

bool sf::col::LayerMask::Hit(const LayerMask& other) const
{
	//�������C���[�̎��A���C���[�̉���1�r�b�g��1�Ȃ�(�����C���[�����蔻��Ȃ�)
	if (layer == other.layer)
	{
		if (layer & 0b01)
		{
			return true;
		}
	}
	//���C���[�̃r�b�g�������Ȃ�
	else if ((layer & other.layer))
	{
		return true;
	}

	return false;
}
