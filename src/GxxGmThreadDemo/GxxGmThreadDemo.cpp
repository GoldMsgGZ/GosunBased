//////////////////////////////////////////////////////////////////////////
//
// ����Ŀ��GXX�������̡߳��̳߳ء�����ز��Թ���

#include "..\ext\Foundation\GSThread.h"
#include "..\ext\Foundation\GSThreadPool.h"
#include <iostream>

//#define _THREAD_DEMO_
#define _THREAD_POOL_DEMO_

//
// �̺߳���
void GS_CALLBACK _FunPtrThreadCallback(GSThread &thread, void *pThreadData)
{
	void *pUserData = thread.GetUserData();
	std::cout<<"�û����ݣ�"<<(const char *)pUserData<<std::endl;
	std::cout<<"�̲߳�����"<<(const char *)pThreadData<<std::endl;

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

	// ����5���׼���˳�
	Sleep(5000);
	first_thread.Stop();
	first_thread.Join();

	std::cout<<"demo is stopping..."<<std::endl;
#else
	#ifdef _THREAD_POOL_DEMO_
		GSThreadPoolGlobalInit();

		// ���̳߳ش���10���߳�

		GSThreadPoolGlobalCleanup();
	#endif
#endif
	return 0;
}