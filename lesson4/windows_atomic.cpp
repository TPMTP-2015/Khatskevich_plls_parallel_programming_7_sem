// atomic_operations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <intrin.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <thread>
#include <windows.h>
#include <winbase.h>
#include <process.h>

typedef unsigned long mytype;
HANDLE ghMutex;
CRITICAL_SECTION gCS;
LPCRITICAL_SECTION sampleCriticalSection = &gCS;

static void * func_add(mytype *arg){
	volatile mytype *p = (mytype *)arg;
	for (int i = 0; i < 100000000; i++){
		(*p)++;
	}
	return 0;
}

static void * func_sub(mytype *arg){
	volatile mytype *p = (mytype *)arg;
	for (int i = 0; i < 100000000; i++){
		(*p)--;
	}
	return 0;
}

static void * func_add_handle(mytype *arg){
	volatile mytype *p = (mytype *)arg;
	for (int i = 0; i < 100000000; i++){
		WaitForSingleObject(ghMutex, INFINITE);
		(*p)++;
		ReleaseMutex(ghMutex);
	}
	return 0;
}

static void * func_sub_handle(mytype *arg){
	volatile mytype *p = (mytype *)arg;
	for (int i = 0; i < 100000000; i++){
		WaitForSingleObject(ghMutex, INFINITE);
		(*p)--;
		ReleaseMutex(ghMutex);
	}
	return 0;
}
static void * func_add_crit_sect(mytype *arg){
	volatile mytype *p = (mytype *)arg;
	for (int i = 0; i < 100000000; i++){
		EnterCriticalSection(sampleCriticalSection);
		(*p)++;
		LeaveCriticalSection(sampleCriticalSection);
	}
	return 0;
}

static void * func_sub_crit_sect(mytype *arg){
	volatile mytype *p = (mytype *)arg;
	for (int i = 0; i < 100000000; i++){
		EnterCriticalSection(sampleCriticalSection);
		(*p)--;
		LeaveCriticalSection(sampleCriticalSection);
	}
	return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	mytype tmp = 0;
	long long time_start = __rdtsc();

	
	///* critical section
	InitializeCriticalSection(sampleCriticalSection);
	std::thread thread_add(func_add_crit_sect, &tmp);
	std::thread thread_sub(func_sub_crit_sect, &tmp);
	//*/
	/* handle mutex
	ghMutex = CreateMutex(NULL, FALSE, NULL);
	std::thread thread_add(func_add_handle, &tmp);
	std::thread thread_sub(func_sub_handle, &tmp);
	*/

	/* simple volotile ( non atomic )
	std::thread thread_add(func_add, &tmp);
	std::thread thread_sub(func_sub, &tmp);
	*/

	thread_add.join();
	thread_sub.join();
	DeleteCriticalSection(sampleCriticalSection);
	printf("time = %lld   result = %lld\n", __rdtsc() - time_start, (long long int) tmp);
	Sleep(1005000);
	return 0;
}

