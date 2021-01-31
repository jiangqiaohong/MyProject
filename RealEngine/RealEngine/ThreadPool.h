#pragma once
#include <functional>
#include <Thread>
#include <vector>

namespace RealEngine
{
	class ThreadPool 
	{
	public:
		ThreadPool();
		~ThreadPool();

		void addThreadTask(std::function<void()> func);

	private:
		// ������亯��
		void threadAllocator();
		void nextTask();

		// �߳�
		std::vector<std::thread> threads;
		// �߳�����
		std::vector<std::function<void()>> tasks;
	};
}