#pragma once
#include <functional>
#include <Thread>
#include <vector>
#include <queue>

// �߳���
#include <mutex>
#include <condition_variable>
#include <utility>

namespace RealEngine
{
	class ThreadPool 
	{
	public:
		ThreadPool();
		~ThreadPool();

		void addThreadTask(std::function<void()> func);
		void start();
		void stop();
	private:
		// ������亯��
		void onThreadAllocator();
		std::function<void()> nextTask();

		// �߳�
		std::vector<std::thread*> _threads;
		// �߳�����
		std::queue<std::function<void()>> _tasks;

		bool b_started;

		// ������
		std::mutex m_mtx;
		// ��������
		std::condition_variable m_cv;
	};
}