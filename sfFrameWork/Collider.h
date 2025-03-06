#pragma once
#include "Component.h"
#include "Delegate.h"
#include <DirectXCollision.h>

#ifdef _DEBUG
#define DrawCollider	(true)
#else
#define DrawCollider	(false)
#endif

namespace sf
{
	namespace col
	{
		const unsigned int Mask_Same = 0b1 << 0;		//���R���C�_�[�Փ˃}�X�N
		const unsigned int Mask_Pad = 0b1 << 1;			//�����C���[�h�~�p�p�f�B���O
		const unsigned int Mask_Area = 0b1 << 2;		//�G���A�}�X�N
		const unsigned int Mask_PlayerAtk = 0b1 << 3;	//�v���C���[�U���}�X�N
		const unsigned int Mask_EnemyAtk = 0b1 << 4;	//�G�U���}�X�N
		const unsigned int Mask_FieldHit = 0b1 << 5;	//�t�B�[���h�Փ˃}�X�N
		const unsigned int Mask_Assist = 0b1 << 6;		//�A�V�X�g�}�X�N

		const unsigned int Layer_Default = Mask_Same;					//�f�t�H���g
		const unsigned int Layer_PlayerHit = Mask_Area | Mask_EnemyAtk;	//�v���C���[��e
		const unsigned int Layer_EnemyHit = Mask_PlayerAtk | Mask_Pad;	//�G��e
		const unsigned int Layer_Area = Mask_Area;						//�G���A�p
		const unsigned int Layer_PlayerAtk = Mask_PlayerAtk;			//�v���C���[�U��
		const unsigned int Layer_EnemyAtk = Mask_EnemyAtk;				//�G�U��
		const unsigned int Layer_FieldHit = Mask_FieldHit | Mask_Same;	//�L�����N�^�[�����o��
		const unsigned int Layer_CharaPush = Mask_FieldHit | Mask_Same;	//�L�����N�^�[�����o��
		const unsigned int Layer_Assist = Mask_Assist;

		//���C���[�}�X�N�N���X
		class LayerMask
		{
		public:
			LayerMask() {}
			LayerMask(unsigned int masks);
			void Set(unsigned int masks);

			bool Hit(const LayerMask& other)const;

			unsigned int Get()const { return layer; }

		private:
			unsigned int layer = Layer_Default;
		};

		class ICollider;

		//�Փˏ��\����
		struct HitInfo
		{
			//���g�̃R���C�_�[
			ICollider* a = nullptr;

			//�Փˑ���̃R���C�_�[
			ICollider* b = nullptr;

			//�Փ˒n�_
			Vector3 hitPoint = Vector3::Zero;

			//����
			float distance = -1.0f;
		};

		//�����蔻����N���X
		class ICollider :public Component, public sf::ref::autoRef<ICollider>
		{
		public:
			ICollider();
			virtual ~ICollider();

			void Activate()override;
			void DeActivate()override;

			static void DeleteColliders();

			static const std::vector<sf::ref::Ref<ICollider>>& GetColliders() { return cols; }

			void Check(ICollider* other);

			virtual bool CheckHitCollider(ICollider* other, HitInfo& info) = 0;

			void AddHitList(ICollider* other);
			void RemoveHitList(ICollider* other);

			bool FindHitList(ICollider* other);

		protected:
			virtual void DebugDraw() = 0;

		private:
			void Remove();

		public:
			del::Delegate<HitInfo> onCollisionEnter;
			del::Delegate<HitInfo> onCollisionExit;

			LayerMask layer;

			bool call = true;

		protected:
			std::list<sf::ref::Ref<ICollider>> hitList;
		public:
			static std::vector<sf::ref::Ref<ICollider>> cols;
			static std::mutex mtx;
			static std::mutex deleteMtx;

		private:
			command::Command<> debugCommand;

		private:
			static std::vector<sf::ref::Ref<ICollider>> deleteCols;
		};

		namespace dxHit
		{
			using namespace DirectX;

			bool GetCollisionInfo(const BoundingSphere& sphere, const BoundingBox& box, HitInfo& hitInfo);

			bool GetCollisionInfo(const BoundingSphere& sphere1, const BoundingSphere& sphere2, HitInfo& hitInfo);
		}
	}
}