#pragma once
#include "Collider.h"
namespace sf
{
	namespace col
	{
		//�{�b�N�X�R���C�_�[�N���X(OBB)
		class BoxCollider :public ICollider
		{
		public:
			DirectX::BoundingBox Get()const;

			bool CheckHitCollider(ICollider* other, HitInfo& info)override;

		protected:
			void DebugDraw()override;

		private:
			std::vector<Vector3> GetVertices()const;
		};
	}
}