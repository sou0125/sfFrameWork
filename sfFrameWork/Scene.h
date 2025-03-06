#pragma once
#include <mutex>
#include "Actor.h"
#include "Ref.h"
#include "list"
namespace sf
{
	//�V�[�����N���X
	class IScene
	{
	public:
		IScene();
		virtual ~IScene();

	public:
		void Load();

		/// <summary>
		/// ���̃V�[�����A�N�e�B�x�[�g�ɂ���(standby�ɂ���K�v������)
		/// </summary>
		void Activate();

		/// <summary>
		/// ���̃V�[�����f�B�A�N�e�B�x�[�g�ɂ���
		/// </summary>
		void DeActivate();

		/// <summary>
		/// ���̃V�[�����X�^���o�C��Ԃ��ǂ���
		/// </summary>
		/// <returns></returns>
		virtual bool StandbyThisScene()const = 0;

		bool IsActivate()const { return activate; }

		static void DestroyScenes();

		static void DestroyFromOnApplicaitonExit();

		ref::Ref<sf::Actor> Instantiate();

		virtual void OnGUI();

	protected:
		virtual void Init() = 0;
		virtual void Loaded() = 0;

	private:
		void Destroy(const Actor* actor);

	private:
		static std::queue<const sf::IScene*> deActiveScene;
		static std::mutex deActiveMtx;

		static std::list<IScene*> scenes;

		bool activate = false;

		std::list<Actor*> actors;
		std::mutex actorsMtx;

		ref::Ref<sf::Actor> select;

		friend Actor;
	};

	//�V�[���e���v���[�g
	template<typename T>
	class Scene :public IScene
	{
	public:
		Scene()
		{
			instance = this;
		}

		virtual ~Scene()
		{
			instance = nullptr;
			standby = false;
		}

		static sf::SafePtr<Scene> SceneInstance() { return instance; }

		/// <summary>
		/// ���̃V�[����standby��Ԃ�
		/// </summary>
		/// <returns></returns>
		static bool Standby()
		{
			bool ret = false;
			{
				std::lock_guard<std::mutex> lock(standbyMtx);
				ret = standby;
			}
			return ret;
		}


		bool StandbyThisScene()const override
		{
			return standby;
		}

		/// <summary>
		/// �V�[����standby��Ԃɂ���
		/// </summary>
		/// <returns></returns>
		static T* StandbyScene()
		{
			T* ret = new T();
			sf::IScene* scene = static_cast<sf::IScene*>(ret);
			scene->Load();
			return ret;
		}

	protected:
		void Loaded()override
		{
			std::lock_guard<std::mutex> lock(standbyMtx);
			standby = true;
		}

	private:
		static bool standby;

		static Scene* instance;

		static std::mutex standbyMtx;
	};

	template<typename T>
	bool Scene<T>::standby = false;

	template<typename T>
	Scene<T>* Scene<T>::instance = nullptr;

	template<typename T>
	std::mutex Scene<T>::standbyMtx;
}