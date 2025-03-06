#pragma once
template<typename T>
class Singleton
{
public:
	static void Init()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}
	}

	static void UnInit()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	static T* Instance() { return instance; }

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

protected:
	Singleton() {}
	virtual ~Singleton() {}

private:
	static T* instance;
};

template<typename T>
T* Singleton<T>::instance = nullptr;

namespace sf
{
	//�P��̃R���|�[�l���g���擾�ł���N���X(�V���O���g���ł͂Ȃ��A�ȈՓI�ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃N���X)
	template<typename T>
	class SingleComponent
	{
	public:
		SingleComponent()
		{
			instance = static_cast<T*>(this);
		}

		virtual ~SingleComponent()
		{
			instance = nullptr;
		}

		static T* Instance() { return instance; }

		SingleComponent(const SingleComponent&) = delete;
		SingleComponent& operator=(const SingleComponent&) = delete;
		SingleComponent(SingleComponent&&) = delete;
		SingleComponent& operator=(SingleComponent&&) = delete;

	private:
		static T* instance;
	};

	template<typename T>
	T* SingleComponent<T>::instance = nullptr;
}