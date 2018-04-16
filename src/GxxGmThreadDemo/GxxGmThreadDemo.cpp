//////////////////////////////////////////////////////////////////////////
//
// 本项目是GXX基础库线程、线程池、任务池测试工程

#include "..\ext\Foundation\GSThread.h"
#include "..\ext\Foundation\GSThreadPool.h"
#include <iostream>

//#define _THREAD_DEMO_
#define _THREAD_POOL_DEMO_

//
// 线程函数
void GS_CALLBACK _FunPtrThreadCallback(GSThread &thread, void *pThreadData)
{
	void *pUserData = thread.GetUserData();
	std::cout<<"用户数据："<<(const char *)pUserData<<std::endl;
	std::cout<<"线程参数："<<(const char *)pThreadData<<std::endl;

	while (true)
	{
		if (thread.TestExit())
			break;

		std::cout<<"running..."<<std::endl;
		Sleep(1000);
	}

	std::cout<<"stopping..."<<std::endl;
	return ;
}

int main(int argc, const char *argv[])
{
#ifdef _THREAD_DEMO_
	GSThread first_thread;
	first_thread.SetUserData("this is a user data...");
	first_thread.Start(_FunPtrThreadCallback, "thread data...");

	// 运行5秒后，准备退出
	Sleep(5000);
	first_thread.Stop();
	first_thread.Join();

	std::cout<<"demo is stopping..."<<std::endl;
#else
	#ifdef _THREAD_POOL_DEMO_
		GSThreadPoolGlobalInit();

		// 在线程池创建10个线程

		GSThreadPoolGlobalCleanup();
	#endif
#endif
	return 0;
}