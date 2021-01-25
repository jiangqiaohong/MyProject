#pragma once
#include "IRuntimeModule.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

namespace RealEngine 
{
	class OpenglManager :public IRuntimeModule
	{
	public:
		virtual int Initialize() {};
		virtual void Finalize() {};
		virtual void Tick() {};

		static OpenglManager& getInstance()
		{
			static OpenglManager s_sInstance;
			return s_sInstance;
		}

		// ��������
		int createWindow(int width, int height, const char* winName);
	private:
		// ���ڴ�С�����ص�
		static void onFrameBufferSizeCallback(GLFWwindow* window, int width, int height);
		// ���̻ص�
		static void onKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		// ���ص�
		static void onMouseCallback(GLFWwindow* window, int button, int action, int mods);
		// ָ��λ�ûص�
		static void onCursorCallback(GLFWwindow* window, double x, double y);
		//���ֻص�
		static void onScrollCallback(GLFWwindow* window, double x, double y);

		// ���ڹرյĻص�
		static void onCloseCallback(GLFWwindow* window);
	private:
		GLFWwindow* pWindows;
		int width;
		int height;
	};
}
