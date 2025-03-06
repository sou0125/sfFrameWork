#pragma once
#include <map>
#include <vector>
#include <mutex>
#include "Actor.h"
#include "Ref.h"
#include "Debug.h"

/*
�Z�R���|�[�l���g�̐���
�E�I�[�o�[���C�h�ł���C�x���g�֐��́A�uBegin�v�uActivate�v�uDeActivate�v��3��ނ���܂��B
	�E�uBegin�v:�R���|�[�l���g���������ꂽ�^�C�~���O�ŌĂ΂�܂��B
				�K��AddComponent�Ɠ����X���b�h�ŌĂяo����܂��B

	�E�uActivate�v
		�EScene��Init�֐����ŃR���|�[�l���g���������ꂽ�ꍇ
					���̊֐���Scene��Activate���ɌĂ΂�܂��B
					���̎��AScene��Activate�Ɠ����X���b�h�ŌĂяo����܂��B

		�E���I�ɃR���|�[�l���g��ǉ������ꍇ
					���̊֐���Begin�̒���ɌĂ΂�܂��B
					���̎��AAddComponent�Ɠ����X���b�h�ŌĂяo����܂��B

	�E�uDeActivate�v:�A�N�^�[���폜���ꂽ���ɌĂяo����܂��B
					 �S�R�}���h�����s���ꂽ��ɁA�K�����C���X���b�h����Ăяo����܂��B


�ȒP�ɐ�������ƁA
	Begin�E�E�EUnity��Awake�֐�
	Activate�E�E�EUnity��Start�֐�
	DeActivate�E�E�EUnity��OnDestroy�֐�

	�������A��{�I��Begin���g�p

�EUpdate�֐��ɂ���
	�EComponent�ɂ�Update�֐�������܂���BCommand�Ƃ����V�X�e�����g�p���܂��B

		Command�������o�ϐ��Ƃ��Ē�`
		��
		Bind�֐��Ŗ��t���[����������֐���o�^
		��
		����Ŗ��t���[���֐����Ăяo���܂�
		Command�͓����E�F�C�g�̏ꍇ�A�}���`�X���b�h�œ����ɌĂяo����܂�
		�ݒ�ł���E�F�C�g��0�`7�ł��B(�f�t�H���g��1)
*/


namespace sf
{
	//�R���|�[�l���g���N���X
	class Component
	{
	public:
		virtual ~Component() {}

		/// <summary>
		/// (�C�x���g�֐�)�ǂݍ��ݎ��ɌĂяo�����
		/// </summary>
		virtual void Begin() {}

		/// <summary>
		/// (�C�x���g�֐�)�R���|�[�l���g���A�N�e�B�x�[�g��ԂɂȂ鎞�ɌĂ΂��
		/// </summary>
		virtual void Activate(){}

		/// <summary>
		/// (�C�x���g�֐�)�R���|�[�l���g���f�B�A�N�e�B�x�[�g��ԂɂȂ鎞�ɌĂ΂��
		/// </summary>
		virtual void DeActivate(){}

		/// <summary>
		/// �R���|�[�l���g���t������A�N�^�[�����݂��Ă��邩�ǂ���
		/// </summary>
		/// <returns></returns>
		bool IsValid()const;

		/// <summary>
		/// �A�N�^�[�̃Z�b�g
		/// </summary>
		/// <param name="other"></param>
		void Set(const Actor* other);

		/// <summary>
		/// ���ʕ����x�N�g��
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="z"></param>
		/// <returns></returns>
		DirectX::XMVECTOR WorldVector(float x, float y, float z) const;

		/// <summary>
		/// Target�������������̊p�x
		/// </summary>
		/// <param name="target"></param>
		/// <returns></returns>
		Vector3 LookAt(Vector3 target)const;

	public:
		//���̃R���|�[�l���g���t������A�N�^�[�Q��
		ref::Ref<Actor> actorRef;
	};
}