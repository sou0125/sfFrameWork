#pragma once
#include "Debug.h"

namespace sf
{
	//Nullptr�������Ō��o���邱�Ƃ��o����A���|�C���^�̑�փN���X
	template<typename T>
	class SafePtr
	{
	public:
		SafePtr() : ptr(nullptr) {}
		SafePtr(T* p) : ptr(p) {}

		SafePtr(const SafePtr& other) : ptr(other.ptr) {}

		//SafePtr�Ƃ̑�����Z�q
		SafePtr& operator=(const SafePtr& other)
		{
			ptr = other.Get();
			return *this;
		}

		//�p���֌W�̂���SafePtr�̏���������
		template<typename U>
		SafePtr(const SafePtr<U>& other) : ptr(other.Get()) {}

		//�p���֌W�̂���SafePtr���m�̑�����Z�q
		template<typename U>
		SafePtr& operator=(const SafePtr<U>& other)
		{
			ptr = other.Get();
			return *this;
		}

		//�p���֌W�̂���SafePtr��U�փL���X�g����֐�
		template<typename U>
		U* Cast()const
		{
			if (ptr == nullptr)
			{
				return nullptr;
			}

			return static_cast<U*>(ptr);
		}

		//�|�C���^�ւ̃A�N�Z�X(null�`�F�b�N)
		T* operator->() const
		{
			if (ptr == nullptr)
			{
				debug::Debug::LogError("Nullptr�����o���܂���");
				throw std::out_of_range("�͈͊O�G���[");
			}
			return ptr;
		}

		//�Q�Ƃւ̃A�N�Z�X(null�`�F�b�N)
		T& operator*() const
		{
			if (ptr == nullptr)
			{
				debug::Debug::LogError("Nullptr�����o���܂���");
				throw std::out_of_range("�͈͊O�G���[");

				static T t{};
				return t;
			}

			return *ptr;
		}

		//���|�C���^��r
		bool operator==(const SafePtr& other)const
		{
			return this->Get() == other.Get();
		}

		//null���ǂ���
		bool isNull() const { return ptr == nullptr; }

		~SafePtr() {}

		//�|�C���^�̎擾
		T* Get()const { return ptr; }

	private:
		//�|�C���^�̎���
		T* ptr = nullptr;
	};
}
