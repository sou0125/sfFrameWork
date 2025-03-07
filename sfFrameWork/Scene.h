#pragma once
#include <mutex>
#include "Actor.h"
#include "Ref.h"
#include "list"
namespace sf
{
	//シーン基底クラス
	class IScene
	{
	public:
		IScene();
		virtual ~IScene();

	public:
		void Load();

		/// <summary>
		/// このシーンをアクティベートにする(standbyにする必要がある)
		/// </summary>
		void Activate();

		/// <summary>
		/// このシーンをディアクティベートにする
		/// </summary>
		void DeActivate();

		/// <summary>
		/// このシーンがスタンバイ状態かどうか
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

	//シーンテンプレート
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
		/// このシーンがstandby状態か
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
		/// シーンをstandby状態にする
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