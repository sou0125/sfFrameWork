#pragma once

#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <functional>
#include <condition_variable>
#include <atomic>

namespace sf
{
	namespace jobsystem
	{
		class JobSystem {
		public:
			/// <summary>
			/// �W���u�V�X�e���̏�����
			/// </summary>
			/// <param name="_throwJob">�W���u���ŗ�O���X���[���ꂽ���̃R�[���o�b�N�֐�</param>
			/// <param name="numThreads">�K�v�X���b�h��</param>
			JobSystem(std::function<void(const std::exception& hoge)> _throwJob, size_t numThreads);
			JobSystem(std::function<void(const std::exception& hoge)> _throwJob);
			JobSystem(size_t numThreads);
			JobSystem();
			~JobSystem();

			/// <summary>
			/// �W���u�̒ǉ�
			/// </summary>
			/// <param name="job">�W���u</param>
			void addJob(std::function<void()> job);

			/// <summary>
			/// �S�ẴW���u�����������̂�҂�
			/// </summary>
			void waitForAllJobs();

			/// <summary>
			/// �S�ẴW���u������������
			/// </summary>
			/// <returns></returns>
			bool EndAllJobs();

		private:
			void Constructor(size_t numThreads);

		private:
			std::function<void(const std::exception& hoge)> throwJob = [](const std::exception&) {};
			
			//���[�J�[�X���b�h
			std::vector<std::thread> workers;

			//�W���u�L���[
			std::queue<std::function<void()>> jobQueue;

			//�W���u�L���[�̕ی�p�~���[�e�b�N�X
			std::mutex queueMutex;

			//�X���b�h�����p
			std::condition_variable condition;

			//�S�W���u�����p
			std::condition_variable allJobsDone;

			//�X���b�h��~�t���O
			std::atomic<bool> stopFlag;

			//���ݎ��s���̃W���u��
			int activeJobs = 0;
		};
	}
}