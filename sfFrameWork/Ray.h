#pragma once
#include "Collider.h"
namespace sf
{
	namespace col
	{
		//�R���C�_�[�ƏՓ˔������郌�C�N���X
		class Ray
		{
		public:
			/// <summary>
			/// ���C�̍쐬
			/// </summary>
			/// <param name="start">�J�n�n�_</param>
			/// <param name="end">�I���n�_</param>
			void CreateFromPoint(Vector3 _start, Vector3 _end);

			/// <summary>
			/// ���C�̍쐬
			/// </summary>
			/// <param name="start">�J�n�n�_</param>
			/// <param name="direction">�I���n�_</param>
			/// <param name="length">����</param>
			void CreateFromDirection(Vector3 _start, Vector3 _direction, float _length);

			bool Intersects(HitInfo& info, LayerMask layer);

			/// <summary>
			/// �����蔻�菈��
			/// </summary>
			/// <param name="other"></param>
			/// <param name="info"></param>
			/// <returns></returns>
			bool Intersect(ICollider* other, HitInfo& info)const;

			void Draw(DirectX::XMFLOAT4 color);

		private:
			DirectX::FXMVECTOR PointFXMVector()const;
			DirectX::FXMVECTOR DirFXMVector()const;

		private:
			Vector3 start;
			Vector3 direction;
			float length;
		};
	}
}