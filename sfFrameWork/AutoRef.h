#pragma once
#include <cstdint>
#include <map>
#include <source_location>
#include <stdexcept>
#include <string>
#include <mutex>
namespace sf
{
	namespace ref
	{
		//�ԐڎQ�Ɗ��N���X
		class IautoRef
		{
		public:
			IautoRef();

			/// <summary>
			/// ���t�@�����X�̎擾
			/// </summary>
			/// <returns></returns>
			const uintptr_t& GetRef()const { return ref; }

		private:
			const uintptr_t ref;
		};

		template<typename T>class Ref;

		//�ԐڎQ�ƃN���X
		template<typename T>
		//�ԐڎQ�ƃN���X
		class autoRef :public IautoRef
		{
		public:
			autoRef()
			{
				std::lock_guard<std::mutex> lock(mtx);
				maps[GetRef()] = static_cast<T*>(this);
			}

			virtual ~autoRef()
			{
				std::lock_guard<std::mutex> lock(mtx);
				maps.erase(maps.find(GetRef()));
			}

		private:
			static std::map<uintptr_t, T*> maps;
			static std::mutex mtx;

			friend Ref<T>;
		};

		template<typename T>
		std::map<uintptr_t, T*> autoRef<T>::maps;

		template<typename T>
		std::mutex autoRef<T>::mtx;

		//�ԐڎQ�Ǝ擾�N���X
		template<typename T>
		//�ԐڎQ�Ǝ擾�N���X
		class Ref
		{
		public:
			Ref() {}
			Ref(const Ref& other)
			{
				ref = other.ref;
			}
			Ref(const autoRef<T>* other)
			{
				if (other != nullptr)
					ref = other->GetRef();
			}
			Ref(const autoRef<T>& other)
			{
				ref = other.GetRef();
			}

		public:
			void operator=(const autoRef<T>* other)
			{
				if (other == nullptr)
					ref = 0;
				else
					ref = other->GetRef();
			}

			bool operator==(const Ref<T>& other)
			{
				return ref == other.ref;
			}
			bool operator==(T* other)
			{
				return ref == other->GetRef();
			}

			/// <summary>
			/// �C���X�^���X�̎擾
			/// </summary>
			/// <returns></returns>
			T* Target(const std::source_location location = std::source_location::current())const
			{
#ifndef _DEBUG
				return autoRef<T>::maps[ref];
#else
				{
					std::lock_guard<std::mutex> lock(autoRef<T>::mtx);
					auto it = autoRef<T>::maps.find(ref);

					if (it != autoRef<T>::maps.end())
					{
						return it->second;
					}
				}
				throw std::runtime_error(
					"�@�@�@�@�@�@�@�@�@�@�@ ���݂��Ȃ�Ref�Ƀ^�[�Q�b�g���܂���[" + std::to_string(ref) + "]\n" +
					"�@�@�@�@�@�@�@�@�@�@�@ " + location.function_name() + "�@Line:" + std::to_string(location.line())
				);
				return nullptr;
#endif
			}

			/// <summary>
			/// �Q�Ɛ�̃C���X�^���X�����݂��邩
			/// </summary>
			/// <returns></returns>
			bool IsValid()const
			{
				bool ret = false;

				{
					std::lock_guard<std::mutex> lock(autoRef<T>::mtx);
					ret = (autoRef<T>::maps.find(ref) != autoRef<T>::maps.end());
				}

				return ret;
			}

			/// <summary>
			/// �Q�Ɛ悪Null���ǂ���
			/// </summary>
			/// <returns></returns>
			bool IsNull()const { return ref == 0; }

			/// <summary>
			/// �Q�Ɛ��Null�ɂ���
			/// </summary>
			void SetNull() { ref = 0; }

		private:
			uintptr_t ref;
		};
	}
}