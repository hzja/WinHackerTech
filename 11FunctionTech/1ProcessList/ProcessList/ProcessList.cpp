#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>

int main(){
	PROCESSENTRY32 pe = {0};
	pe.dwSize = sizeof(PROCESSENTRY32);

	//获取全部进程
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(INVALID_HANDLE_VALUE==hProcessSnap){
		printf("CreateToolhelp32Snapshot()函数调用出现错误");
		return 0;
	}

	printf("读取系统中的进程信息--------------------------------------------------------------------------\n");

	//获取系统快照中的第一个进程信息;
	BOOL bRet = ::Process32First(hProcessSnap, &pe);
	while (bRet)
	{
		//显示结构大小
		printf("进程大小:%d\t", pe.dwSize);
		//显示进程ID
		printf("进程ID:%d\t", pe.th32ProcessID);
		//显示进程名称
		printf("进程名称:%S\n", &pe.szExeFile);
		//获取下一个进程信息
		bRet = ::Process32Next(hProcessSnap, &pe);
	}

	//关闭句柄
	::CloseHandle(hProcessSnap);
	//使得系统暂停100秒
	Sleep(100000);
	return 0;
}

